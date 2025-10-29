#pragma once
#include "SM.h"
typedef struct TestArr {
	ActiveEntity* ActiveEntityArr; //I want TestArr to own dynamic arr ActiveEntity structs, Allows me to free it here.
	size_t entitySize; //why not pointer? cause i want my array to actually own these structs and be able to use and delete them as and when.
	size_t used; //used = curr empty entry
	size_t maxLength;
}TestArr;
TestArr enemyArr; //newArr IS OUR ONLY ENTITY ARRAY will change name
TestArr playerArr; //playerArr is ONLY UNIT ARRAY will change name

TestArr* Arr_Init(size_t maxLength, TestArr* Array);

void Arr_Insert(TestArr* Array, ActiveEntity Entity);

void Arr_Del(TestArr* DynArray, int id);

void Arr_Free(TestArr* Array);