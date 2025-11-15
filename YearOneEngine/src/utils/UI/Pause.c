#include "pause.h"
#include "Button/button.h"
#include "cprocessing.h"

static int s_paused = 0;
static int s_menuRequest = 0;

static ButtonInfo s_btnPause;
static ButtonInfo s_btnResume;
static ButtonInfo s_btnMenu;
static ButtonSound s_pauseSound;

static float s_unit = 1.0f;

#define PAUSE_N   "Assets/Buttons/pause/pause normal.png"
#define PAUSE_H   "Assets/Buttons/pause/pause hover.png"
#define PAUSE_C   "Assets/Buttons/pause/pause clicked.png"

#define RESUME_N  "Assets/Buttons/pause/resume normal.jpg"
#define RESUME_H  "Assets/Buttons/pause/resume hover.jpg"
#define RESUME_C  "Assets/Buttons/pause/resume clicked.jpg"

#define MENU_N    "Assets/Buttons/pause/menu normal.jpg"
#define MENU_H    "Assets/Buttons/pause/menu hover.jpg"
#define MENU_C    "Assets/Buttons/pause/menu clicked.jpg"

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

    Button_Sound_Load(&s_pauseSound,
        "Assets/soundTesters/ClickSound.wav",
        "Assets/soundTesters/HoverSound.wav",
        "Assets/soundTesters/ReleaseSound.wav");

    const float iconSize = 6.0f * s_unit;
    const float margin = 2.5f * s_unit;

    const float pauseX = W - margin - iconSize * 0.5f;
    const float pauseY = margin + iconSize * 0.5f;

    Button_Load(&s_btnPause, &s_pauseSound,
        pauseX, pauseY,
        iconSize, iconSize,
        0.0f,
        PAUSE_N, PAUSE_C, PAUSE_H,
        1);

    const float cx = 0.5f * W;
    const float cy = 0.5f * H;

    const float btnW = 45.0f * s_unit;
    const float btnH = 13.0f * s_unit;
    const float gap = 8.0f * s_unit;

    const float resumeY = cy - 5.0f * s_unit;
    const float menuY = resumeY + btnH + gap;

    Button_Load(&s_btnResume, &s_pauseSound,
        cx, resumeY,
        btnW, btnH,
        0.0f,
        RESUME_N, RESUME_C, RESUME_H,
        1);

    Button_Load(&s_btnMenu, &s_pauseSound,
        cx, menuY,
        btnW, btnH,
        0.0f,
        MENU_N, MENU_C, MENU_H,
        1);
}

void Pause_UpdateAndDraw(void)
{
    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();
    (void)H;

    if (!s_paused)
    {
        Button_Behavior(&s_btnPause);
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

    Button_Behavior(&s_btnResume);
    Button_Behavior(&s_btnMenu);

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

void Pause_Exit(void)
{
    Button_Free(&s_btnPause);
    Button_Free(&s_btnResume);
    Button_Free(&s_btnMenu);
    Button_Sound_Free(&s_pauseSound);
    s_paused = 0;
    s_menuRequest = 0;
    s_unit = 1.0f;
}
