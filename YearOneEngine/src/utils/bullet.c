#include "bullet.h"
#include <stdio.h>
#include <stdlib.h>

BulletArr* B_Arr_Init(size_t maxLength, BulletArr* Array) {
	Array->bulletArr = malloc(maxLength * sizeof(Bullet));
	if (!Array->bulletArr) {
		fprintf(stderr, "Bullet array malloc failed!\n");
		exit(1);
	}
	memset(Array->bulletArr, 0, maxLength * sizeof(Bullet));
	Array->maxLength = maxLength;
	Array->entitySize = 0;
	Array->used = 0;
	for (int i = 0; i < maxLength; i++) {
		*(Array->bulletArr + i) = (Bullet){
		.id = (int)i,
				.centerPos = {100, 100},
				.velocity = {0, 0},
				.color = {255, 0, 0, 255},
				.diameter = 100,
				.stateTimer = 0,
				.opacity = 0
			};
	}

	//for (int i = 0; i < maxLength; i++) { 
	//	(Array->bulletArr[i]) = (Bullet){
	//		.id = (int)i,
	//		.centerPos = {100, 100},
	//		.velocity = {0, 0},
	//		.color = {255, 0, 0, 255},
	//		.diameter = 100,
	//		.stateTimer = 0
	//	};
	//}

	return Array;
}

void B_Arr_Insert(BulletArr* Array, Bullet Entity) {
	//printf("%d",Array->used);
	if (Array->used >= Array->maxLength) {
		Array->maxLength *= 2;
		Array->bulletArr = realloc(Array->bulletArr, Array->maxLength * sizeof(Bullet)); //so how am I able to pass it itself?
		//i  want to add another element to the array. but doesnt this wipe the first array and realloc(, numofArrElems)
		if (!Array->bulletArr) {
			fprintf(stderr, "Memory reallocation failed!\n");
		}
	}
	//realloc tries preserves old data when it enlarges, if unable it allocates new memory but frees old block 
	Entity.id = Array->used;
	Entity.opacity = 255;
	Array->bulletArr[Array->used++] = Entity;

}

void B_Arr_Del(BulletArr* DynArray, int id) {
	printf("Dele");
	int check = 0;
	for (int i = 0; i < DynArray->maxLength - 1; i++) {
		if (1 == check || DynArray->bulletArr[i].id == id)
		{
			DynArray->bulletArr[i] = DynArray->bulletArr[i + 1]; check = 1;
		}
	}
	check = 0;
	DynArray->maxLength -= 1;
	DynArray->used--;
	//realloc tries preserves old data when it enlarges, if unable it allocates new memory but frees old block 
	DynArray->bulletArr = realloc(DynArray->bulletArr, DynArray->maxLength * sizeof(Bullet)); //so how am I able to pass it itself?
	//i  want to add another element to the array. but doesnt this wipe the first array and realloc(, numofArrElems)
	if (!DynArray->bulletArr) {
		fprintf(stderr, "Memory reallocation failed!\n");
	}
}

void B_Arr_Free(BulletArr* Array) {
	free(Array->bulletArr);
	Array->bulletArr = NULL;
	Array->entitySize = 0;
	Array->maxLength = 0;
	Array->used = 0;
}

