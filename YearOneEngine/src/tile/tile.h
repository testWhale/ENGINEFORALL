#ifndef TILE_H
#define TILE_H
#include "cprocessing.h"
#include "utils/SM.h"
#define TILE_ROWS 6
#define TILE_COLUMNS 12
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
void Map_Init();
void Map_Update();
Tile* setOnTile(GameEntity* Entity, CP_Vector mouse);
Tile* hoverTileAt(GameEntity* Entity, CP_Vector mouse);
Tile* hoverTileExit();
Tile* SelAfterPlaced(GameEntity* Entity, CP_Vector mouse);

#endif