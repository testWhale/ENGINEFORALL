//---------------------------------------------------------
// file:	pickup.h
// author:	[Zachary Ng]
// email:	zacharyhuaen.n@digipen.edu
//
// brief:	Declares the player pickup/selection states and helpers.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "utils/SM.h"

extern States IdleState;
extern States PickUpState;
extern States SelectedState;

/* Idle_Init()
Input:
    GameEntity* entity - entity entering idle
    StateMachine* SM - owning state machine
    float dt - delta time
Output:
    void
Brief:
    Prepares colors/timer for the idle state.
*/
void Idle_Init(GameEntity* entity, StateMachine* SM, float dt);

/* Idle_Update()
Input:
    GameEntity* entity - idle entity
    StateMachine* SM - its machine
    float dt - delta time
Output:
    void
Brief:
    Updates timers and switches to pickup when appropriate.
*/
void Idle_Update(GameEntity* entity, StateMachine* SM, float dt);

/* Idle_Exit()
Input:
    GameEntity* entity - leaving idle
    StateMachine* SM - its machine
    float dt - delta time
Output:
    void
Brief:
    Placeholder for idle exit cleanup.
*/
void Idle_Exit(GameEntity* entity, StateMachine* SM, float dt);

/* PickedUp_Init()
Input:
    GameEntity* entity - entity being picked up
    StateMachine* SM - its machine
    float dt - delta time
Output:
    void
Brief:
    Assigns pickup indices and prepares the drag visuals.
*/
void PickedUp_Init(GameEntity* entity, StateMachine* SM, float dt);

/* PickedUp_Update()
Input:
    GameEntity* entity - dragging entity
    StateMachine* SM - its machine
    float dt - delta time
Output:
    void
Brief:
    Follows the mouse, handles placement, and transitions back.
*/
void PickedUp_Update(GameEntity* entity, StateMachine* SM, float dt);

/* PickedUp_Exit()
Input:
    GameEntity* entity - finishing pickup
    StateMachine* SM - its machine
    float dt - delta time
Output:
    void
Brief:
    Resets entity state and plays the place sound.
*/
void PickedUp_Exit(GameEntity* entity, StateMachine* SM, float dt);

/* Sel_Init()
Input:
    GameEntity* entity - entity being selected
    StateMachine* SM - its machine
    float dt - delta time
Output:
    void
Brief:
    Clears other selections and marks this entity as active.
*/
void Sel_Init(GameEntity* entity, StateMachine* SM, float dt);

/* Sel_Update()
Input:
    GameEntity* entity - selected entity
    StateMachine* SM - its machine
    float dt - delta time
Output:
    void
Brief:
    Keeps the selection active until the user clicks away.
*/
void Sel_Update(GameEntity* entity, StateMachine* SM, float dt);

/* Sel_Exit()
Input:
    GameEntity* entity - entity leaving selection
    StateMachine* SM - its machine
    float dt - delta time
Output:
    void
Brief:
    Drops selection flags and clears hover highlights.
*/
void Sel_Exit(GameEntity* entity, StateMachine* SM, float dt);

