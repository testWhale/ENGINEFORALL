#pragma once
#ifndef CON_STATES_H
#define CON_STATES_H

#include "../SM.h"
#include "../container.h"

extern States ConHiddenState;
extern States ConScrollState;
extern States ConIdleState;

void ConIdle_Init(Container* container, StateMachine* SM, float dt);
void ConIdle_Update(Container* container, StateMachine* SM, float dt);
void ConIdle_Exit(Container* container, StateMachine* SM, float dt);

void ConScrollIn_Init(Container* container, StateMachine* SM, float dt);
void ConScrollIn_Update(Container* container, StateMachine* SM, float dt);
void ConScrollIn_Exit(Container* container, StateMachine* SM, float dt);

void ConHidden_Init(Container* container, StateMachine* SM, float dt);
void ConHidden_Update(Container* container, StateMachine* SM, float dt);
void ConHidden_Exit(Container* container, StateMachine* SM, float dt);


#endif // !CON_STATES_H
