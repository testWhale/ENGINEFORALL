#ifndef ENTITY_H
#define ENTITY_H

#include "../SM.h"

void Init_NewWave(int num);

GameEntity Make_Template(const char* name);

void Init_PlayerDemo();

void Load_TempText();

void Draw_TempText(float dt);

void Del_TempText();

void Print_BulletInfo(GameEntity* entity);

void Draw_Entities();

#endif