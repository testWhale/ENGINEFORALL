#include "utils/SM.h"

extern States ShootState;

void Shoot_Init(GameEntity* turret, StateMachine* SM, float dt);
void Shoot_Update(GameEntity* turret, StateMachine* SM, float dt);
void Shoot_Exit(GameEntity* turret, StateMachine* SM, float dt);
 