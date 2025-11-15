#include "cprocessing.h"
#include "gameover.h"
#include "scenes/mainscene.h"   
#include "mainmenu.h"
#include <math.h>
#include <stdio.h>

static int   GO_wave = 0;     
static float GO_finalTime = 0.0f;  
static float GO_money = 0.0f; 

static float GO_timer = 0.0f;
static float GO_fade = 0.0f;

static CP_Sound KO = 0;
static CP_Font  GO_font = 0;

void GameOver_SetData(float finalTime, float money) //add in int waveSurvived once code is read
{
    //GO_wave = waveSurvived;
    GO_finalTime = finalTime;
    GO_money = money;
}

void GameOver_Init(void) {
    GO_timer = GO_fade = 0.0f;
    GO_font = CP_Font_Load("Assets/Exo2-Regular.ttf");
    if (GO_font) CP_Font_Set(GO_font);
    KO = CP_Sound_Load("Assets/Game Over Arcade by myfox14 Id-382310.wav");
    CP_Sound_Play(KO);
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
}

void GameOver_Update(void) {
    const float dt = CP_System_GetDt();
    GO_timer += dt;
    GO_fade += 220.0f * dt; if (GO_fade > 200.0f) GO_fade = 200.0f;

    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)GO_fade));
    CP_Graphics_DrawRect(0, 0, W, H);

    CP_Settings_Fill(CP_Color_Create(235, 235, 235, 255));
    CP_Settings_TextSize(72.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText("GAME OVER", W * 0.5f, H * 0.35f);

    char line[64];
    CP_Settings_TextSize(36.0f);

    (void)snprintf(line, sizeof(line), "Wave survived: %f", GO_money); //Go_wave
    CP_Font_DrawText(line, W * 0.5f, H * 0.45f);

    (void)snprintf(line, sizeof(line), "Time: %.0f s", GO_finalTime);
    CP_Font_DrawText(line, W * 0.5f, H * 0.52f);

    (void)snprintf(line, sizeof(line), "Money: %.0f$", GO_money);
    CP_Font_DrawText(line, W * 0.5f, H * 0.59f);

    float blink = 0.5f + 0.5f * sinf(6.0f * GO_timer);
    int alpha = (int)(130 + 100 * blink);
    CP_Settings_Fill(CP_Color_Create(230, 230, 230, alpha));
    CP_Settings_TextSize(28.0f);
    CP_Font_DrawText("Press R to Retry   |   Press M for Menu", W * 0.5f, H * 0.68f);

    if (GO_timer > 0.6f) {
        if (CP_Input_KeyTriggered(KEY_R) || CP_Input_KeyTriggered('R')) {
            CP_Engine_SetNextGameState(Main_Scene_Init, Main_Scene_Update, Main_Scene_Exit);
            return;
        }
        if (CP_Input_KeyTriggered(KEY_M) || CP_Input_KeyTriggered('M')) {
            CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
            return;
        }
    }
}


void GameOver_Exit(void) {
    if (GO_font) CP_Font_Free(GO_font);
    CP_Sound_Free(KO);
}
