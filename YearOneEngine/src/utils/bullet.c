#include "bullet.h"
#include <stdio.h>
#include <stdlib.h>
<<<<<<< Updated upstream:YearOneEngine/src/utils/bullet.c
#include <string.h> // for strcmp, memset

Bullet BulletTemplate(const char* name) {
    Bullet bullet = { 0 };

=======
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

Bullet BulletTemplate(const char* name) {
    Bullet bullet = { 0 };
    int dt = CP_System_GetDt();
>>>>>>> Stashed changes:YearOneEngine/src/bullet/bullet.c
    if (strcmp(name, "poison") == 0) {
        bullet = (Bullet){
            .id = 0,
            .centerPos = {100, 100},
            .velocity = {0, 0},
            .color = {255, 0, 255, 255},
            .diameter = 100,
            .opacity = 0,
            .type = "poison",
            .bulletDmg = 10.0f,
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
            .diameter = 100,
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
            .diameter = 100,
            .opacity = 0,
            .type = "normal",
            .bulletDmg = 10.0f
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
    // memset (starting address to be filled, value to fill, num of bytes to fill)      initialCapacity= num of []
    memset(Array->bulletArr, 0, initialCapacity * sizeof(Bullet)); // [Bullet] [Bullet] [Bullet] [Bullet] 
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
        printf("Bullet array expanded to %zu\n", Array->used);
    }

    Entity.id = Array->used;
    Entity.opacity = 255;
    Array->bulletArr[Array->used++] = Entity;
}

/* ---------------- DELETE ---------------- */
void B_Arr_Del(BulletArr* DynArray, int id) {
    if (DynArray->used == 0) return;

    int foundIndex = -1;
    // loop through until id is found. if [3and 4]
    for (int i = 0; i < DynArray->used; i++) {
        if (DynArray->bulletArr[i].id == id) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) return;  // if not found return not found

    // Shift everything left -> Why do we seperate thz 2 loops?
    // Cleaner, let's us set the flag alr. leaving only the copy code to handle.
    for (int i = foundIndex; i < DynArray->used - 1; i++) {
        DynArray->bulletArr[i] = DynArray->bulletArr[i + 1];
        DynArray->bulletArr[i].id = i; // keep IDs consistent
    }

    DynArray->used--;

    // shrink only if under 1/4 capacity
    if (DynArray->used > 0 && DynArray->used < DynArray->maxLength / 4) {
        size_t newCapacity = DynArray->maxLength / 2;
        Bullet* temp = realloc(DynArray->bulletArr, newCapacity * sizeof(Bullet));
        if (temp) {
            DynArray->bulletArr = temp;
            DynArray->maxLength = newCapacity;
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
void B_Arr_Free(BulletArr* Array) {
    free(Array->bulletArr);
    Array->bulletArr = NULL;
    Array->entitySize = 0;
    Array->maxLength = 0;
    Array->used = 0;
}
