//---------------------------------------------------------
// file: goal.h
// author: Xavier Lim
// email: yipfengxavier.lim@digipen.edu
//
// brief:  Funcion declaration for goal system.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#ifndef GOAL_H
#define GOAL_H
#include "cprocessing.h"
#include "tile/tile.h"  
#include "health.h"      

#define GOAL_COUNT 6 // Have 6 goal objects to check for collision with enemy to deduct heart

void Goal_InitFromTileMap(float radiusScale, float marginScale);

void ProcessGoalHits(HealthSystem* hs);

#endif
