#include "bullet.h"
#include <stdio.h>
BulletArr* B_Arr_Init(size_t maxLength, BulletArr* Array) {
	Array->maxLength = maxLength;
	Array->entitySize = 0;
	Array->used = 0;
	Array->bulletElems = (Bullet*)
		malloc(maxLength * sizeof(Bullet));
	for (int i = 0; i < maxLength; i++) {
		*(Array->bulletElems + i) = (Bullet){
		.id = i,  .centerPos = {100, 100}, .velocity = {0,0}, .color = {255,0,0,255}, .diameter = 100, .stateTimer = 0 };
	}

	return Array;
}

void B_Arr_Insert(BulletArr* Array, Bullet Entity) {
	if (Array->used >= Array->maxLength) {
		Array->maxLength *= 2;
		Array->bulletElems = realloc(Array->bulletElems, Array->maxLength * sizeof(Bullet)); //so how am I able to pass it itself?
		//i  want to add another element to the array. but doesnt this wipe the first array and realloc(, numofArrElems)
		if (!Array->bulletElems) {
			fprintf(stderr, "Memory reallocation failed!\n");
		}
	}
	//realloc tries preserves old data when it enlarges, if unable it allocates new memory but frees old block 
	Entity.id = Array->used;
	Array->bulletElems[Array->used++] = Entity;


}

void B_Arr_Del(BulletArr* DynArray, int id) {
	int check = 0;
	for (int i = 0; i < DynArray->maxLength - 1; i++) {
		if (1 == check || DynArray->bulletElems->id == id)
		{
			DynArray->bulletElems[i] = DynArray->bulletElems[i + 1]; check = 1;
		}
	}
	check = 0;
	DynArray->maxLength -= 1;
	DynArray->used--;
	//realloc tries preserves old data when it enlarges, if unable it allocates new memory but frees old block 
	DynArray->bulletElems = realloc(DynArray->bulletElems, DynArray->maxLength * sizeof(Bullet)); //so how am I able to pass it itself?
	//i  want to add another element to the array. but doesnt this wipe the first array and realloc(, numofArrElems)
	if (!DynArray->bulletElems) {
		fprintf(stderr, "Memory reallocation failed!\n");
	}
}

void B_Arr_Free(BulletArr* Array) {
	free(Array->bulletElems);
	Array->bulletElems = NULL;
	Array->entitySize = 0;
	Array->maxLength = 0;
	Array->used = 0;
}