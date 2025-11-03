#include "utils/SM.h"

extern States ShootState;
typedef struct {
	int id;
	CP_Vector centerPos, forwardVector;
	CP_BOOL isActive;
}Bullet;

void Shoot_Init(Bullet* bullet, StateMachine* SM, float dt);
void Shoot_Update(Bullet* bullet, StateMachine* SM, float dt);
void Shoot_Exit(Bullet* bullet, StateMachine* SM, float dt);
