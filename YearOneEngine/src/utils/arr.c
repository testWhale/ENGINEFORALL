#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils/arr.h"
#include "State.h"

TestArr enemyArr;
TestArr playerArr;

void Arr_Init(size_t maxLength, TestArr* A) {
    if (!A) return;
    if (maxLength == 0) maxLength = 1;
    // intilizes with zeroing, if pointer assigns zero
    A->ActiveEntityArr = (ActiveEntity*)calloc(maxLength, sizeof(ActiveEntity));
    if (!A->ActiveEntityArr) {
        fprintf(stderr, "Arr_Init: allocation failed\n");
        A->maxLength = A->used = A->entitySize = 0;
        return;
    }
    A->maxLength = maxLength;
    A->used = 0;
    A->entitySize = sizeof(ActiveEntity);
}

void Arr_Insert(TestArr* A, ActiveEntity e) {
    if (!A) return;

    if (A->used >= A->maxLength) {

        size_t newCap = (A->maxLength ? A->maxLength * 2 : 1);
        /* make a tmp new memory space 
        -> to avoid losing original array, 
        -> realloc resizes existing block, OR allocates new Memory Block copying old data
        -> realloc (the existing array, to new size (aka. new Max Length * sizeof(ActiveEntity)    */
        ActiveEntity* tmp = (ActiveEntity*)realloc(A->ActiveEntityArr, newCap * sizeof(ActiveEntity));
        if (!tmp) { fprintf(stderr, "Arr_Insert: realloc failed\n"); return; }

        /* zero out the new memory, (tmp) = address containing start of new array, 
            -> + A -> maxLength move past the existing elements    
            -> fill value with 0,
            -> total byte size of new memory (excluding existing)   */
        memset(tmp + A->maxLength, 0, (newCap - A->maxLength) * sizeof(ActiveEntity));

        /* since no error, assign new block address tmp to ActiveEntityArr */
        A->ActiveEntityArr = tmp;
        /* since no error, assign new maxLength */
        A->maxLength = newCap;
    }

    /* When we insert a new unit into arr, 
    -> we need to intilise its bullet array 
    -> and insert in some values */
    A->ActiveEntityArr->id = A->used;
    A->ActiveEntityArr[A->used] = e;
    GameEntity* unit = &A->ActiveEntityArr[A->used].unit;
    
    // Initlise bullet array, with 0 values.
    B_Arr_Init(2, &unit->bullets);
    for (int j = 0; j < 4; j++) {
        printf("j = %d\n", j);
        //memset(&unit->bullets, 0, sizeof(unit->bullets));
        Bullet b = { .id = j, .centerPos = unit->centerPos, .velocity = {1,0}, .color = {0,255,0,255}, .diameter = 50 };
        B_Arr_Insert(&unit->bullets, b);
        unit->bullets.bulletArr[j].opacity = 0;
        printf("Turret %d,  Bullet ID: %d \n", A->ActiveEntityArr[A->used].id, unit->bullets.bulletArr[j].id);
    }

    if (e.maxHealth <= 0) e.maxHealth = 100;
    if (e.health <= 0) e.health = e.maxHealth;
    if (e.alive != 0 && e.alive != 1) e.alive = 1;

    A->ActiveEntityArr[A->used++] = e;
}

void Arr_Del(TestArr* A, int id) {
    if (!A || A->used == 0) return;
    size_t idx = A->used;
    for (size_t i = 0; i < A->used; ++i)
        if (A->ActiveEntityArr[i].id == id) { idx = i; break; }
    if (idx == A->used) return;
    A->ActiveEntityArr[idx] = A->ActiveEntityArr[A->used - 1];
    --A->used;
}

void Arr_Free(TestArr* A) {
    if (!A) return;
    free(A->ActiveEntityArr);
    A->ActiveEntityArr = NULL;
    A->entitySize = 0;
    A->used = 0;
    A->maxLength = 0;
}
