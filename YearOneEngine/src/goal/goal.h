#ifndef GOAL_H
#define GOAL_H

#include "cprocessing.h"
#include "tile/tile.h"  
#include "health.h"      

#define GOAL_COUNT 6

void Goal_InitFromTileMap(float radiusScale, float marginScale);

void ProcessGoalHits(HealthSystem* hs);

void Goal_DebugDraw(void);


#endif
