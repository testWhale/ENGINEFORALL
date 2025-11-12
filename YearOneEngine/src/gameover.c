#include "gameover.h"
#include "test.h"
#include "mainmenu.h"
#include "cprocessing.h"

#include <stdio.h>
#include <math.h>

GameOverSystem gGameOver;

void GameOver_State_Init(void) {
    GameOver_Activate(&gGameOver);
}
void GameOver_State_Update(void) {
    GameOver_Update(&gGameOver);
    GameOver_Draw(&gGameOver);
}
void GameOver_State_Exit(void) {
    GameOver_Exit(&gGameOver); // free if your CP build needs it
}

void GameOver_Init(GameOverSystem* go)
{
    if (!go) return;

    go->isActive = 0;
    go->finalTime = 0.0f;
    go->goals = 0;
    go->fade = 0.0f;
    go->timer = 0.0f;

    
    go->font = CP_Font_Load("Assets/Exo2-Regular.ttf");
    if (go->font) {
        CP_Font_Set(go->font);
    }
    go->sound = CP_Sound_Load("Assets/Game Over Arcade by myfox14 Id-382310.wav");

    
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

void GameOver_SetData(GameOverSystem* go, float finalTime, int goals)
{
    if (!go) return;
    go->finalTime = finalTime;
    go->goals = goals;
}

void GameOver_Activate(GameOverSystem* go)
{
    if (!go) return;
    if (go->isActive) return;

    go->isActive = 1;
    go->fade = 0.0f;
    go->timer = 0.0f;

    CP_Sound_Play(go->sound);
}

void GameOver_Update(GameOverSystem* go)
{
    if (!go || !go->isActive) return;

    const float dt = CP_System_GetDt();
    go->timer += dt;

 
    go->fade += 220.0f * dt;
    if (go->fade > 200.0f) go->fade = 200.0f;

   
    if (go->timer > 0.6f) {
        if (CP_Input_KeyTriggered(KEY_R) || CP_Input_KeyTriggered('R')) {
            CP_Engine_SetNextGameState(Test_Init, Test_Update, Test_Exit);
            return;
        }
        if (CP_Input_KeyTriggered(KEY_M) || CP_Input_KeyTriggered('M')) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
            return;
        }
    }
}

void GameOver_Draw(const GameOverSystem* go)
{
    if (!go || !go->isActive) return;

    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();

    CP_Settings_RectMode(CP_POSITION_CORNER);

    CP_Settings_NoStroke();
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)go->fade)); 
    CP_Graphics_DrawRect(0, 0, W, H);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    if (go->font) CP_Font_Set(go->font);

    CP_Settings_Fill(CP_Color_Create(235, 235, 235, 255));
    CP_Settings_TextSize(72.0f);
    CP_Font_DrawText("GAME OVER", W * 0.5f, H * 0.35f);

    char line[64];
    CP_Settings_TextSize(36.0f);

    snprintf(line, sizeof(line), "Wave survived: %d", go->goals);
    CP_Font_DrawText(line, W * 0.5f, H * 0.45f);

    snprintf(line, sizeof(line), "Time: %.0f s", go->finalTime);
    CP_Font_DrawText(line, W * 0.5f, H * 0.52f);

    snprintf(line, sizeof(line), "Money earn: %d", go->goals);
    CP_Font_DrawText(line, W * 0.5f, H * 0.59f);

    const float blink = 0.5f + 0.5f * sinf(6.0f * go->timer);
    const int alpha = (int)(130.0f + 100.0f * blink);
    CP_Settings_Fill(CP_Color_Create(230, 230, 230, alpha));
    CP_Settings_TextSize(28.0f);
    CP_Font_DrawText("Press R to Retry   |   Press M for Menu", W * 0.5f, H * 0.68f);
}

void GameOver_Exit(GameOverSystem* go)
{
    if (!go) return;

    if (go->font) {
        CP_Font_Free(&go->font);
    }
    CP_Sound_Free(go->sound);

    go->isActive = 0;
}
