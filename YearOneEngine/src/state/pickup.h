#include "utils/SM.h"

extern States IdleState;
extern States PickUpState;
extern States SelectedState;

void Idle_Init(GameEntity* entity, StateMachine* SM, float dt);
void Idle_Update(GameEntity* entity, StateMachine* SM, float dt);
void Idle_Exit(GameEntity* entity, StateMachine* SM, float dt);

void PickedUp_Init(GameEntity* entity, StateMachine* SM, float dt);
void PickedUp_Update(GameEntity* entity, StateMachine* SM, float dt);
void PickedUp_Exit(GameEntity* entity, StateMachine* SM, float dt);

void Sel_Init(GameEntity* entity, StateMachine* SM, float dt);
void Sel_Update(GameEntity* entity, StateMachine* SM, float dt);
void Sel_Exit(GameEntity* entity, StateMachine* SM, float dt);

