#include "tile.h"
#include "cprocessing.h"
#include "utils/SM.h"
Tile g_TileMap[TILE_ROWS][TILE_COLUMNS];

void Map_Init() {
	float scrn_width, scrn_height;
	scrn_width = CP_System_GetWindowWidth(); scrn_height = CP_System_GetWindowHeight();
	float t_width = scrn_width / TILE_COLUMNS; float t_height = scrn_height / TILE_ROWS;
	float s_width = 0; float s_height = 0; CP_Vector startPoint = { 0,0 }; CP_Vector centerPos = { 0,0 };

	for (int i = 0; i < TILE_ROWS; i++) {
		s_width = startPoint.x; s_height = startPoint.y;
		centerPos.y = (startPoint.y + (t_height / 2));
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(startPoint.x, startPoint.y, 10);

		for (int j = 0; j < TILE_COLUMNS; j++) {
			g_TileMap[i][j].startPos.x = startPoint.x;
			g_TileMap[i][j].startPos.y = startPoint.x;
			g_TileMap[i][j].endPos.y = startPoint.x;

			startPoint.x += t_width;
			g_TileMap[i][j].endPos.x = startPoint.x;

			centerPos.x = (startPoint.x - (t_width / 2));
			g_TileMap[i][j].centerPos = centerPos;
			g_TileMap[i][j].dim = (CP_Vector){ t_width , t_height };
			g_TileMap[i][j].entity = NULL;
			g_TileMap[i][j].hasEntity = 0;
			g_TileMap[i][j].nextTileCheck = NULL;
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawCircle(startPoint.x, startPoint.y, 10);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawCircle(centerPos.x, centerPos.y, 10);
		}
	
		startPoint.y += t_height; s_height += t_height;	
		/*CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
		CP_Graphics_DrawLine(s_width, s_height, startPoint.x, startPoint.y);*/
		startPoint.x = 0; centerPos.x = 0; 
	}
}

Tile* getTileAt(GameEntity* Entity,CP_Vector mouse) {
	int row = mouse.y / g_TileMap[0][0].dim.y;
	int col = mouse.x / g_TileMap[0][0].dim.x;
	Tile* c_tile = &g_TileMap[row][col];
	if (row < 0 || row >= TILE_ROWS || col < 0 || col >= TILE_COLUMNS) {
		printf("ERROR");
	}
	if (1 == c_tile->hasEntity) {
		printf("Cannot Place Unit Here.\n");
		CP_Settings_Fill(CP_Color_Create(150, 150, 255, 255));
		Entity->centerPos = (CP_Vector){0,0};
		return NULL;
	}
	if (1 == c_tile->nextTileCheck) {
		printf("Cannot Place, Enemy Too Close.\n");
		Entity->centerPos = (CP_Vector){ 0,0 };
		return NULL;
	}
	else{
		c_tile->hasEntity = 1;
		Entity->isItActive = 1;
		Entity->centerPos = c_tile->centerPos;
		c_tile->entity = Entity;
	}
}

void Map_Update() {
	for (int i = 0; i < TILE_ROWS; i++) {
		for (int j = 0; j < TILE_COLUMNS; j++) {
			Tile* c_tile = &g_TileMap[i][j];
		
			//CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			//CP_Graphics_DrawCircle(startPoint.x, startPoint.y, 10);
			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
			CP_Graphics_DrawCircle(c_tile->centerPos.x, c_tile->centerPos.y, 10);
			CP_Graphics_DrawRect(c_tile->centerPos.x, c_tile->centerPos.y, c_tile->dim.x - 2, c_tile->dim.y - 2);
		}
	}
};