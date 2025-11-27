//---------------------------------------------------------
// file: nuke.c
// author: Xavier Lim, Ding Yi Chaw Maung
// email: yipfengxavier.lim@digipen.edu, dingyichaw.maung@digipen.edu
//
// brief: Endgame scene, for when the player wins
//   - Displays falling nuke animation
//   - Triggers staged explosion visuals and sounds
//   - Transitions back to main menu after final stage
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "nuke.h"
#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "scenes/mainmenu.h"

static float nukeX, nukeY;             // position of the nuke
static float nukeDropSpeed = 80.0f;    // falling speed
static int explosionStage = 0;         // current explosion stage
static float explosionTimer = 0.0f;    // timer for explosion stage transitions
static CP_Sound drop;                  // drop sound
static CP_Sound boom;                  // first explosion sound
static CP_Sound boom2;                 // second explosion sound
static CP_Image nuke, explode;         // images for nuke and explosion

/* Nuke_Init()
Input:
    None
Output:
    None
Description:
    - Loads images and sounds for the nuke drop and explosion
    - Sets initial position of the nuke
    - Plays drop sound effect
*/

void Nuke_Init(void) {
    nuke = CP_Image_Load("Assets/Misc/Nuke.jpg");
    explode = CP_Image_Load("Assets/Misc/explosion.jpg");
    nukeX = 1920 / 2.0f;   // center horizontally
    nukeY = 0.0f;          // start at top
    drop = CP_Sound_Load("Assets/soundTesters/Designed, Tonal, Bomb, Falling, WWII SND7490.wav");
    boom = CP_Sound_Load("Assets/soundTesters/Huge Explosion by CGEffex Id-93834.wav");
    boom2 = CP_Sound_Load("Assets/soundTesters/Huge Explosion Part 1   Shockwave by bevibeldesign Id-366091.wav");
    CP_Sound_SetGroupVolume(0, 2.0f);
    CP_Sound_Play(drop);
}

/* Nuke_Update()
Input:
    None
Output:
    None
Description:
    - Updates nuke position until impact
    - Triggers explosion stages with timed growth and sound effects
    - After final stage, switches game state to main menu
*/

void Nuke_Update(void) {
    float dt = CP_System_GetDt();
    CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

    // Stage 0: falling nuke
    if (explosionStage == 0) {
        float scale = 0.3f;
        CP_Image_Draw(nuke, nukeX, nukeY, 791 * scale, 1204 * scale, 255);
        nukeY += nukeDropSpeed * dt; // move down

        // Impact point reached
        if (nukeY >= 540) {
            explosionStage = 1;
            explosionTimer = 0.0f;
            CP_Sound_Play(boom); // play first explosion sound
        }
        return;
    }

    // Explosion stages
    explosionTimer += dt;
    float explosionSizes[] = { 300, 600, 900 };
    CP_Image_Draw(explode, nukeX, nukeY,
        explosionSizes[explosionStage - 1],
        explosionSizes[explosionStage - 1], 255);

    // Advance explosion stages every 0.8s
    if (explosionTimer > 0.8f) {
        explosionStage++;
        explosionTimer = 0.0f;

        if (explosionStage == 2) {
            CP_Sound_Play(boom2); // play secondary explosion sound
        }

        // After final stage, return to main menu
        if (explosionStage > 3) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

/* Nuke_Exit()
Input:
    None
Output:
    None
Description:
    - Frees loaded images and sounds
    - Cleans up resources used by the nuke system
*/

void Nuke_Exit(void) {
    CP_Image_Free(&nuke);
    CP_Image_Free(&explode);
    CP_Sound_Free(drop);
    CP_Sound_Free(boom);
    CP_Sound_Free(boom2);
}