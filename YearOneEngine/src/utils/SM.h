//---------------------------------------------------------
// file:	SM.h
// author:	Zachary Ng
// email:	zacharyhuaen.n@digipen.edu
//
// brief:	Contains declarations of functions 
//			StateMachine.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#ifndef ENT_H
#define ENT_H

#include "cprocessing.h"
#include "sound.h"
#include "bullet/bullet.h"

#define Up 90.0
#define Left 0.0
#define Down 270.0
#define Right 180.0
#define MAX_ENTITIES 50
#define RED   (Color){ 255, 0,   0,   255 }
#define BLUE  (Color){ 0,   0, 255, 255 }
#define GREEN (Color){ 0, 255,  0,  255 }
#define WHITE (Color){ 255, 255,  255,  255 }
#define WHITISH (Color){ 255, 255,  255,  100 }
#define REALLYCLEAR (Color){ 255, 255,  255,  0 }

typedef int EntityID;
typedef struct GameEntity GameEntity;
typedef struct StateMachine StateMachine;

/* GameEntity
Brief:
	GameEntity contains positional, 
*/
struct GameEntity {
	/*Generic Values*/
	BulletArr bullets;	 
	entSound sound;
	CP_Image sprite, shadow;
	CP_Vector accel, centerPos, forwardVector, velocity; 
	CP_BOOL isPlayer; Color color; 
	float rotation, diameter, stateTimer;
	float poisonTimerDecay, poisonDamage;
	float stunTimer, sWidth, sHeight, aspectRatio, scale;
	int isStunned, pickUpIndex, pickUpRemoval, isPoisoned;
	/*Check Values*/
	int isItOnMap; int isSel; char* label;

 
}; //Base For all Entities

// NOTES:
// Step 1: State function pointer type:
// When u want to make a function call StateFunction which means pointer to a function.
// ^void return		^pointer ^typeName StateFunction	^Parameters
typedef void (*StateFunction)(float deltaTime);

//eg: Idle State: will have 3 functions, Init, Update, Exit.
typedef struct {
	void (*Init)(GameEntity* data,  StateMachine* sm, float dt); //replace with T
	void (*Update)(GameEntity* data,  StateMachine* sm, float dt);
	void (*Exit)(GameEntity* data,  StateMachine* sm, float dt);
} States;

struct StateMachine {
	States currState;
};  

typedef struct ActiveEntity ActiveEntity;

/* FSM_SetState()
Input:
	StateMachine* fsm     - pointer to the Entity's State
	States newState		  - the newState to replace currState in fsm
	GameEntity* data	  - positional data/ flags/ image/ sound data 
	float dt			  - deltaTime
	
Output:
	Returns the StateFunction.
*/
StateFunction FSM_SetState(StateMachine* fsm, States newState, GameEntity* data, float dt); //Replace with T

/* FSM_Update()
Input:
	StateMachine* fsm     - pointer to the Entity's State
	GameEntity* data	  - positional data/ flags/ image/ sound data
	float dt			  - deltaTime

Output:
	Returns the StateFunction.
*/
StateFunction FSM_Update(StateMachine* fsm, GameEntity* data, float dt);

/* FSM_Init()
Input:
	StateMachine* fsm     - pointer to the Entity's State
	GameEntity* data	  - positional data/ flags/ image/ sound data
	float dt			  - deltaTime

Output:
	Returns the StateFunction.
*/
StateFunction FSM_Init(StateMachine* fsm, GameEntity* data, float dt);

#endif