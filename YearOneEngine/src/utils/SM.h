#ifndef ENT_H
#define ENT_H

#include "cprocessing.h"
#include "sound.h"
#include "bullet/bullet.h"

#define Up 90.0
#define Left 0.0
#define Down 270.0
#define Right 180.0
#define MAX_ENTITIES 10
#define RED   (Color){ 255, 0,   0,   255 }
#define BLUE  (Color){ 0,   0, 255, 255 }
#define GREEN (Color){ 0, 255,  0,  255 }
#define WHITE (Color){ 255, 255,  255,  255 }
#define WHITISH (Color){ 255, 255,  255,  100 }
#define REALLYCLEAR (Color){ 255, 255,  255,  0 }

typedef int EntityID;
typedef struct GameEntity GameEntity;
typedef struct StateMachine StateMachine;

struct GameEntity {
	/*Generic Values*/
	CP_Vector centerPos; float rotation; CP_BOOL isPlayer; 
	CP_Vector forwardVector, velocity; Color color; float diameter; float stateTimer; 
	int isPoisoned;
	float poisonTimerDecay;
	float poisonDamage;
	int isStunned;
	float stunTimer;

	/*Check Values*/
	int isItOnMap; int isSel; char* label; entSound sound;
	BulletArr bullets;

	CP_Image sprite, shadow;
}; //Base For all Entities

// Step 1: State function pointer type:
// When u want to make a function call StateFunction which means pointer to a function.
// ^void return		^pointer ^typeName StateFunction	^Parameters
typedef void (*StateFunction)(float deltaTime);

//Holder of Data for each Entity

//eg: Idle State
typedef struct {
	void (*Init)(GameEntity* data,  StateMachine* sm, float dt); //replace with T
	void (*Update)(GameEntity* data,  StateMachine* sm, float dt);
	void (*Exit)(GameEntity* data,  StateMachine* sm, float dt);
} States;

struct StateMachine {
	States currState;
};  

typedef struct ActiveEntity ActiveEntity;



StateFunction FSM_SetState(StateMachine* fsm, States newState, GameEntity* data, float dt); //Replace with T
StateFunction FSM_Update(StateMachine* fsm, GameEntity* data, float dt);


// Init, Set currState, send function pointer to States.init
#endif