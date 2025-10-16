#include "utils/SM.h"

extern States IdleState;

extern States PickUpState;
extern States DamageState;
extern States SelectedState;

void PlayerIdle_Init(GameEntity* entity, StateMachine* SM, float dt);
void PlayerIdle_Update(GameEntity* entity, StateMachine* SM, float dt);
void PlayerIdle_Exit(GameEntity* entity, StateMachine* SM, float dt);

void PlayerAttack_Init(GameEntity* entity, StateMachine* SM, float dt);
void PlayerAttack_Update(GameEntity* entity, StateMachine* SM, float dt);
void PlayerAttack_Exit(GameEntity* entity, StateMachine* SM, float dt);

