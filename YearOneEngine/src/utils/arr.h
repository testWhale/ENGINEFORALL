//---------------------------------------------------------
// file:	arr.h
// author:	[Zachary Ng]
// email:	[zacnghuaen.n@digipen.edu]
//
// brief:	Contains definition of dynamic array 
//			
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

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

/* Arr_Init()
Input:
    size_t maxLength - slots to reserve
    TestArr* Array - target array
Output:
    void
Brief:
    Allocates ActiveEntity storage and clears counters.
*/
void Arr_Init(size_t maxLength, TestArr* Array);

/* Arr_Insert()
Input:
    TestArr* Array - array to append into
    ActiveEntity Entity - value to add
Output:
    void
Brief:
    Grows the buffer if needed and sets up the new entity.
*/
void Arr_Insert(TestArr* Array, ActiveEntity Entity);

/* Arr_Del()
Input:
    TestArr* Array - array to remove from
    int id - id of the entity to delete
Output:
    void
Brief:
    Finds the entity by id and packs the array by replacing it with the last entry.
*/
void Arr_Del(TestArr* Array, int id);

/* Arr_Free()
Input:
    TestArr* Array - array to free
Output:
    void
Brief:
    Releases the array buffer and resets metadata.
*/
void Arr_Free(TestArr* Array);

#endif /* UTILS_ARR_H_INCLUDED */
