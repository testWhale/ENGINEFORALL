//---------------------------------------------------------
// file:	SM.c
// author:	Zachary Ng
// email:	zacharyhuaen.n@digipen.edu
//
// brief:	Contains definition of functions 
//			StateMachine.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "SM.h"
#include <string.h>
#include <stdio.h>

/* FSM_SetState()
Input:
    StateMachine* fsm     - pointer to the Entity's State
    GameEntity* data	  - positional data/ flags/ image/ sound data
    float dt			  - deltaTime

Output:
    Returns the StateFunction.

Brief:
    FSM_SetState takes ur currState in fsm and runs the exit function, 
    then it runs the newState Init() once.
*/
StateFunction FSM_SetState(StateMachine* fsm, States newState, GameEntity* data, float dt) {
	if (fsm->currState.Exit) {
		fsm->currState.Exit(data, fsm, dt);
	}
	fsm->currState = newState;
	fsm->currState.Init(data, fsm, dt);
}

/* FSM_Update()
Input:
    StateMachine* fsm     - pointer to the Entity's State
    GameEntity* data	  - positional data/ flags/ image/ sound data
    float dt			  - deltaTime

Output:
    Returns the StateFunction.

Brief:
    FSM_Update takes ur currState in fsm 
    and runs the Update function,
*/
StateFunction FSM_Update(StateMachine* fsm, GameEntity* data, float dt) {
    /*fsm->currState.Init(data, fsm, dt);*/
	fsm->currState.Update(data, fsm,dt);
}

/* FSM_Init()
Input:
    StateMachine* fsm     - pointer to the Entity's State
    GameEntity* data	  - positional data/ flags/ image/ sound data
    float dt			  - deltaTime

Output:
    Returns the StateFunction.

Brief:
    FSM_Init takes ur currState in fsm
    and runs the Init function,
*/
StateFunction FSM_Init(StateMachine* fsm, GameEntity* data, float dt) {
    fsm->currState.Init(data, fsm, dt);
}
