#include "utils/SM.h"

extern States Enemy_IdleState;
extern States Enemy_PickUpState;
extern States Enemy_SelectedState;

void Enemy_IdleInit(GameEntity* entity, StateMachine* SM, float dt);
void Enemy_IdleUpdate(GameEntity* entity, StateMachine* SM, float dt);
void Enemy_IdleExit(GameEntity* entity, StateMachine* SM, float dt);

void Enemy_PickedUpInit(GameEntity* entity, StateMachine* SM, float dt);
void Enemy_PickedUpUpdate(GameEntity* entity, StateMachine* SM, float dt);
void Enemy_PickedUpExit(GameEntity* entity, StateMachine* SM, float dt);

void Enemy_SelInit(GameEntity* entity, StateMachine* SM, float dt);
void Enemy_SelUpdate(GameEntity* entity, StateMachine* SM, float dt);
void Enemy_SelExit(GameEntity* entity, StateMachine* SM, float dt);
