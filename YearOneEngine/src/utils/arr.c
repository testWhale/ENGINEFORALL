#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "utils/arr.h"

TestArr enemyArr;
TestArr playerArr;

void Arr_Init(size_t maxLength, TestArr* A) {
    if (!A) return;
    if (maxLength == 0) maxLength = 1;
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
        ActiveEntity* tmp = (ActiveEntity*)realloc(A->ActiveEntityArr, newCap * sizeof(ActiveEntity));
        if (!tmp) { fprintf(stderr, "Arr_Insert: realloc failed\n"); return; }
        memset(tmp + A->maxLength, 0, (newCap - A->maxLength) * sizeof(ActiveEntity));
        A->ActiveEntityArr = tmp;
        A->maxLength = newCap;
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
