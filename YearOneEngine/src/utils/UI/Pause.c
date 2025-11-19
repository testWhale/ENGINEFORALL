#include "pause.h"
#include "Button/button.h"
#include "cprocessing.h"

static int s_paused = 0;
static int s_menuRequest = 0;

static ButtonInfo  s_btnPause;
static ButtonInfo  s_btnResume;
static ButtonInfo  s_btnMenu;
static ButtonSound s_pauseSound;

static float  s_unit = 1.0f;

static CP_Image s_overlay = 0;

#define PAUSE_N   "Assets/Buttons/pause/PauseNormal.png"
#define PAUSE_H   "Assets/Buttons/pause/PauseHighlight.png"
#define PAUSE_C   "Assets/Buttons/pause/PauseClicked.png"

#define RESUME_N  "Assets/Buttons/pause/ResumeNormal.png"
#define RESUME_H  "Assets/Buttons/pause/ResumeHovered.png"
#define RESUME_C  "Assets/Buttons/pause/ResumeClicked.png"

#define MENU_N    "Assets/Buttons/pause/MenuNormal.png"
#define MENU_H    "Assets/Buttons/pause/MenuHovered.png"
#define MENU_C    "Assets/Buttons/pause/MenuClicked.png"

#define OVERLAY_IMG "Assets/Buttons/pause/PauseOverlay.png"

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
        PAUSE_N, PAUSE_H, PAUSE_C,
        1);

    const float btnW = 34.0f * s_unit;
    const float btnH = 9.0f * s_unit;
    const float gap = 30.0f * s_unit;

    const float panelW = 120.0f * s_unit;
    const float panelH = 70.0f * s_unit;

    const float cx = 0.5f * W;
    const float cy = 0.5f * H;

    const float top = cy - panelH * 0.5f;
    const float resumeY = top + panelH * 0.62f;   
    const float menuY = top + panelH * 0.80f;

    Button_Load(&s_btnResume, &s_pauseSound,
        cx, resumeY,
        btnW, btnH,
        0.0f,
        RESUME_N, RESUME_H, RESUME_C, 
        1);

    Button_Load(&s_btnMenu, &s_pauseSound,
        cx, menuY,
        btnW, btnH,
        0.0f,
        MENU_N, MENU_H, MENU_C,         
        1);
 
    s_overlay = CP_Image_Load(OVERLAY_IMG); 
}

void Pause_UpdateAndDraw(void)
{
    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();

    if (!s_paused)
    {
        Button_Behavior(&s_btnPause);
        if (s_btnPause.isClicked) {
            s_paused = 1;
            s_btnPause.isClicked = 0;
        }
        return;
    }

    if (s_overlay) {                                  
        CP_Settings_ImageMode(CP_POSITION_CENTER);
        const float panelW = 120.0f * s_unit;
        const float panelH = 70.0f * s_unit;
        CP_Image_Draw(s_overlay, 0.5f * W, 0.5f * H, panelW, panelH, 255);
    }

    Button_Behavior(&s_btnResume);
    Button_Behavior(&s_btnMenu);

    if (s_btnResume.isClicked) {
        s_paused = 0;
        s_btnResume.isClicked = 0;
    }
    if (s_btnMenu.isClicked) {
        s_menuRequest = 1;
        s_btnMenu.isClicked = 0;
    }
}

void Pause_Exit(void)
{
    Button_Free(&s_btnPause);
    Button_Free(&s_btnResume);
    Button_Free(&s_btnMenu);
    Button_Sound_Free(&s_pauseSound);

    if (s_overlay) {                               
        CP_Image_Free(&s_overlay);
        s_overlay = 0;
    }
    s_paused = 0;
    s_menuRequest = 0;
    s_unit = 1.0f;
}
