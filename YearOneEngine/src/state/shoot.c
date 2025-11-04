#include "shoot.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "utils/container.h"
#include "tile/tile.h"


void Shoot_Init( GameEntity* turret, StateMachine* SM, float dt) {
	printf("SHoort");
}

void Shoot_Update(GameEntity* turret, StateMachine* SM, float dt) {
	printf("ID: %d\n", turret->id);
	for (int i = 0; i < turret->bullets.used; i++) {
		Bullet* bullet = &turret->bullets.bulletArr[i];
		bullet->isActive = TRUE; 

		if (bullet->isActive) {
			//spawn bullet
			bullet->velocity.x = 100.0f * dt;
			bullet->centerPos = turret->centerPos;

			//Move bullet
			/*bullet->velocity = CP_Vector_Add(bullet->velocity, acc);
			entity->centerPos = CP_Vector_Add(entity->centerPos, CP_Vector_Scale(entity->velocity, dt));*/

			//// Check for collision with green circle
			//if (AreCirclesIntersecting(bullet_coord[0].x, bullet_coord[0].y, 40.0f,
			//	enemy_coord[0].x, enemy_coord[0].y, 80.0f) && length <= max_length && length >= min_length)
			//{
			//	//Deactivate bullet
			//	bullet->isActive = FALSE;
			//	//reduce health bar
			//	bullet_spawn = 0.0f;
			//}
		}
	}
	
}

void Shoot_Exit( GameEntity* turret, StateMachine* SM, float dt) {

}

/*---------------------------------States Assigning-----------------------------*/
//States IdleState = {
//	Idle_Init,
//	Idle_Update,
//	Idle_Exit
//};
//
//States PickUpState = {
//	PickedUp_Init,
//	PickedUp_Update,
//	PickedUp_Exit
//};
//
States ShootState = {
	Shoot_Init,
	Shoot_Update,
	Shoot_Exit
};