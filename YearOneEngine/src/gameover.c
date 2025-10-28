#include "cprocessing.h"
#include "gameover.h"
#include "test.h"       
#include "mainmenu.h"   
#include <math.h>
#include <stdio.h>


static float GO_finalTime = 0.0f;
static int   GO_goals = 0;
static float GO_timer = 0.0f;
static float GO_fade = 0.0f;

static CP_Sound KO; 
static CP_Font  GO_font;

void GameOver_SetData(float finalTime, int goals) {
    GO_finalTime = finalTime;
    GO_goals = goals;
}

void GameOver_Init(void) {
    GO_timer = 0.0f;
    GO_fade = 0.0f;

    GO_font = CP_Font_Load("Assets/Exo2-Regular.ttf");
    if (GO_font) CP_Font_Set(GO_font);

    KO = CP_Sound_Load("Assets/Game Over Arcade by myfox14 Id-382310.wav");
    CP_Sound_Play(KO);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

void GameOver_Update(void) {
    const float dt = CP_System_GetDt();
    GO_timer += dt;

    GO_fade += 220.0f * dt;
    if (GO_fade > 200.0f) GO_fade = 200.0f;

    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();

    // Dark overlay
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)GO_fade));
    CP_Graphics_DrawRect(0, 0, W, H);

    // Title
    CP_Settings_Fill(CP_Color_Create(235, 235, 235, 255));
    CP_Settings_TextSize(72.0f);
    CP_Font_DrawText("GAME OVER", W * 0.5f, H * 0.35f);

    // Stats
    char line[64];
    CP_Settings_TextSize(36.0f);
    snprintf(line, sizeof(line), "Time: %.0f s", GO_finalTime);
    CP_Font_DrawText(line, W * 0.5f, H * 0.48f);
    snprintf(line, sizeof(line), "Money earn: %d", GO_goals);
    CP_Font_DrawText(line, W * 0.5f, H * 0.55f);

    // Prompt (blink)
    float blink = 0.5f + 0.5f * sinf(6.0f * GO_timer);
    int alpha = (int)(130 + 100 * blink);
    CP_Settings_Fill(CP_Color_Create(230, 230, 230, alpha));
    CP_Settings_TextSize(28.0f);
    CP_Font_DrawText("Press R to Retry   |   Press M for Menu", W * 0.5f, H * 0.68f);

    // Accept input after a short delay
    if (GO_timer > 0.6f) {
        if (CP_Input_KeyTriggered(KEY_R) || CP_Input_KeyTriggered('R')) {
            CP_Engine_SetNextGameState(Game_Init, Game_Update, Game_Exit);
            return;
        }
        if (CP_Input_KeyTriggered(KEY_M) || CP_Input_KeyTriggered('M')) {
            CP_Engine_SetNextGameState(MainMenu_Init, MainMenu_Update, MainMenu_Exit);
            return;
        }
    }
}

void GameOver_Exit(void) {
    CP_Font_Free(&GO_font);
    CP_Sound_Free(KO);
}
