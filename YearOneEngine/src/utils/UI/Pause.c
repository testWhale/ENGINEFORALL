#include "pause.h"
#include "buttons/buttonCode.h"
#include "cprocessing.h"

static int s_paused = 0;
static int s_menuRequest = 0;

static ButtonInfo  s_btnPause;
static ButtonInfo  s_btnResume;
static ButtonInfo  s_btnMenu;
static ButtonSound s_pauseSound;

static CP_Image s_overlay = 0;
static float unit = 1.0f;

#define PAUSE_N   "Assets/Buttons/pause/PauseNormal.png"
#define PAUSE_H   "Assets/Buttons/pause/PauseHighlight.png"
#define PAUSE_C   "Assets/Buttons/pause/PauseClicked.png"

#define RESUME_N  "Assets/Buttons/pause/ResumeNormal.png"
#define RESUME_H  "Assets/Buttons/pause/ResumeHovered.png"
#define RESUME_C  "Assets/Buttons/pause/ResumeClicked.png"

#define MENU_N    "Assets/Buttons/pause/MenuNormal.png"
#define MENU_H    "Assets/Buttons/pause/MenuHovered.png"
#define MENU_C    "Assets/Buttons/pause/MenuClicked.png"

int   Pause_IsPaused(void) { return s_paused; }
void  Pause_SetPaused(int on) { s_paused = (on != 0); }
float Pause_Dt(float dt) { return s_paused ? 0.0f : dt; }
int   Pause_TakeMenuRequest(void) { int r = s_menuRequest; s_menuRequest = 0; return r; }

void Pause_Init(void)
{
    const float H = (float)CP_System_GetWindowHeight();
    const float W = (float)CP_System_GetWindowWidth();
    unit = H / 100.0f;

    Button_Sound_Load(&s_pauseSound,
        "Assets/soundTesters/ClickSound.wav",
        "Assets/soundTesters/HoverSound.wav",
        "Assets/soundTesters/ReleaseSound.wav");

    Button_Load(&s_btnPause, &s_pauseSound,
        (W / unit - 2.5f - 3.0f) * unit, (2.5f + 3.0f) * unit,
        6.0f * unit, 6.0f * unit, 0.0f,
        PAUSE_N, PAUSE_H, PAUSE_C, 1);

    Button_Load(&s_btnResume, &s_pauseSound,
        50.0f * unit, 49.0f * unit,
        23.0f * unit, 8.0f * unit, 0.0f,
        RESUME_N, RESUME_H, RESUME_C, 1);

    Button_Load(&s_btnMenu, &s_pauseSound,
        50.0f * unit, 59.0f * unit,
        23.0f * unit, 8.0f * unit, 0.0f,
        MENU_N, MENU_H, MENU_C, 1);

    s_overlay = CP_Image_Load("Assets/Buttons/pause/PauseOverlay.png");
}

void Pause_UpdateAndDraw(void)
{
    float W = (float)CP_System_GetWindowWidth();
    float H = (float)CP_System_GetWindowHeight();
    float cx = W * 0.5f;
    float cy = H * 0.5f;
    float buttonScale = 0.58f;
    if (!s_paused)
    {
        Button_Behavior(&s_btnPause);
        if (s_btnPause.isClicked) { s_paused = 1; s_btnPause.isClicked = 0; }
        return;
    }

    CP_Settings_ImageMode(CP_POSITION_CENTER);
    CP_Image_Draw(s_overlay, cx, cy, 0.652f * H, 0.639f * H, 255);

    int nativeW = CP_Image_GetWidth(s_btnResume.buttonNormal);
    int nativeH = CP_Image_GetHeight(s_btnResume.buttonNormal);

    // Apply size to both buttons (assuming same artwork size)
    s_btnResume.buttonWidth = nativeW * buttonScale;
    s_btnResume.buttonHeight = nativeH * buttonScale;
    s_btnMenu.buttonWidth = nativeW * buttonScale;
    s_btnMenu.buttonHeight = nativeH * buttonScale;

    // --- positioning (pixel offsets from screen center) ---
    // Put RESUME just under the "PAUSE" title
    s_btnResume.buttonPos.x = cx;
    s_btnResume.buttonPos.y = cy + 0.04f * H;   // move up/down by tweaking this (e.g., -0.10f * H)

    // Gap between buttons
    float gap = 0.020f * H;  // make smaller/bigger as you like

    // MENU sits below RESUME
    s_btnMenu.buttonPos.x = cx;
    s_btnMenu.buttonPos.y = s_btnResume.buttonPos.y + s_btnResume.buttonHeight + gap;

    Button_Behavior(&s_btnResume);
    Button_Behavior(&s_btnMenu);

    if (s_btnResume.isClicked) { s_paused = 0; s_btnResume.isClicked = 0; }
    if (s_btnMenu.isClicked) { s_menuRequest = 1; s_btnMenu.isClicked = 0; }
}


void Pause_Exit(void)
{
    Button_Free(&s_btnPause);
    Button_Free(&s_btnResume);
    Button_Free(&s_btnMenu);
    Button_Sound_Free(&s_pauseSound);
    s_overlay = 0;
    s_paused = 0;
    s_menuRequest = 0;
    unit = 1.0f;
}
