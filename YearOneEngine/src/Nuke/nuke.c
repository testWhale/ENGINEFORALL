#include "nuke.h"
#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"
#include "scenes/mainmenu.h"

static float nukeX, nukeY;
static float nukeDropSpeed = 80.0f;
static int explosionStage = 0;
static float explosionTimer = 0.0f;
static CP_Sound drop;
static CP_Sound boom;
static CP_Sound boom2;
static CP_Image nuke, explode;

void Nuke_Init(void) {
    nuke = CP_Image_Load("Assets/Misc/Nuke.jpg");
    explode = CP_Image_Load("Assets/Misc/explosion.jpg");
    nukeX = 1920 / 2.0f;
    nukeY = 0.0f;
    drop = CP_Sound_Load("Assets/soundTesters/Designed, Tonal, Bomb, Falling, WWII SND7490.wav");
    boom = CP_Sound_Load("Assets/soundTesters/Huge Explosion by CGEffex Id-93834.wav");
    boom2 = CP_Sound_Load("Assets/soundTesters/Huge Explosion Part 1   Shockwave by bevibeldesign Id-366091.wav");
    CP_Sound_SetGroupVolume(0, 2.0f);
    CP_Sound_Play(drop);
}

void Nuke_Update(void) {
    float dt = CP_System_GetDt();
    CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));

    if (explosionStage == 0) {
        float scale = 0.3f;
        CP_Image_Draw(nuke, nukeX, nukeY, 791 * scale, 1204 * scale, 255);
        nukeY += nukeDropSpeed * dt;

        if (nukeY >= 540) {
            explosionStage = 1;
            explosionTimer = 0.0f;
            CP_Sound_Play(boom);
        }
        return;
    }

    explosionTimer += dt;
    float explosionSizes[] = { 300, 600, 900 };
    CP_Image_Draw(explode, nukeX, nukeY, explosionSizes[explosionStage - 1], explosionSizes[explosionStage - 1], 255);

    if (explosionTimer > 0.8f) {
        explosionStage++;
        explosionTimer = 0.0f;
    if (explosionStage == 2) {
        CP_Sound_Play(boom2);
        }
    if (explosionStage > 3) {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        }
    }
}

void Nuke_Exit(void) {
    CP_Image_Free(&nuke);
    CP_Image_Free(&explode);
    CP_Sound_Free(drop);
    CP_Sound_Free(boom);
    CP_Sound_Free(boom2);
}