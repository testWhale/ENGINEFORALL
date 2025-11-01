#include <stdio.h>
#include <stdlib.h>
#include "arr.h"


TestArr Arr_Init(size_t maxLength) {
	TestArr array;
	array.maxLength = maxLength;
	array.entitySize = 0;
	array.used = 0;
	array.ActiveEntityArr = (ActiveEntity*)
		malloc(maxLength * sizeof(ActiveEntity));
	for (int i = 0; i < maxLength; i++) {
		*(array.ActiveEntityArr + i) = (ActiveEntity){
		.id = 0, .fsm=NULL, .unit = NULL};
	}
	
	return array;
}

void Arr_Insert(TestArr* Array, ActiveEntity Entity) {
	if (Array->used >= Array->maxLength) {
		Array->maxLength += 1;
	}
	//realloc tries preserves old data when it enlarges, if unable it allocates new memory but frees old block 
	Array->ActiveEntityArr = realloc(Array->ActiveEntityArr, Array->maxLength * sizeof(ActiveEntity)); //so how am I able to pass it itself?
	//i  want to add another element to the array. but doesnt this wipe the first array and realloc(, numofArrElems)
	if (!Array->ActiveEntityArr) {
		fprintf(stderr, "Memory reallocation failed!\n");
	}
	Array->ActiveEntityArr[Array->used] = Entity;
	Array->used++;
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

