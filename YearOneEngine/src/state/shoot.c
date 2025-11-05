#include "shoot.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "utils/container.h"
#include "tile/tile.h"
#include "utils/bullet.h"
#include <stdio.h>
void B_Arr_Refresh(BulletArr* array, GameEntity* turret) {
	
	for (int i = 0; i < array->used; i++) {

		
		array->bulletArr[i].centerPos.x = turret->centerPos.x;
		array->bulletArr[i].centerPos.y = turret->centerPos.y;
		array->bulletArr[i].opacity = 255;
		printf("%d %f", turret->bullets.bulletArr[i].id, turret->bullets.bulletArr[i].opacity);
	}
}

void Shoot_Init( GameEntity* turret, StateMachine* SM, float dt) 
{
	

	B_Arr_Refresh(&(turret->bullets.bulletArr), turret);
}

void Shoot_Update(GameEntity* turret, StateMachine* SM, float dt) {
	turret->stateTimer += dt;
	static float shootSpan = 1.0;

	if (turret->stateTimer >= shootSpan) {
		turret->stateTimer = 0;
		Bullet b = { .id = 0, .centerPos = turret->centerPos, .velocity = {1,0}, .color = {0,255,0,255}, .diameter = 5 };
		B_Arr_Insert(&(turret->bullets), b);
	}
	for (int i = 0; i < turret->bullets.used; i++) {
		Bullet* bullet = &turret->bullets.bulletArr[i];
		bullet->isActive = TRUE; 
		CP_Vector acc = { 10,0 };
		
			//spawn bullet
			bullet->velocity = CP_Vector_Add(bullet->velocity, acc);
			bullet->centerPos = CP_Vector_Add(bullet->centerPos, CP_Vector_Scale(bullet->velocity, dt));
			//Move bullet
			/*bullet->velocity = CP_Vector_Add(bullet->velocity, acc);
			entity->centerPos = CP_Vector_Add(entity->centerPos, CP_Vector_Scale(entity->velocity, dt));*/
			if (bullet->centerPos.x >= CP_System_GetWindowWidth()) {
				B_Arr_Del(&(turret->bullets), bullet->id);
			}
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