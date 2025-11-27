//---------------------------------------------------------
// file:	wave.h
// author:	[Zachary Ng]
// email:	[zacharyhuaen.n@digipen.edu]
//
// brief:	declaration for wave functions and enemy speeds in each wave
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "../arr.h"
extern int wave;
extern int waveFlag;
extern float waveState;

/* Start_Wave()
Input:
    GameEntity* entity - entity to position before the wave begins
    float dt - reserved delta time value (currently unused)
Output:
    GameEntity* pointer after assigning spawn tile and velocity characteristics
Brief:
    Initializes an entity so it can enter the active wave with randomized lane/texture/acceleration.
*/
GameEntity* Start_Wave(GameEntity* entity, float dt);

/* Move_Wave()
Input:
    GameEntity* entity - entity whose motion should advance
    float dt - seconds since the last frame
Output:
    GameEntity* pointer after updating center position
Brief:
    Steps the entity forward by adding acceleration to its velocity and translating it across the level.
*/
GameEntity* Move_Wave(GameEntity* entity, float dt);

/* Draw_WaveCounter()
Input:
    None
Output:
    void
Brief:
    Draws the current wave number overlay at the top of the screen.
*/
void Draw_WaveCounter();