#include "utils/SM.h"

extern States EnemyIdleState;

void Enemy_IdleInit(GameEntity* entity, StateMachine* sm, float dt);
void Enemy_IdleUpdate(GameEntity* entity, StateMachine* sm, float dt);
void Enemy_IdleExit(GameEntity* entity, StateMachine* sm, float dt);

