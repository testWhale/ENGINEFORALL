#ifndef GOAL_H
#define GOAL_H
#include "tile/tile.h"

CP_Vector g_goalCenters[TILE_ROWS];


float     g_enemyHitCD[1024];

extern int IsCircleClicked(float cx, float cy, float diameter, float mx, float my);

int CirclesOverlap(float x1, float y1, float r1, float x2, float y2, float r2);

void setGoal();

void DamageEnemiesOnPlayerCollisions(int dmgPerHit, float cd, float dt);

void ProcessGoalHits(void);

#endif // !1