#include "wave.h"
#include "tile/tile.h"
#include <stdlib.h>
#include <time.h>
wave = 0;
waveFlag = 0;
waveState = 0;

/* Start_Wave()
Input: Either player or enemy pointer
Output: pointer to the GameEntity */
GameEntity* Start_Wave(GameEntity* entity, float dt) {
	int rndm = rand() % TILE_ROWS;
	int tes=rndm;
	if (tes == rndm) { rndm = rand() % TILE_ROWS;  }
	
	entity->centerPos.y = g_TileMap[rndm][TILE_COLUMNS-1].centerPos.y;
	entity->centerPos.x = g_TileMap[rndm][(rand() % TILE_COLUMNS)].centerPos.x ;
	entity->centerPos.x += 2000;

}

/* MoveWave()
Input: Either player or enemy 
Output: pointer to the GameEntity */
GameEntity* Move_Wave(GameEntity* entity, float dt) {
	 
	int rndm = rand() % 99;
	CP_Vector acc = { -4 * dt,0 };
	
	if (rndm == 4) { 
		acc.x = -1;
		entity->velocity = CP_Vector_Add(entity->velocity, acc);
		entity->centerPos = CP_Vector_Add(entity->centerPos, CP_Vector_Scale(entity->velocity, dt));
		return 1;
	}

	if (rndm == 3) {
		acc.x = -1;
		entity->velocity = CP_Vector_Add(entity->velocity, acc);
		entity->centerPos = CP_Vector_Add(entity->centerPos, CP_Vector_Scale(entity->velocity, dt));
		return 1;
	}

	entity->velocity = CP_Vector_Add(entity->velocity, acc);
	entity->centerPos = CP_Vector_Add(entity->centerPos,CP_Vector_Scale(entity->velocity, dt));
}
