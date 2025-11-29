//---------------------------------------------------------
// file:	enemy.c
// author:	[Zachary Ng][Ding Yi Chaw Maung]
// email:	[zacharyhuaen.n@digipen.edu][dingyichaw.maung@digipen.edu]
//
// brief:	contains the Shoot State definitions 
//			of the player unit.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "enemy.h"
#include "tile/tile.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "./utils/SM.h"
/*---------------------------------IDLE CODE-----------------------------*/
void Enemy_IdleInit(GameEntity* entity, StateMachine* sm, float dt) {
	printf("Player entered IDLE::INIT state\n");
	entity->color.red = 255;
	entity->color.green = 255;
	entity->color.blue = 0;
	entity->stateTimer = 0.0f;

}
void Enemy_IdleUpdate(GameEntity* entity, StateMachine* sm, float dt) {
	entity->stateTimer += dt;
}
void Enemy_IdleExit(GameEntity* entity, StateMachine* sm, float dt) {
	printf("LEAVING IDLE state\n");
}

/*---------------------------------States Assigning-----------------------------*/
States EnemyIdleState = {
	Enemy_IdleInit,
	Enemy_IdleUpdate,
	Enemy_IdleExit
};

