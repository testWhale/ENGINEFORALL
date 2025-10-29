#include "wave.h"
#include "tile/tile.h"
#include <stdlib.h>
#include <time.h>

GameEntity* startWave(GameEntity* entity, int dt) {
	int rndm = rand() % TILE_ROWS;
	int tes=rndm;
	if (tes == rndm) { rndm = rand() % TILE_ROWS;  }
	printf("RNDM: %d %d\n", rndm, entity->id);
	printf("X POS: %d || Y POS: %d\n", entity->centerPos.x, entity->centerPos.y);
	printf("rndm=%d, tileY=%f\n", rndm, g_TileMap[rndm][11].centerPos.y);
	entity->centerPos.y = g_TileMap[rndm][11].centerPos.y;
	entity->centerPos.x = g_TileMap[rndm][(rand() % TILE_COLUMNS)].centerPos.x ;
	entity->centerPos.x += 1500;

}
GameEntity* moveWave(GameEntity* entity, float dt) {
	/*srand(time(0));
	int rndm = rand() % ((TILE_ROWS - 1) - 0 + 1) + 0;
	printf("RNDM: %d\n", rndm);*/
	//entity->centerPos.y = g_TileMap[rndm][11].centerPos.y;
	//printf("ID:%d MOVING:%d\n", entity->id, entity->centerPos.x); 
	int rndm = rand() % 99;
	CP_Vector acc = { -4 * dt,0 };
	
	if (rndm == 4) {
		acc.x = -10;
		entity->velocity = CP_Vector_Add(entity->velocity, acc);
		entity->centerPos = CP_Vector_Add(entity->centerPos, CP_Vector_Scale(entity->velocity, dt));
		return 1;
	}
	if (rndm == 3) {
		acc.x = 10;
		entity->velocity = CP_Vector_Add(entity->velocity, acc);
		entity->centerPos = CP_Vector_Add(entity->centerPos, CP_Vector_Scale(entity->velocity, dt));
		return 1;
	}
	entity->velocity = CP_Vector_Add(entity->velocity, acc);
	entity->centerPos = CP_Vector_Add(entity->centerPos,CP_Vector_Scale(entity->velocity, dt));


}
