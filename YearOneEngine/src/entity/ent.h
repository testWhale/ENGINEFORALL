#ifndef ENTITY_H
#define ENTITY_H

#include "../SM.h"

void Init_NewWave(int num);

GameEntity MakeTemplate(const char* name);

void initPlayerDemo();

void Draw_Text(float dt);

void PrintBulletInfo(GameEntity* entity);

void DrawEntities();

#endif