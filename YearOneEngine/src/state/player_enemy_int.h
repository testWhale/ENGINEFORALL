#include "utils/SM.h"

extern States DamageState;
extern States ShootingState;

void _Init(GameEntity* entity, StateMachine* SM, float dt);
void PlayerIdle_Update(GameEntity* entity, StateMachine* SM, float dt);
void PlayerIdle_Exit(GameEntity* entity, StateMachine* SM, float dt);

void PlayerAttack_Init(GameEntity* entity, StateMachine* SM, float dt);
void PlayerAttack_Update(GameEntity* entity, StateMachine* SM, float dt);
void PlayerAttack_Exit(GameEntity* entity, StateMachine* SM, float dt);

