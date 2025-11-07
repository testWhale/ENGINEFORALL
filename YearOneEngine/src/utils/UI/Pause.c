#include "pause.h"
#include "Button/button.h"

static int s_paused = 0;   //if 0 game is running, if 1 game is pasued
static int s_menuRequest = 0;  // when click it become 1 and game can switch to main menu

static buttonInfo s_btnPause;   
static buttonInfo s_btnResume; 
static buttonInfo s_btnMenu;


//Assets for the buttons
#define PAUSE_N   "Assets/buttons/Pause normal.png"
#define PAUSE_H   "Assets/buttons/Pause hover.png"
#define PAUSE_C   "Assets/buttons/Pause clicked.png"

#define BTN_N     "Assets/buttons/button normal.png"
#define BTN_H     "Assets/buttons/button hover.png"
#define BTN_C     "Assets/buttons/button clicked.png"


int   Pause_IsPaused(void) { return s_paused; } 
void  Pause_SetPaused(int on) { s_paused = (on != 0); }
float Pause_Dt(float dt) { return s_paused ? 0.0f : dt; } //return 0 when pause so update code freeze
int   Pause_TakeMenuRequest(void) { int r = s_menuRequest; s_menuRequest = 0; return r; }

void Pause_Init(void)
{
    s_paused = 0;
    s_menuRequest = 0;

    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();
    (void)H;

    const float icon = 42.0f;

    const float cx = W - (icon * 0.5f) - 10.0f;
    const float cy = 10.0f + (icon * 0.5f);

    //button confriguration
    buttonLoad(&s_btnPause, cx, cy, icon, icon, 0.0f, PAUSE_N, PAUSE_C, PAUSE_H);
    buttonLoad(&s_btnResume, 0.0f, 0.0f, 200.0f, 48.0f, 0.0f, BTN_N, BTN_C, BTN_H);
    buttonLoad(&s_btnMenu, 0.0f, 0.0f, 200.0f, 48.0f, 0.0f, BTN_N, BTN_C, BTN_H);
}

void Pause_UpdateAndDraw(void)
{
    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();

    if (!s_paused)
    {
        buttonBehavior(&s_btnPause);
        if (s_btnPause.isClicked) {
            s_paused = 1;
            s_btnPause.isClicked = 0;
        }
        return;
    }

    //overlay panel
    const float panelW = 720.0f;   
    const float panelH = 360.0f;    
    const float cx = 0.5f * W;
    const float cy = 0.5f * H;

    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_Fill(CP_Color_Create(25, 25, 25, 230));
    CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 35));
    CP_Settings_StrokeWeight(2.0f);
    CP_Graphics_DrawRect(cx, cy, panelW, panelH);

   
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(240, 240, 240, 255));
    CP_Settings_TextSize(36.0f);
    CP_Font_DrawText("PAUSED", cx, cy - panelH * 0.5f + 70.0f);

   
    const float gap = 72.0f;

    s_btnResume.buttonWidth = 280.0f;
    s_btnResume.buttonHeight = 60.0f;
    s_btnMenu.buttonWidth = 280.0f;
    s_btnMenu.buttonHeight = 60.0f;

    s_btnResume.buttonPos.x = cx;
    s_btnResume.buttonPos.y = cy - 10.0f;
    s_btnMenu.buttonPos.x = cx;
    s_btnMenu.buttonPos.y = s_btnResume.buttonPos.y + s_btnResume.buttonHeight + gap;

    buttonBehavior(&s_btnResume);
    buttonBehavior(&s_btnMenu);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_TextSize(28.0f);
    CP_Font_DrawText("Resume", s_btnResume.buttonPos.x, s_btnResume.buttonPos.y);
    CP_Font_DrawText("Menu", s_btnMenu.buttonPos.x, s_btnMenu.buttonPos.y);

    if (s_btnResume.isClicked) { s_paused = 0; s_btnResume.isClicked = 0; }
    if (s_btnMenu.isClicked) { s_menuRequest = 1; s_btnMenu.isClicked = 0; }

    CP_Settings_RectMode(CP_POSITION_CENTER);
}

