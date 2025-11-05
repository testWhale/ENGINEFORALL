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
	CP_BOOL isActive; char* type;
}Bullet;

typedef struct BulletArr {
	Bullet* bulletArr;
	size_t entitySize; //why not pointer? cause i want my array to actually own these structs and be able to use and delete them as and when.
	size_t used; //used = curr empty entry
	size_t maxLength;
}BulletArr;

Bullet BulletTemplate(char* name);

BulletArr* B_Arr_Init(size_t maxLength, BulletArr* Array);

void B_Arr_Insert(BulletArr* Array, Bullet bullet);

void B_Arr_Del(BulletArr* DynArray, int id);

void B_Arr_Free(BulletArr* Array);

#endif