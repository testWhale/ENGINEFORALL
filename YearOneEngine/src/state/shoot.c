#include "shoot.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "utils/container.h"
#include "tile/tile.h"
#include "bullet/bullet.h"
#include <stdio.h>

int AreCirclesIntersecting(Bullet* bullet, GameEntity* enemy) {
	CP_Vector vec_c1 = CP_Vector_Set(bullet->centerPos.x, bullet->centerPos.y);
	CP_Vector vec_c2 = CP_Vector_Set(enemy->centerPos.x, enemy->centerPos.y);

	return (bullet->diameter / 2.0f + enemy->diameter / 2.0f) >= CP_Vector_Distance(vec_c1, vec_c2);
}


void B_Arr_Refresh(BulletArr* array, GameEntity* turret) {
	
	for (int i = 0; i < array->used; i++) {
		array->bulletArr[i].centerPos.x = turret->centerPos.x;
		array->bulletArr[i].centerPos.y = turret->centerPos.y;
		array->bulletArr[i].opacity = 255;
		//printf("%d %f", turret->bullets.bulletArr[i].id, turret->bullets.bulletArr[i].opacity);
	}
}

void Shoot(GameEntity* turret, StateMachine* SM, float dt)
{
	turret->stateTimer += dt;
	static float shootSpan = 1.0;
	if (turret->stateTimer >= shootSpan)
	{
		turret->stateTimer = 0;
		Bullet b = { .id = 0, .centerPos = turret->centerPos, .velocity = {1,0}, .color = {0,255,0,255}, .diameter = 50 };
		B_Arr_Insert(&(turret->bullets), b);
	}
	for (int i = 0; i < turret->bullets.used; i++)
	{ /* Bullets that are currently being shot */
		Bullet* bullet = &turret->bullets.bulletArr[i];
		CP_Vector acc = { 10,0 };

		//spawn bullet
		bullet->velocity = CP_Vector_Add(bullet->velocity, acc);
		bullet->centerPos = CP_Vector_Add(bullet->centerPos, CP_Vector_Scale(bullet->velocity, dt));
		//Move bullet

		/*if (bullet->type == "poison") {

		}
		if (bullet->type == "normal") {

		}
		if (bullet->type == "stun") {

		}*/

		if (bullet->centerPos.x >= CP_System_GetWindowWidth())
		{
			B_Arr_Del(&(turret->bullets), bullet->id);
		}
		//// Check for collision with green circle 

		//loop through all enemies and check if they are being hit
		for (int j = 0; j < enemyArr.used; j++)
		{
			GameEntity* enemy = &enemyArr.ActiveEntityArr[j].unit;
			/* Check if enemy is intersecting with bullet*/
			if (AreCirclesIntersecting(bullet, enemy))
			{
				B_Arr_Del(&(turret->bullets), bullet->id);
			}
		}

	}
}

void Shoot_Init( GameEntity* turret, StateMachine* SM, float dt) 
{
	
}


void Shoot_Update(GameEntity* turret, StateMachine* SM, float dt) {
	turret->stateTimer += dt;
	static float shootSpan = 1.0;
	if (IsCircleClicked(turret->centerPos.x, turret->centerPos.y, turret->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		//printf("STARTED ATTACK STATE FROM IDLE\n");
		/*deselectEnt();*/
		FSM_SetState(SM, SelectedState, turret, dt);
		return;
	}

	if (turret->stateTimer >= shootSpan) {
		turret->stateTimer = 0;
		Bullet b;
		if(turret->label == "poison"){
			printf("FYUCKECECWEC\n");
			b = Bullet_Template("poison");
		

		}
		if (turret->label == "stun") {
			b = Bullet_Template("stun");
		

		}
		if (turret->label == "fire") {
			b = Bullet_Template("normal");
			

		}
		b.centerPos = turret->centerPos;
		B_Arr_Insert(&(turret->bullets), b);
		//Bullet b = { .id = 0, .centerPos = turret->centerPos, .velocity = {1,0}, .color = {0,255,0,255}, .diameter = 50 };
	}

	for (int i = 0; i < turret->bullets.used; i++) 
	{ /* Bullets that are currently being shot */
		Bullet* bullet = &turret->bullets.bulletArr[i];
		CP_Vector acc = { 10,0 };
		
			//spawn bullet
			bullet->velocity = CP_Vector_Add(bullet->velocity, acc);
			bullet->centerPos = CP_Vector_Add(bullet->centerPos, CP_Vector_Scale(bullet->velocity, dt));
			//Move bullet

			/*if (bullet->type == "poison") {

			}
			if (bullet->type == "normal") {

			}
			if (bullet->type == "stun") {

			}*/

			/*bullet->velocity = CP_Vector_Add(bullet->velocity, acc);
			entity->centerPos = CP_Vector_Add(entity->centerPos, CP_Vector_Scale(entity->velocity, dt));*/
			if (bullet->centerPos.x >= CP_System_GetWindowWidth()) {
				//printf("DEL\n");
				B_Arr_Del(&(turret->bullets), bullet->id);
			}
			//// Check for collision with green circle 

			//loop through all enemies and check if they are being hit
			for (int j = 0; j < enemyArr.used; j++) {
				GameEntity* enemy = &enemyArr.ActiveEntityArr[j].unit;
				
				/*enemy->unit.centerPos = 
				printf("ID %d CenterPos %f\n", enemy->id,enemy->unit.centerPos.x);*/
				/* Check if enemy is intersecting with bullet*/
				if (AreCirclesIntersecting(bullet, enemy)) {
					{ enemy->color.red = 255; enemy->color.green = 0; enemy->color.blue = 0;   enemy->color.opacity = 255; }

					//Deactivate bullet
					enemyArr.ActiveEntityArr[j].health -= 60.0f;
					if (enemyArr.ActiveEntityArr[j].health <= 0.f) {
						Arr_Del(&enemyArr, enemyArr.ActiveEntityArr[j].id);
					}

					B_Arr_Del(&(turret->bullets), bullet->id);

				}

			}
				
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