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

/* When called, place entity onto that tile, based on parameters mouse coords
* input: GameEntity* entity to place. CP_Vector mouse coords
* return: the tile that best matches the curr Mouse Coords. */
Tile* Set_OnTile(GameEntity* Entity, CP_Vector mouse);

/* When mouse hovers above tile, light that tile up. 
* input: GameEntity* entity to place. CP_Vector mouse coords
* return: A highlighted tile that best matches the curr Mouse Coords. */
Tile* Hover_TileAt(GameEntity* Entity, CP_Vector mouse);

/* When called all tiles are deselected. 
* input: GameEntity* entity to place. CP_Vector mouse coords
* return: the tile that best matches the curr Mouse Coords. */
Tile* Hover_Tile_Exit();

/* Set the tile that entity is on. c_tile->tsel = 1; */
void Sel_AfterPlaced(GameEntity* Entity, CP_Vector );

void Map_Init(CP_Vector startPos, float width, float height);

void Map_Update();
Tile* setOnTile(GameEntity* Entity, CP_Vector mouse);
Tile* hoverTileAt(GameEntity* Entity, CP_Vector mouse);
Tile* hoverTileExit();
Tile* SelAfterPlaced(GameEntity* Entity, CP_Vector mouse);

#endif