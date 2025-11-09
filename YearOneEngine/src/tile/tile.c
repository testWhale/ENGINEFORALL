#include "tile.h"
#include "cprocessing.h"
#include "utils/SM.h"
#include "buttons/buttonCode.h"
Tile g_TileMap[TILE_ROWS][TILE_COLUMNS];
Offset off;

/*---------------------------------MAP_INIT FUNCTION-----------------------------*/
void Map_Init(CP_Vector startPos, float width, float height) {
	float scrnW = width;
	float scrnH = height;

	float t_width = scrnW / TILE_COLUMNS;
	float t_height = scrnH / TILE_ROWS;

	CP_Vector startPoint = { startPos.x, startPos.y };
	CP_Vector centerPos = { 0, 0 };

	off = (Offset){ .offset.x = width, .offset.y = height };

	for (int i = 0; i < TILE_ROWS; i++) {
		startPoint.x = startPos.x; // reset x at the start of each row
		centerPos.y = startPoint.y + (t_height / 2);

		for (int j = 0; j < TILE_COLUMNS; j++) {
			// Set tile start and end positions
			g_TileMap[i][j].startPos.x = startPoint.x;
			g_TileMap[i][j].startPos.y = startPoint.y;

			g_TileMap[i][j].endPos.x = startPoint.x + t_width;
			g_TileMap[i][j].endPos.y = startPoint.y + t_height;

			// Set center position
			centerPos.x = startPoint.x + (t_width / 2);
			g_TileMap[i][j].centerPos = centerPos;

			// Set dimensions and default values
			g_TileMap[i][j].dim = (CP_Vector){ t_width, t_height };
			g_TileMap[i][j].entity = NULL;
			g_TileMap[i][j].hasEntity = 0;
			g_TileMap[i][j].nextTileCheck = NULL;
			g_TileMap[i][j].tcolor = WHITE;
			g_TileMap[i][j].currHovered = 0;

			// Optional debug visuals
			CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			CP_Graphics_DrawCircle(startPoint.x, startPoint.y, 10);
			startPoint.x += t_width;
		}

		//printf("ROW NUM: %d\n", i);
		startPoint.y += t_height;
	}
}



/*---------------------------------Check TILE FUNCTIONS-----------------------------*/
Tile* setOnTile(GameEntity* Entity, CP_Vector mouse) {
	float y = mouse.y - g_TileMap[0][0].startPos.y;
	float x = mouse.x - g_TileMap[0][0].startPos.x;
	if (y < 0 || x < 0) { return; }
	int row = (y) / g_TileMap[0][0].dim.y;
	
	int col = (x) / g_TileMap[0][0].dim.x;
	printf("ROW NOT GOOD: %d %d", row, col);
	printf("The Value %f %f", mouse.x - g_TileMap[0][0].startPos.x, mouse.y - g_TileMap[0][0].startPos.y);
	if (row < 0 || row > TILE_ROWS || col < 0 || col > TILE_COLUMNS) {  return 0; }
	Tile* c_tile = &g_TileMap[row][col];

	if (row < 0 || row >= TILE_ROWS || col < 0 || col >= TILE_COLUMNS) {
		//printf("Out of Bounds\n");
		return;
	}
	if (1 == c_tile->hasEntity) {
		printf("Cannot Place Unit Here.\n");
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		Entity->centerPos = (CP_Vector){ 0,0 };
		return NULL;
	}
	if (1 == c_tile->nextTileCheck) {
		printf("Cannot Place, Enemy Too Close.\n");
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		Entity->centerPos = (CP_Vector){ 0,0 };
		return NULL;
	}
	else {
		c_tile->hasEntity = 1;
		Entity->isItOnMap = 1;
		/*printf("CENTERPOS %d\n", c_tile->centerPos);
		printf("Tile %d %d\n", row, col);*/

		Entity->centerPos = c_tile->centerPos; //magnetise entity to tile
		c_tile->entity = Entity; //in case tile needs entity data give it
	}
}

/*---------------------------------HOVER FUNCTIONS-----------------------------*/
Tile* hoverTileAt(GameEntity* Entity, CP_Vector mouse) {
	//reset all tileMaps to 0 first
	for (int i = 0; i < TILE_ROWS; i++) {
		for (int j = 0; j < TILE_COLUMNS; j++) {
			g_TileMap[i][j].currHovered = 0;
		}
	}
	if (mouse.x < g_TileMap[0][0].startPos.x) mouse.x = g_TileMap[0][0].startPos.x;
	if (mouse.y < g_TileMap[0][0].startPos.y) mouse.y = g_TileMap[0][0].startPos.y;
	if (mouse.x > g_TileMap[0][TILE_COLUMNS - 1].startPos.x) mouse.x = g_TileMap[0][TILE_COLUMNS - 1].startPos.x;
	if (mouse.y > g_TileMap[TILE_ROWS - 1][0].startPos.y) mouse.y = g_TileMap[TILE_ROWS - 1][0].startPos.y;

	int row = (mouse.y - g_TileMap[0][0].startPos.y) / g_TileMap[0][0].dim.y;
	int col = (mouse.x - g_TileMap[0][0].startPos.x) / g_TileMap[0][0].dim.x;
	if (row < 0 || row >= TILE_ROWS || col < 0 || col >= TILE_COLUMNS) {
		//printf("ERROR"Z);
		return;
	}
	Tile* c_tile = &g_TileMap[row][col];
	c_tile->currHovered = 1;

	return c_tile;
}
Tile* hoverTileExit() {
	for (int i = 0; i < TILE_ROWS; i++) {
		for (int j = 0; j < TILE_COLUMNS; j++) {
			g_TileMap[i][j].currHovered = 0;
			g_TileMap[i][j].tsel = 0;
		}
	}
}
Tile* SelAfterPlaced(GameEntity* Entity, CP_Vector mouse) {
	int row = mouse.y / g_TileMap[0][0].dim.y;
	int col = mouse.x / g_TileMap[0][0].dim.x;
	Tile* c_tile = &g_TileMap[row][col];
	c_tile->tsel = 1;
	if (row < 0 || row >= TILE_ROWS || col < 0 || col >= TILE_COLUMNS) {
		//printf("ERROR");
	}
}

/*---------------------------------MAP_UPDATE FUNCTIONS-----------------------------*/
void Map_Update() {
	for (int i = 0; i < TILE_ROWS; i++) {
		for (int j = 0; j < TILE_COLUMNS; j++) {
			Tile* c_tile = &g_TileMap[i][j];
			Color t_color = c_tile->tcolor;
			if (c_tile->currHovered || c_tile->tsel) {
				t_color = WHITISH;

			}
			else {
				t_color = REALLYCLEAR; // NOT HOVERED = WHITE
			}
			//CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
			//CP_Graphics_DrawCircle(startPoint.x, startPoint.y, 10);

			CP_Settings_Fill(CP_Color_Create(255, 255, 255, 150));
			//CP_Graphics_DrawCircle(c_tile->centerPos.x, c_tile->centerPos.y, 10);
			{ CP_Settings_Fill(CP_Color_Create(t_color.red, t_color.green, t_color.blue, t_color.opacity)); }
			CP_Graphics_DrawRect(c_tile->startPos.x, c_tile->startPos.y, c_tile->dim.x - 2, c_tile->dim.y - 2);
		}
	}
};