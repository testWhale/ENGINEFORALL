#include "pause.h"
#include "Button/button.h"
#include "cprocessing.h"

static int s_paused = 0;
static int s_menuRequest = 0;

static buttonInfo s_btnPause;
static buttonInfo s_btnResume;
static buttonInfo s_btnMenu;

static float s_unit = 1.0f;

#define PAUSE_N   "Assets/buttons/pause normal.png"
#define PAUSE_H   "Assets/buttons/pause hover.png"
#define PAUSE_C   "Assets/buttons/pause clicked.png"

#define RESUME_N  "Assets/buttons/resume normal.jpg"
#define RESUME_H  "Assets/buttons/resume hover.jpg"
#define RESUME_C  "Assets/buttons/resume clicked.jpg"

#define MENU_N    "Assets/buttons/menu normal.jpg"
#define MENU_H    "Assets/buttons/menu hover.jpg"
#define MENU_C    "Assets/buttons/menu clicked.jpg"

int   Pause_IsPaused(void) { return s_paused; }
void  Pause_SetPaused(int on) { s_paused = (on != 0); }
float Pause_Dt(float dt) { return s_paused ? 0.0f : dt; }
int   Pause_TakeMenuRequest(void) { int r = s_menuRequest; s_menuRequest = 0; return r; }

void Pause_Init(void)
{
    s_paused = 0;
    s_menuRequest = 0;

    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();

    s_unit = H / 100.0f;  

    const float iconSize = 6.0f * s_unit;
    const float margin = 2.5f * s_unit;

    const float pauseX = W - margin - iconSize * 0.5f;
    const float pauseY = margin + iconSize * 0.5f;

    buttonLoad(&s_btnPause,
        pauseX, pauseY,
        iconSize, iconSize,
        0.0f,
        PAUSE_N, PAUSE_C, PAUSE_H);

    const float cx = 0.5f * W;
    const float cy = 0.5f * H;

    const float btnW = 45.0f * s_unit;   
    const float btnH = 13.0f * s_unit;
    const float gap = 8.0f * s_unit;   

    const float resumeY = cy - 5.0f * s_unit;          
    const float menuY = resumeY + btnH + gap;      

    buttonLoad(&s_btnResume,
        cx, resumeY,
        btnW, btnH, 0.0f,
        RESUME_N, RESUME_C, RESUME_H);

    buttonLoad(&s_btnMenu,
        cx, menuY,
        btnW, btnH, 0.0f,
        MENU_N, MENU_C, MENU_H);
}

void Pause_UpdateAndDraw(void)
{
    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();
    (void)H;

    if (!s_paused)
    {
        buttonBehavior(&s_btnPause);
        if (s_btnPause.isClicked) {
            s_paused = 1;
            s_btnPause.isClicked = 0;
        }
        return;
    }

    const float panelW = 120.0f * s_unit;
    const float panelH = 70.0f * s_unit;
    const float cx = 0.5f * W;
    const float cy = 0.5f * H;

    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_Fill(CP_Color_Create(25, 25, 25, 230));
    CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 35));
    CP_Settings_StrokeWeight(2.0f);
    CP_Graphics_DrawRect(cx, cy, panelW, panelH);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(240, 240, 240, 255));
    CP_Settings_TextSize(30.0f);
    CP_Font_DrawText("PAUSED", cx, cy - panelH * 0.5f + 8.0f * s_unit);

    // ---------- buttons ----------
    buttonBehavior(&s_btnResume);
    buttonBehavior(&s_btnMenu);

    CP_Settings_ImageMode(CP_POSITION_CENTER);

    CP_Image_Draw(s_btnResume.buttonNormal,
        s_btnResume.buttonPos.x, s_btnResume.buttonPos.y,
        s_btnResume.buttonWidth, s_btnResume.buttonHeight, 255);

    CP_Image_Draw(s_btnMenu.buttonNormal,
        s_btnMenu.buttonPos.x, s_btnMenu.buttonPos.y,
        s_btnMenu.buttonWidth, s_btnMenu.buttonHeight, 255);

    if (s_btnResume.isClicked) {
        s_paused = 0;
        s_btnResume.isClicked = 0;
    }

    if (s_btnMenu.isClicked) {
        s_menuRequest = 1;
        s_btnMenu.isClicked = 0;
    }

    CP_Settings_RectMode(CP_POSITION_CENTER);
}
