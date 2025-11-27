//---------------------------------------------------------
// file:	bullet.h
// author:	[Zachary Ng][Ding Yi Chaw Maung]
// email:	[zacharyhuaen.n@digipen.edu][dingyichaw.maung@digipen.edu]
//
// brief:	Defines bullets and their array helpers.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#pragma once
#ifndef BULLET_H
#define BULLET_H

#include "cprocessing.h"

typedef struct { int red; int green; int blue; int opacity; }Color;
typedef struct Bullet {
	int id;
	CP_Vector centerPos;
	CP_Vector velocity; Color color;
	float diameter; float stateTimer;
	int opacity;
	float bulletDmg;
	float poisonDmg;
	int isPoisoned;
	float poisonDecayTimer;
	int isStunned;
	float stunTimer;

	CP_BOOL isActive; char* type;
	CP_Image yarn;
}Bullet;

typedef struct BulletArr {
	Bullet* bulletArr;
	size_t used; //used = curr num of elements used
	size_t maxLength;
}BulletArr;

/* Bullet_Template()
Input:
    char* name - template key (poison, stun, etc.)
Output:
    Bullet filled with default stats for that type
Brief:
    Builds a bullet blueprint based on name.
*/
Bullet Bullet_Template(char* name);

/* B_Arr_Init()
Input:
    size_t maxLength - slots to reserve
    BulletArr* Array - array to initialize
Output:
    BulletArr* pointer passed in
Brief:
    Clears the array metadata and allocates the buffer.
*/
BulletArr* B_Arr_Init(size_t maxLength, BulletArr* Array);

/* B_Arr_Insert()
Input:
    BulletArr* Array - array to append to
    Bullet bullet - element to add
Output:
    void
Brief:
    Adds a bullet to the end of the array.
*/
void B_Arr_Insert(BulletArr* Array, Bullet bullet);

/* B_Arr_Del()
Input:
    BulletArr* DynArray - array to delete from
    int id - index of bullet to remove
Output:
    void
Brief:
    Removes the bullet with the given id and keeps the rest packed.
*/
void B_Arr_Del(BulletArr* DynArray, int id);

/* B_Arr_Free()
Input:
    BulletArr* Array - array to free
Output:
    void
Brief:
    Releases the bullet buffer.
*/
void B_Arr_Free(BulletArr* Array);

#endif