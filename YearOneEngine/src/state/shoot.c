#include "shoot.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "utils/container.h"
#include "tile/tile.h"


void Shoot_Init(GameEntity* turret, Bullet* bullet, float dt) {

}

void Shoot_Update(GameEntity* turret, Bullet* bullet, float dt) {
	bullet->isActive = TRUE;

	if (bullet->isActive) {
		//spawn bullet
		bullet->centerPos = turret->centerPos;

		//Move bullet
		bullet->centerPos.x += 10.0f * dt;

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

void Shoot_Exit(GameEntity* turret, Bullet* bullet, float dt) {

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