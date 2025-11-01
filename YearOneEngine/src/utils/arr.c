#include <stdio.h>
#include <stdlib.h>
#include "arr.h"

TestArr* Arr_Init(size_t maxLength, TestArr* Array) {
	Array->maxLength = maxLength;
	Array->entitySize = 0;
	Array->used = 0;
	Array->ActiveEntityArr = (ActiveEntity*)
		malloc(maxLength * sizeof(ActiveEntity));
	for (int i = 0; i < maxLength; i++) {
		*(Array->ActiveEntityArr + i) = (ActiveEntity){
		.id = i, .fsm = NULL, .unit = NULL };
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
	Entity.unit.id = Array->used;
	Array->ActiveEntityArr[Array->used++] = Entity;


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

