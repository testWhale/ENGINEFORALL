#include "wave.h"
#include "tile/tile.h"
#include <stdlib.h>
#include <time.h>
int tes = 0;
GameEntity* startWave(GameEntity* entity, int dt) {
	int rndm = rand() % TILE_ROWS;
	if (tes == rndm) { rndm = rand() % TILE_ROWS;  }
	tes = rndm; 
	printf("RNDM: %d %d\n", rndm, entity->id);
	printf("X POS: %d || Y POS: %d\n", entity->centerPos.x, entity->centerPos.y);
	printf("rndm=%d, tileY=%f\n", rndm, g_TileMap[rndm][11].centerPos.y);
	entity->centerPos.y = g_TileMap[rndm][11].centerPos.y;
	entity->centerPos.x = g_TileMap[rndm][(rand() % TILE_COLUMNS)].centerPos.x ;
	entity->centerPos.x += 1500;

}
GameEntity* moveWave(GameEntity* entity, float dt) {
	entity->centerPos.x -= 50 * dt * 2;

}
