#include <stdio.h>
#include <stdlib.h>
#include "arr.h"
#include "SM.h"
TestArr* Arr_Init(size_t maxLength, TestArr* Array) {
	Array->maxLength = maxLength;
	Array->entitySize = 0;
	Array->used = 0;
	Array->ActiveEntityArr = (ActiveEntity*)
		malloc(maxLength * sizeof(ActiveEntity));
	for (int i = 0; i < maxLength; i++) {
		*(Array->ActiveEntityArr + i) = (ActiveEntity){
		.id = i, .unit = 0, .fsm = NULL  };
	}

	return Array;
}

void Arr_Insert(TestArr* Array, ActiveEntity Entity) {
	if (Array->used >= Array->maxLength) {
		Array->maxLength *= 2;
		Array->ActiveEntityArr = realloc(Array->ActiveEntityArr, Array->maxLength * sizeof(ActiveEntity)); //so how am I able to pass it itself?
		//i  want to add another element to the array. but doesnt this wipe the first array and realloc(, numofArrElems)
		if (!Array->ActiveEntityArr) {
			fprintf(stderr, "Memory reallocation failed!\n");
		}
	}
	//realloc tries preserves old data when it enlarges, if unable it allocates new memory but frees old block 
	Entity.id = Array->used;
	Array->ActiveEntityArr[Array->used] = Entity;

	GameEntity* unit = &Array->ActiveEntityArr[Array->used].unit ;

	B_Arr_Init(2, &unit->bullets);
	for (int j = 0; j < 4; j++) {
		//memset(&unit->bullets, 0, sizeof(unit->bullets));
		Bullet b = { .id = j, .centerPos = unit->centerPos, .velocity = {1,0}, .color = {0,255,0,255}, .diameter = 5 };
		B_Arr_Insert(&unit->bullets, b);
		unit->bullets.bulletArr[j].opacity = 0;
		printf("Turret %d,  Bullet ID: %d \n", Array->ActiveEntityArr[Array->used].id, unit->bullets.bulletArr[j].id);
	}
	Array->ActiveEntityArr[Array->used++];

}

void Arr_Del(TestArr* DynArray, int id){
	int check = 0;
	for (int i = 0; i < DynArray->maxLength-1; i++) {
		if (1 == check || DynArray->ActiveEntityArr->id == id ) 
		{ DynArray->ActiveEntityArr[i] = DynArray->ActiveEntityArr[i + 1]; check = 1; } 
	}
	check = 0;
	DynArray->maxLength -= 1;
	DynArray->used--;
	//realloc tries preserves old data when it enlarges, if unable it allocates new memory but frees old block 
	DynArray->ActiveEntityArr = realloc(DynArray->ActiveEntityArr, DynArray->maxLength * sizeof(ActiveEntity)); //so how am I able to pass it itself?
	//i  want to add another element to the array. but doesnt this wipe the first array and realloc(, numofArrElems)
	if (!DynArray->ActiveEntityArr) {
		fprintf(stderr, "Memory reallocation failed!\n");
	}
}

void Arr_Free(TestArr* Array) {
	free(Array->ActiveEntityArr);
	Array->ActiveEntityArr = NULL;
	Array->entitySize = 0;
	Array->maxLength = 0;
	Array->used = 0;
}

//void Arr_Render(TestArr* Array) {
//
//}