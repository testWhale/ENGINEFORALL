//---------------------------------------------------------
// file:	shoot.h
// author:	[Zachary Ng][Ding Yi Chaw Maung]
// email:	[zacharyhuaen.n@digipen.edu][dingyichaw.maung@digipen.edu]
//
// brief:	Contains the declarations of Unit Shoot functions
//			
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "utils/SM.h"

extern States ShootState;

int AreCirclesIntersecting(Bullet* bullet, GameEntity* enemy);
void B_Arr_Refresh(BulletArr* array, GameEntity* turret);
void Shoot(GameEntity* turret, StateMachine* SM, float dt);
void Shoot_Init(GameEntity* turret, StateMachine* SM, float dt);
void Shoot_Update(GameEntity* turret, StateMachine* SM, float dt);
void Shoot_Exit(GameEntity* turret, StateMachine* SM, float dt);
