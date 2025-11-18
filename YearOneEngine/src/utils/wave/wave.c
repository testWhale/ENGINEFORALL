#include "wave.h"
#include "tile/tile.h"
#include "scenes/mainmenu.h"
#include <stdlib.h>
#include <time.h>
wave = 0;
waveFlag = 0;
waveState = 0;

/* Start_Wave()
Input: Either player or enemy pointer
Output: pointer to the GameEntity */
GameEntity* Start_Wave(GameEntity* entity, float dt) {
	// provides rdnm number till TILE_ROWS numbers range from 0-6
	int rndm = rand() % TILE_ROWS;
	int tes=rndm;
	if (tes == rndm) { rndm = rand() % TILE_ROWS;  }
	// when we set the enemy pos, we set btwen 0-5 index
	entity->centerPos.y = g_TileMap[rndm][TILE_COLUMNS-1].centerPos.y;
	entity->centerPos.x = g_TileMap[rndm][(rand() % TILE_COLUMNS)].centerPos.x ;
	entity->centerPos.x += 2000;
	
	/* This sets a random speed value for each enemy*/
	entity->accel = (CP_Vector){ (rand() % 10), 0 };
	if (entity->accel.x >= 1) {
		entity->accel.x *= 0.1;
	}
	if (entity->accel.x == 0) {
		entity->accel.x = 1;
	}

	entity->accel = CP_Vector_Negate(entity->accel);
	entity->velocity = CP_Vector_Add(entity->velocity, entity->accel);
	
	printf("Accel %f\n", entity->velocity.x);
}

/* MoveWave()
Input: Either player or enemy 
Output: pointer to the GameEntity */
GameEntity* Move_Wave(GameEntity* entity, float dt) {
	 
	entity->velocity = CP_Vector_Add(entity->velocity, entity->accel);
	entity->centerPos = CP_Vector_Add(entity->centerPos,CP_Vector_Scale(entity->velocity, dt));
}


void Draw_WaveCounter() {
	/* Draw Wave Counter */
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_TextSize(9 * unit);
	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	char label[64];
	sprintf_s(label, sizeof(label), "Wave Counter: %d", wave);
	CP_Font_DrawText(label, 120 * unit, 10 * unit);
}