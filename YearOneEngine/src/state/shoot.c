//---------------------------------------------------------
// file:	shoot.c
// author:	[Zachary Ng][Ding Yi Chaw Maung]
// email:	[zacharyhuaen.n@digipen.edu][dingyichaw.maung@digipen.edu]
//
// brief:	contains the Shoot State definitions 
//			of the player unit.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "shoot.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "tile/tile.h"
#include "bullet/bullet.h"
#include <stdio.h>
#include "utils/wave/wave.h"


/* AreCirclesIntersecting()
Input:
	Bullet* bullet     - pointer to the bullet
	GameEntity* enemy  - positional data of enemy

Output:
	Returns the StateFunction.

Breif: 
	Used inside of the shoot state to check if 
	the enemy is in contact with the bullet.
*/
int AreCirclesIntersecting(Bullet* bullet, GameEntity* enemy) {
	CP_Vector vec_c1 = CP_Vector_Set(bullet->centerPos.x, bullet->centerPos.y);
	CP_Vector vec_c2 = CP_Vector_Set(enemy->centerPos.x, enemy->centerPos.y);

	return (bullet->diameter / 2.0f + enemy->diameter / 2.0f) >= CP_Vector_Distance(vec_c1, vec_c2);
}

/* B_Arr_Refresh()
Input:
	Bullet* bullet     - pointer to the bullet
	GameEntity* turret  - positional data of turret
Output:
	NA.
Breif:
	Used inside of PickUpExit to magnetise the bullets to the specific turrets 
	position. Making it visible and ready to be shot.
*/
void B_Arr_Refresh(BulletArr* array, GameEntity* turret) {
	
	for (int i = 0; i < array->used; i++) {
		array->bulletArr[i].centerPos.x = turret->centerPos.x;
		array->bulletArr[i].centerPos.y = turret->centerPos.y;
		array->bulletArr[i].opacity = 255;
		printf("%d %f", turret->bullets.bulletArr[i].id, turret->bullets.bulletArr[i].opacity);
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

/* Shoot_Update()
Input:
	GameEntity* turret     - pointer to the turret
	StateMachine* SM  - State of the turret
	float dt		- deltaTime
Output:
	NA.
Breif:
	Run inside game Loop, creates the bullet and tracks its position, 
	Using Bullet_Template to 
*/
void Shoot_Update(GameEntity* turret, StateMachine* SM, float dt) {
	turret->stateTimer += dt;
	static float shootSpan;
	Bullet b;
		if (turret->label == "poison") {
			b = Bullet_Template("poison");

			shootSpan = 4.0;
	}
		if (turret->label == "stun") {
			b = Bullet_Template("stun");

			shootSpan = 2.0;
	}
		if (turret->label == "fire") {
			b = Bullet_Template("normal");

			shootSpan = 1.0;
	}
	
	int crossedLine = 0;
	int turretRow = (turret->centerPos.y - g_TileMap[0][0].startPos.y) / g_TileMap[0][0].dim.y;

	if (Is_Circle_Clicked(turret->centerPos.x, turret->centerPos.y, turret->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		//FSM_SetState(SM, SelectedState, turret, dt);
		return;
	}

	for (int i = 0; i < enemyArr.used; i++) {
		GameEntity* enemy = &enemyArr.ActiveEntityArr[i].unit;
		int enemyRow = (enemy->centerPos.y - g_TileMap[0][0].startPos.y) / g_TileMap[0][0].dim.y;
			if (enemyRow == turretRow && EnemyCrossedLine(&enemyArr.ActiveEntityArr[i].unit)) {
				crossedLine = 1;
				break;
		}
	}

	if (crossedLine && turret->stateTimer >= shootSpan) {
		turret->stateTimer = 0;
		
		b.centerPos = turret->centerPos;
		B_Arr_Insert(&(turret->bullets), b);
		
	}
	
		for (int i = 0; i < turret->bullets.used; i++) {
			 /* Bullets that are currently being shot */
			Bullet* bullet = &turret->bullets.bulletArr[i];
			CP_Vector acc = { 10,0 };
		
				//spawn bullet
				bullet->velocity = CP_Vector_Add(bullet->velocity, acc);
				//Move bullet
				bullet->centerPos = CP_Vector_Add(bullet->centerPos, CP_Vector_Scale(bullet->velocity, dt));
				
					if (bullet->centerPos.x >= CP_System_GetWindowWidth()) {
					printf("DEL\n");
						B_Arr_Del(&(turret->bullets), bullet->id);
					}
			
				//loop through all enemies and check if they are being hit 
				for (int j = 0; j < enemyArr.used; j++) {
					GameEntity* enemy = &enemyArr.ActiveEntityArr[j].unit;
					
				
				/* Check if enemy is intersecting with bullet*/
					if (AreCirclesIntersecting(bullet, enemy)) {
						{ enemy->color.red = 255; enemy->color.green = 0; enemy->color.blue = 0;   enemy->color.opacity = 255; }

						//poison effects, still checks for stun so the conditions dont overlap
						if (strcmp(bullet->type, "poison")==0) {
							if (!enemy->isPoisoned) {
								enemy->isPoisoned = 1;
								enemy->poisonDamage = bullet->poisonDmg;
								enemy->poisonTimerDecay = bullet->poisonDecayTimer;
								Health_PlayHitSfx();
								enemyArr.ActiveEntityArr[j].health -= enemy->poisonDamage * dt;
							}
							if (!enemy->isStunned) {
								enemyArr.ActiveEntityArr[j].health -= bullet->bulletDmg;
								enemy->isStunned = 1;
								enemy->stunTimer = bullet->stunTimer;
							}
						}

						//normal
						if (strcmp(bullet->type, "normal") == 0) {
							enemyArr.ActiveEntityArr[j].health -= bullet->bulletDmg;
							Health_PlayHitSfx();
						}

						//stun, checks for poison status effect as well
						if (strcmp(bullet->type, "stun") == 0) {
							if (!enemy->isStunned) {
								enemyArr.ActiveEntityArr[j].health -= bullet->bulletDmg;
								enemy->isStunned = 1;
								enemy->stunTimer = bullet->stunTimer;
							}
							if (!enemy->isPoisoned) {
								enemy->isPoisoned = 1;
								enemy->poisonDamage = bullet->poisonDmg;
								enemy->poisonTimerDecay = bullet->poisonDecayTimer;
								Health_PlayHitSfx();
								enemyArr.ActiveEntityArr[j].health -= enemy->poisonDamage * dt;
							}
						}

						//Deactivate bullet
						B_Arr_Del(&(turret->bullets), bullet->id);
						
						if (enemyArr.ActiveEntityArr[j].health <= 0.f) {
							Arr_Del(&enemyArr, enemyArr.ActiveEntityArr[j].id);
						}
					}



					if (enemy->isPoisoned) {
						enemyArr.ActiveEntityArr[j].health -= enemy->poisonDamage * dt;
						enemy->poisonTimerDecay -= dt;

						if (enemy->poisonTimerDecay <= 0) {
							enemy->isPoisoned = 0;
							enemy->poisonTimerDecay = 0;
						}
					}
				}
	}
	
}

void Shoot_Exit( GameEntity* turret, StateMachine* SM, float dt) {

}

States ShootState = {
	Shoot_Init,
	Shoot_Update,
	Shoot_Exit
};