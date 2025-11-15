#include "utils/SM.h"

extern States EnemyIdleState;
extern States EnemyPickUpState;
extern States EnemySelectedState;

void Enemy_IdleInit(GameEntity* entity, StateMachine* sm, float dt);
void Enemy_IdleUpdate(GameEntity* entity, StateMachine* sm, float dt);
void Enemy_IdleExit(GameEntity* entity, StateMachine* sm, float dt);

void Enemy_PickedUpInit(GameEntity* entity, StateMachine* sm, float dt);
void Enemy_PickedUpUpdate(GameEntity* entity, StateMachine* sm, float dt);
void Enemy_PickedUpExit(GameEntity* entity, StateMachine* sm, float dt);

void Enemy_SelInit(GameEntity* entity, StateMachine* sm, float dt);
void Enemy_SelUpdate(GameEntity* entity, StateMachine* sm, float dt);
void Enemy_SelExit(GameEntity* entity, StateMachine* sm, float dt);
