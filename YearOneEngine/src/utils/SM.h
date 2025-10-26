#ifndef ENT_H
#define ENT_H

#include "cprocessing.h"

#define Up 90.0
#define Left 0.0
#define Down 270.0
#define Right 180.0
#define MAX_ENTITIES 2
#define RED   (Color){ 255, 0,   0,   255 }
#define BLUE  (Color){ 0,   0, 255, 255 }
#define GREEN (Color){ 0, 255,  0,  255 }
#define WHITE (Color){ 255, 255,  255,  255 }

typedef int EntityID;
typedef struct GameEntity GameEntity;
typedef struct StateMachine StateMachine;

typedef struct { int red; int green; int blue; int opacity; }Color;
struct GameEntity {
	/*Generic Values*/
	int id; CP_Vector centerPos; float rotation; CP_BOOL isPlayer; 
	CP_Vector forwardVector; Color color; float diameter; float stateTimer; 
	
	/*Check Values*/
	int isItOnMap; int isSel; char* label; 
}; //Base For all Entities

// Step 1: State function pointer type:
// When u want to make a function call StateFunction which means pointer to a function.
// ^void return		^pointer ^typeName StateFunction	^Parameters
typedef void (*StateFunction)(float deltaTime);

//Holder of Data for each Entity

//eg: Idle State
typedef struct {
	void (*init)(GameEntity* data,  StateMachine* SM, float dt);
	void (*update)(GameEntity* data,  StateMachine* SM, float dt);
	void (*exit)(GameEntity* data,  StateMachine* SM, float dt);
} States;

struct StateMachine {
	States currState;
};

typedef struct ActiveEntity {
	int id;
	GameEntity* unit; //Array
	StateMachine* fsm;

}ActiveEntity;

StateFunction FSM_SetState(StateMachine* fsm, States newState, GameEntity* data, float dt);
StateFunction FSM_Update(StateMachine* fsm, GameEntity* data, float dt);

// Init, Set currState, send function pointer to States.init
#endif