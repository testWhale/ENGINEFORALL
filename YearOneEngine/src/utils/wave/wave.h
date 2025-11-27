//---------------------------------------------------------
// file:	wave.h
// author:	[Zachary Ng][Ding Yi Chaw Maung]
// email:	[zacharyhuaen.n@digipen.edu][dingyichaw.maung@digipen.edu]
//
// brief:	declaration for wave functions and enemy speeds in each wave
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "../arr.h"
extern int wave;
extern int waveFlag;
extern float waveState;

GameEntity* Start_Wave(GameEntity* entity, float dt);
GameEntity* Move_Wave(GameEntity* entity, float dt);
void Draw_WaveCounter();