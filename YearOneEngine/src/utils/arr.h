#ifndef UTILS_ARR_H_INCLUDED
#define UTILS_ARR_H_INCLUDED

#include <stddef.h>
#include "state/pickup.h"   // GameEntity
#include "utils/SM.h"       // StateMachine

// utils/arr.h  (ActiveEntity definition)
typedef struct ActiveEntity {
    int id;
    GameEntity unit;
    StateMachine fsm;

    int   maxHealth;
    float   health;
    int   alive;
    int   hasScored;        
    float lastLeftmostX;  
    int   isHitting;     
    float  contactTime;
} ActiveEntity;


typedef struct TestArr {
    ActiveEntity* ActiveEntityArr;
    size_t        entitySize;
    size_t        used;
    size_t        maxLength;
} TestArr;

extern TestArr enemyArr;
extern TestArr playerArr;

void Arr_Init(size_t maxLength, TestArr* Array);
void Arr_Insert(TestArr* Array, ActiveEntity Entity);
void Arr_Del(TestArr* Array, int id);
void Arr_Free(TestArr* Array);

#endif /* UTILS_ARR_H_INCLUDED */
