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
    StateMachine* fsm - state machine to switch
    States newState - state to become active
    GameEntity* data - entity data passed to state callbacks
    float dt - delta time
Output:
    StateFunction for the current state
Brief:
    Runs the old state's Exit, swaps in the new state, and runs its Init.
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
    StateMachine* fsm - machine being updated
    GameEntity* data - entity data for the state
    float dt - delta time
Output:
    StateFunction for the current state
Brief:
    Calls the current state's Update callback.
*/
StateFunction FSM_Update(StateMachine* fsm, GameEntity* data, float dt) {
    /*fsm->currState.Init(data, fsm, dt);*/
	fsm->currState.Update(data, fsm,dt);
}

/* FSM_Init()
Input:
    StateMachine* fsm - machine whose current state needs init
    GameEntity* data - data passed into callbacks
    float dt - delta time
Output:
    StateFunction for the current state
Brief:
    Runs the current state's Init callback.
*/
StateFunction FSM_Init(StateMachine* fsm, GameEntity* data, float dt) {
    fsm->currState.Init(data, fsm, dt);
}
