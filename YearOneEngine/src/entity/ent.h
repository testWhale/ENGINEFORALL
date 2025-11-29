//---------------------------------------------------------
// file:	ent.h
// author:	[Zachary Ng][Ding Yi Chaw Maung]
// email:	[zacharyhuaen.n@digipen.edu][dingyichaw.maung@digipen.edu]
//
// brief:	Declarations for entity management, drawing, and cleanup helpers used across the state machine.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------
#ifndef ENTITY_H
#define ENTITY_H

#include "../SM.h"

/* Init_NewWave()
Input:
    int num - current wave index/scaling factor that determines enemy count
Output:
    void
Brief:
    Prepares the enemy container for a fresh wave by spawning templated enemies and tuning their stats.
*/
void Init_NewWave(int num);

/* Make_Template()
Input:
    const char* name - tag identifying the desired entity template
Output:
    GameEntity configured with default visuals/stats
Brief:
    Produces a prototype entity (player, enemy, poison, stun) used for populating arrays.
*/
GameEntity Make_Template(const char* name);

/* Init_PlayerDemo()
Input:
    None
Output:
    void
Brief:
    Creates the initial player/enemy units for demo mode and prepares their state machines.
*/
void Init_PlayerDemo();

/* Load_TempText()
Input:
    None
Output:
    void
Brief:
    Initializes the temporary UI buttons and tip timers around the new-wave prompt.
*/
void Load_TempText();

/* Draw_TempText()
Input:
    float dt - delta time to advance animations/timers
Output:
    void
Brief:
    Renders the temporary wave buttons, handles clicks, and shows timed tooltip messages.
*/
void Draw_TempText(float dt); 

/* Del_TempText()
Input:
    None
Output:
    void
Brief:
    Releases resources used by the temporary buttons once they are no longer needed.
*/
void Del_TempText();

/* Print_BulletInfo()
Input:
    GameEntity* entity - entity whose bullets should be logged or inspected
Output:
    void
Brief:
    Outputs diagnostic information about an entity's bullet array for debugging.
*/
void Print_BulletInfo(GameEntity* entity);

/* Draw_Entities()
Input:
    None
Output:
    void
Brief:
    Updates/draws players, enemies, shadows, health bars, and spawns new waves when needed.
*/
void Draw_Entities();

/* setup()
Input:
    char* imgPath - base texture path
    char* normPath - normal map texture path
Output:
    void
Brief:
    Preloads textures and precomputes lighting textures for the custom draw pipeline.
*/
void setup(const char* imgPath, const char* normPath);

/* draw()
Input:
    float x - world X coordinate
    float y - world Y coordinate
    float w - width for sprite rendering
    float h - height for sprite rendering
    int alpha - alpha blend value for drawing
Output:
    void
Brief:
    Draws to-screen textures using precomputed directional lighting based on mouse direction.
*/
void draw(float x, float y, float w, float h, int alpha);

/* clean()
Input:
    None
Output:
    void
Brief:
    Frees textures and buffers allocated during setup to avoid leaks.
*/
void clean();

/* Kill_NewWave()
Input:
    None
Output:
    void
Brief:
    Iterates through the enemy container and deletes each entry to clear the wave.
*/
void Kill_NewWave();

/* LateUpdate_Pickups()
Input:
    None
Output:
    void
Brief:
    Processes pending pickup removals, shifts remaining indices, and updates mouse state.
*/
void LateUpdate_Pickups();
#endif
