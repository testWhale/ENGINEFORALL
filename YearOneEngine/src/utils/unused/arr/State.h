/*Ok so this file is a generic macro used for activeEntities & dynamic arrays.  
The purpose of which is to allow for dynamic memory storage & ease of use with creating new activeEntities.
Note: u have to define T##_ActiveEntity first before your dynamic array that stores it.

eg, struct name: uiButton			NewEntity(uiButton)--->uiButton_ActiveEntity

Step 1: Fill up uiButton_ActiveEntity!---
	First, uiButton_ActiveEntity requires three parameters,	(T##ActiveEntity* entity, StateMachine state, T data)
	define all 3 first before passing it into uiButton_ActiveEntity_Init();
----

Step 2: Creating uiButton_ActiveEntity_MacroArr!--- 
	First, uiButton_ActiveEntity_MacroArr is defined by 
	---ARR_(T), where T= uiButton_ActiveEntity,		---> uiButton_ActiveEntity_MacroArr
	uiButton_ActiveEntity_MacroArr uiButtonArrPtr   ---> make a Array

	Secondly, uiButtonArr_Init requires u to define the size and array that u are pointing to.
	eg. uiButton_ActiveEntityArr_Init(2 <---size of Arr, uiButton_MacroArr* wrapperArray <---this is a wrapper that includes every detal )
----

Step 3: Inserting Elements into the MacroArr!---
	First, have a template of type T eg.( struct uiButton_ActiveEntity	) to fill up the values
	eg. uiButton_ActiveEntityArr_Insert( uiButton_ActiveEntity_MacroArr* Array, uiButton_ActiveEntity template	)
	this function copys the template, -> inserting and filling ur Array.
*/

#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "../SM.h"

/*--------------------------------------------------------*/
#define NewEntity(T)\
typedef struct { 																						\
	T data; 																							\
	StateMachine fsm;																					\
}T##ActiveEntity;																						\
																										\
static inline T##ActiveEntity* T##_ActiveEntity_Init(T##ActiveEntity* entity, StateMachine state, T data){ \
	entity->data=data;																					\
	entity->fsm=state;																					\
	return entity;}																						\
static inline StateFunction T##FSM_SetState(StateMachine* fsm, States newState, T* data, float dt);		\
static inline StateFunction T##FSM_Update(StateMachine* fsm, T* data, float dt);						\
/*--------------------------------------------------------*/

#define ZERO_NEW_MEMORY(ptr, old_len, new_len, type)	\
	memset((ptr) + old_len, 0, (new_len - old_len) * sizeof(type))	\

#define ARR_(T)																							\
typedef struct { 																						\
	T* elem; 																							\
	size_t used;																						\
	size_t maxLength;																					\
}T##_MacroArr; 																							\
static inline T##_MacroArr* T##Arr_Init(size_t maxLength, T##_MacroArr* A){							\
	if(!A)return;																					\
	if(maxLength==0)maxLength=1;																		\
	A->maxLength = maxLength;																		\
	A->used = 0;																					\
	A->elem = (T*)calloc(maxLength, sizeof(T));														\
	if (!A->elem) {																					\
		fprintf(stderr, "Arr_Init: allocation failed\n");												\
		return NULL;																							\
	}																									\
																										\
	return A;																						\
}																										\
																										\
static inline T##_MacroArr* T##Arr_Insert(T##_MacroArr* A, T Entity) { \
    if (!A) return; \
    if (A->used >= A->maxLength) { \
        size_t newCap = (A->maxLength ? A->maxLength * 2 : 1); \
        /* make a tmp new memory space 
		-> to avoid losing original array,
		-> realloc resizes existing block, OR allocates new Memory Block copying old data
		-> realloc (the existing array, to new size (aka. new Max Length * sizeof(ActiveEntity)    */\
        T* tmp = (T*)realloc(A->elem, newCap * sizeof(T)); \
        if (!tmp) { \
            fprintf(stderr, "Arr_Insert: realloc failed\n"); \
            return; \
        } \
			/* zero out the new memory, (tmp) = address containing start of new array,
			-> + A -> maxLength move past the existing elements
			-> fill value with 0,
			-> total byte size of new memory (excluding existing)   */\
			ZERO_NEW_MEMORY(A, A->maxLength, newCap, T); \
        A->elem = tmp; \
        A->maxLength = newCap; \
    } \
    A->elem[A->used++] = Entity; \
	return A; \
}\
																										\
																										\
static inline void T##Arr_Free(T##_MacroArr* Array){ 													\
	free(Array->elem);																					\
	Array->elem = NULL;																					\
	Array->maxLength = 0;																				\
	Array->used = 0;																					\
}																										\
																										\
static inline void T##Arr_Del(T##_MacroArr* A, int id) {												\
if (!A || A->used == 0) return;																			\
	size_t idx = A->used;																				\
for (size_t i = 0; i < A->used; ++i)																	\
	if (A->elem[i].id == id) { idx = i; break; }														\
		if (idx == A->used) return;																		\
		A->elem[idx] = A->elem[A->used - 1];															\
		--A->used;																						\
																										\
}																										\
/*--------------------------------------------------------*/


 
//#define SM(T)							\
//typedef struct GameEntity GameEntity; \
//typedef struct StateMachine StateMachine; \
//											\
//typedef struct { int red; int green; int blue; int opacity; }Color; \
//struct GameEntity { \
//	/*Generic Values*/ \
//	int id; CP_Vector centerPos; float rotation; CP_BOOL isPlayer; \
//	CP_Vector forwardVector; Color color; float diameter; float stateTimer; \
//																			\
//	/*Check Values*/
//	int isItOnMap; int isSel; char* label; entSound sound;				\
//}; /*Base For all Entities			*/															\
//																		\
///* Step 1: State function pointer type : */																		\
///* When u want to make a function call StateFunction which means pointer to a function. */						\
///* ^void return		^pointer ^typeName StateFunction	^Parameters*/ 											\
//typedef void (*StateFunction)(float deltaTime);										\
//																		\
///*Holder of Data for each Entity*/ 																		\
//																		\
///*eg: Idle State*/ 																		\
//typedef struct { 																		\
//	void (*init)(GameEntity* data, StateMachine* SM, float dt); 																		\
//	void (*update)(GameEntity* data, StateMachine* SM, float dt);																		\
//	void (*exit)(GameEntity* data, StateMachine* SM, float dt);																		\
//} States;																		\
//																		\
//struct StateMachine {																		\
//	States currState;																		\
//};																		\
//																		\
//typedef struct T {																		\
//	int id;																		\
//	GameEntity unit; 																		\
//	StateMachine fsm; 																	\
//																		\
//}T;																		\
//																		\
//StateFunction FSM_SetState(StateMachine* fsm, States newState, GameEntity* data, float dt);																		\
//StateFunction FSM_Update(StateMachine* fsm, GameEntity* data, float dt);																		\
