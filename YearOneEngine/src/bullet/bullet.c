#include "bullet.h"
#include "../utils/arr/State.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// for strcmp, memset
//ARR_(Bullet)
//typedef struct {
//    int id;
//    char label[45];
//    CP_Image img;
//    char* filepath;
//    CP_Vector leftTCornerPos;
//}UI;
//
//ARR_(UI)

Bullet Bullet_Template(const char* name) {
    Bullet bullet = { 0 };
    int dt = CP_System_GetDt();
    if (strcmp(name, "poison") == 0) {
        bullet = (Bullet){
            .id = 0,
            .centerPos = {100, 100},
            .velocity = {0, 0},
            .color = {255, 0, 255, 255},
            .diameter = 30,
            .opacity = 0,
            .type = "poison",
            .bulletDmg = 2.0f,
            .poisonDmg = 10.0f
        };
        bullet.bulletDmg += bullet.poisonDmg * dt;
    }
    else if (strcmp(name, "stun") == 0) {
        bullet = (Bullet){
            .id = 0,
            .centerPos = {100, 100},
            .velocity = {0, 0},
            .color = {255, 255, 0, 255},
            .diameter = 30,
            .opacity = 0,
            .type = "stun",
            .bulletDmg = 10.0f,
            .stunTimer = 1.0f
        };
    }
    else { // default "normal"
        bullet = (Bullet){
            .id = 0,
            .centerPos = {100, 100},
            .velocity = {0, 0},
            .color = {255, 0, 0, 255},
            .diameter = 30,
            .opacity = 0,
            .type = "normal",
            .bulletDmg = 10.0f
        };
    }

    return bullet;
}



/* ---------------- INIT ---------------- */
BulletArr* B_Arr_Init(size_t initialCapacity, BulletArr* A) {
    //BulletArr_Init(initialCapacity, A);
    A->bulletArr = (BulletArr*)calloc(initialCapacity, sizeof(Bullet));
    if (!A->bulletArr) {
        fprintf(stderr, "Bullet array malloc failed!\n");
        exit(EXIT_FAILURE);
    }
    // memset (starting address to be filled, value to fill, num of bytes to fill)      initialCapacity= num of []
    A->maxLength = initialCapacity;
    A->used = 0;

    return A;
}

/* ---------------- INSERT ---------------- */
void B_Arr_Insert(BulletArr* A, Bullet Entity) {
    //BulletArr_Insert(A, Entity);

    if (!A) return;

    if (A->used >= A->maxLength) {

        size_t newCap = (A->maxLength ? A->maxLength * 2 : 1);
        /* make a tmp new memory space
        -> to avoid losing original array,
        -> realloc resizes existing block, OR allocates new Memory Block copying old data
        -> realloc (the existing array, to new size (aka. new Max Length * sizeof(Bullet)    */
        Bullet* tmp = (Bullet*)realloc(A->bulletArr, newCap * sizeof(Bullet));
        if (!tmp) { fprintf(stderr, "Arr_Insert: realloc failed\n"); return; }

        /* zero out the new memory, (tmp) = address containing start of new array,
            -> + A -> maxLength move past the existing elements
            -> fill value with 0,
            -> total byte size of new memory (excluding existing)   */
        memset(tmp + A->maxLength, 0, (newCap - A->maxLength) * sizeof(Bullet));

        /* since no error, assign new block address tmp to ActiveEntityArr */
        A->bulletArr = tmp;
        /* since no error, assign new maxLength */
        A->maxLength = newCap;
    }

    Entity.id = A->used;
    Entity.opacity = 255;
    A->bulletArr[A->used++] = Entity;
}

/* ---------------- DELETE ---------------- */
void B_Arr_Del(BulletArr* A, int id) {
    if (A->used == 0) return;

    int foundIndex = -1;
    // loop through until id is found. if [3and 4]
    for (int i = 0; i < A->used; i++) {
        if (A->bulletArr[i].id == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) return;  // if not found return not found

    // Shift everything left -> Why do we seperate thz 2 loops?
    // Cleaner, let's us set the flag alr. leaving only the copy code to handle.
    for (int i = foundIndex; i < A->used - 1; i++) {
        A->bulletArr[i] = A->bulletArr[i + 1];
        A->bulletArr[i].id = i; // keep IDs consistent
    }

    A->used--;

    // shrink only if under 1/4 capacity
    if (A->used > 0 && A->used < A->maxLength / 4) {
        size_t newCapacity = A->maxLength / 2;
        Bullet* temp = realloc(A->bulletArr, newCapacity * sizeof(Bullet));
        if (temp) {
            A->bulletArr = temp;
            A->maxLength = newCapacity;
            printf("Bullet array shrunk to %zu\n", newCapacity);
        }
    }
    //Edge case to teammates: what happens when buffer shrinks to 1 elem?
    /* If after deleting 1 bullet, maxLength =1, used = 1,
    -> if delete another bullet, -> the maxLength = 0 -> realloc(0). UNDEFINED BREAKS */
    /*SO sort based on used if arr has 2 elems, -> delete 1 -> used =1 BUT maxlength still stays 2
    when insert again, it still has space! no nd undefined realloc(0)*/
}

/* ---------------- FREE ---------------- */
void B_Arr_Free(BulletArr* A) {
    free(A->bulletArr);
    A->bulletArr = NULL;
    A->maxLength = 0;
    A->used = 0;
}

