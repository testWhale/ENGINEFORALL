#include "../arr.h"
extern int wave;
extern int waveFlag;
extern float waveState;

GameEntity* Start_Wave(GameEntity* entity, float dt);
GameEntity* Move_Wave(GameEntity* entity, float dt);
void Draw_WaveCounter();