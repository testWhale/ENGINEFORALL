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
	float stunTimer;
	float poisonDmg;
	int isPoisoned;
	float poisonDecayTimer;
	CP_BOOL isActive; char* type;
}Bullet;

typedef struct BulletArr {
	Bullet* bulletArr;
	size_t used; //used = curr num of elements used
	size_t maxLength;
}BulletArr;

Bullet Bullet_Template(char* name);

BulletArr* B_Arr_Init(size_t maxLength, BulletArr* Array);

void B_Arr_Insert(BulletArr* Array, Bullet bullet);

void B_Arr_Del(BulletArr* DynArray, int id);

void B_Arr_Free(BulletArr* Array);

#endif