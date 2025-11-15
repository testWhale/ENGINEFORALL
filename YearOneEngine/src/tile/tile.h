#ifndef TILE_H
#define TILE_H
#include "cprocessing.h"
#include "utils/SM.h"
#define TILE_ROWS 6
#define TILE_COLUMNS 9

typedef struct Offset {
	CP_Vector offset;
}Offset;

typedef struct Tile{
	CP_Vector centerPos;
	CP_Vector startPos;
	CP_Vector endPos;
	CP_Vector dim;
	GameEntity* entity;
	int hasEntity;
	int nextTileCheck;
	Color tcolor;
	int currHovered;
	int tsel;
}Tile;

extern Tile g_TileMap[TILE_ROWS][TILE_COLUMNS]; //declaration of one global instance of TileMap

Tile* Set_OnTile(GameEntity* Entity, CP_Vector mouse);
Tile* Hover_TileAt(GameEntity* Entity, CP_Vector mouse);
Tile* Hover_Tile_Exit();
Tile* Sel_AfterPlaced(GameEntity* Entity, CP_Vector mouse);

void Map_Init(CP_Vector startPos, float width, float height);

void Map_Update();


#endif