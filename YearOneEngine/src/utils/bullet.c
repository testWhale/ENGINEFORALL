#include "bullet.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strcmp, memset

Bullet BulletTemplate(const char* name) {
    Bullet bullet = { 0 };

    if (strcmp(name, "poison") == 0) {
        bullet = (Bullet){
            .id = 0,
            .centerPos = {100, 100},
            .velocity = {0, 0},
            .color = {0, 255, 0, 255},
            .diameter = 300,
            .opacity = 0,
            .type = "poison"
        };
    }
    else if (strcmp(name, "stun") == 0) {
        bullet = (Bullet){
            .id = 0,
            .centerPos = {100, 100},
            .velocity = {0, 0},
            .color = {255, 255, 0, 255},
            .diameter = 300,
            .opacity = 0,
            .type = "stun"
        };
    }
    else { // default "normal"
        bullet = (Bullet){
            .id = 0,
            .centerPos = {100, 100},
            .velocity = {0, 0},
            .color = {255, 0, 0, 255},
            .diameter = 100,
            .opacity = 0,
            .type = "normal"
        };
    }

    return bullet;
}

/* ---------------- INIT ---------------- */
BulletArr* B_Arr_Init(size_t initialCapacity, BulletArr* Array) {
    Array->bulletArr = malloc(initialCapacity * sizeof(Bullet));
    if (!Array->bulletArr) {
        fprintf(stderr, "Bullet array malloc failed!\n");
        exit(EXIT_FAILURE);
    }

    memset(Array->bulletArr, 0, initialCapacity * sizeof(Bullet));
    Array->maxLength = initialCapacity;
    Array->used = 0;
    Array->entitySize = sizeof(Bullet);

    return Array;
}

/* ---------------- INSERT ---------------- */
void B_Arr_Insert(BulletArr* Array, Bullet Entity) {
    if (Array->used >= Array->maxLength) {
        size_t newCapacity = Array->maxLength * 2;
        Bullet* temp = realloc(Array->bulletArr, newCapacity * sizeof(Bullet));
        if (!temp) {
            fprintf(stderr, "Bullet array reallocation failed!\n");
            return;
        }

        Array->bulletArr = temp;
        Array->maxLength = newCapacity;
        printf("Bullet array expanded to %zu\n", Array->maxLength);
    }

    Entity.id = Array->used;
    Entity.opacity = 255;
    Array->bulletArr[Array->used++] = Entity;
}

/* ---------------- DELETE ---------------- */
void B_Arr_Del(BulletArr* DynArray, int id) {
    if (DynArray->used == 0) return;

    int foundIndex = -1;

    for (int i = 0; i < DynArray->used; i++) {
        if (DynArray->bulletArr[i].id == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) return; // Not found

    // Shift everything left
    for (int i = foundIndex; i < DynArray->used - 1; i++) {
        DynArray->bulletArr[i] = DynArray->bulletArr[i + 1];
        DynArray->bulletArr[i].id = i; // keep IDs consistent
    }

    DynArray->used--;

    // Optional: shrink only if under 1/4 capacity
    if (DynArray->used > 0 && DynArray->used < DynArray->maxLength / 4) {
        size_t newCapacity = DynArray->maxLength / 2;
        Bullet* temp = realloc(DynArray->bulletArr, newCapacity * sizeof(Bullet));
        if (temp) {
            DynArray->bulletArr = temp;
            DynArray->maxLength = newCapacity;
            printf("Bullet array shrunk to %zu\n", newCapacity);
        }
    }
}

/* ---------------- FREE ---------------- */
void B_Arr_Free(BulletArr* Array) {
    free(Array->bulletArr);
    Array->bulletArr = NULL;
    Array->entitySize = 0;
    Array->maxLength = 0;
    Array->used = 0;
}
