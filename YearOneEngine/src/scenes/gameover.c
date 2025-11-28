//---------------------------------------------------------
// file: gameover.c
// author: Xavier Lim
// email: yipfengxavier.lim@digipen.edu
//
// brief: Handles Game Over screen inclduing displaying 
//   final stats and retry/menu options.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------
#include "cprocessing.h"
#include "gameover.h"
#include "scenes/mainscene.h"   
#include "mainmenu.h"
#include "../wave/wave.h"
#include "economy/economyCode.h"
#include <math.h>
#include <stdio.h>
#include "clicker/clickCode.h"
   
//--------------------variables----------------------------- 
static float GO_finalTime = 0.0f;  
static float GO_money = 0.0f; 
static float GO_timer = 0.0f;
static float GO_fade = 0.0f;
static CP_Sound KO = 0;
static CP_Font  GO_font = 0;

/*GameOver_SetData()
Input:
    finalTime - time survived (seconds)
    money     - money earned
Output:
    None
Description:
    - Stores final values for display when the Game Over
    - screen initializes and draws.*/

void GameOver_SetData(float finalTime, float money) 
{
    GO_finalTime = finalTime;
    GO_money = money;
}

/* GameOver_Init()
Input:
    None
Output:
    None
Description:
    - Resets timers and fade
    - Loads and sets font
    - Loads and plays Game Over sound
    - Prepares drawing modes/alignment
*/

void GameOver_Init(void) {
    GO_timer = GO_fade = 0.0f;
    GO_font = CP_Font_Load("Assets/Fonts/Quinndoodle.ttf");
    if (GO_font) CP_Font_Set(GO_font);
    KO = CP_Sound_Load("Assets/Sound_Effects/Game Over Arcade by myfox14 Id-382310.wav");
    CP_Sound_Play(KO);
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

/* GameOver_Update()
Input:
    None (reads system dt and input)
Output:
    None (draws to screen; may trigger state change)
Description:
    - Advances fade and UI animation timer
    - Draws a dark overlay and "GAME OVER" title
    - Prints wave, time, and money
    - Shows a blinking instruction line
    - After some time it shows :
        R -> retry (back to main scene)
        M -> menu (main menu)
*/

void GameOver_Update(void) {
    const float dt = CP_System_GetDt();
    GO_timer += dt;
    GO_fade += 220.0f * dt; if (GO_fade > 200.0f) GO_fade = 200.0f;

    // Fade alpha increases over time (capped at 200)
    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();

    //black overlay to create a darken background effect
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)GO_fade));
    CP_Graphics_DrawRect(0, 0, W, H);

    // Game over title
    CP_Settings_Fill(CP_Color_Create(235, 235, 235, 255));
    CP_Settings_TextSize(72.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("GAME OVER", W * 0.5f, H * 0.35f);

    //--------------------stats----------------------------- 
    char line[64];
    CP_Settings_TextSize(36.0f);
    (void)snprintf(line, sizeof(line), "Wave survived: %d", wave); 
    CP_Font_DrawText(line, W * 0.5f, H * 0.45f);

    (void)snprintf(line, sizeof(line), "Time: %.0fs", GO_finalTime);
    CP_Font_DrawText(line, W * 0.5f, H * 0.52f);

    (void)snprintf(line, sizeof(line), "Money: $%.0f", GO_money);
    CP_Font_DrawText(line, W * 0.5f, H * 0.59f);

    // ---------------- Blinking instruction ----------------
    // Uses a sine wave to make alpha goes up and down between ~130–230
    // Creating a "press key" blinking effect
    float blink = 0.5f + 0.5f * sinf(6.0f * GO_timer);
    int alpha = (int)(130 + 100 * blink);
    CP_Settings_Fill(CP_Color_Create(230, 230, 230, alpha));
    CP_Settings_TextSize(28.0f);
    CP_Font_DrawText("Press R to Retry   |   Press M for Menu", W * 0.5f, H * 0.68f);

    //After 0.6s delay, allow player to retry or return to menu
    if (GO_timer > 0.6f) {
        if (CP_Input_KeyTriggered(KEY_R) || CP_Input_KeyTriggered('R')) {
            waveFlag = 0;
            CP_Engine_SetNextGameState(Main_Scene_Init, Main_Scene_Update, Main_Scene_Exit);
            return;
        }
        if (CP_Input_KeyTriggered(KEY_M) || CP_Input_KeyTriggered('M')) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
            return;
        }
    }
}

/* GameOver_Exit()
Input:
    None
Output:
    None
Description:
    - Resets wave counter
    - Frees loaded font 
    - Frees Game Over sound
    - Cleans up resources before leaving Game Over state
*/

void GameOver_Exit(void) {
    wave = 0;
    if (GO_font) CP_Font_Free(GO_font);
    CP_Sound_Free(KO);

}
