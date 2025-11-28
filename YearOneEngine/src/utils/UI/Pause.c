//---------------------------------------------------------
// file: pause.c
// author: Xavier Lim
// email: yipfengxavier.lim@digipen.edu
//
// brief: Implements the Pause system.
//   - Provides pause toggle and overlay rendering
//   - Handles pause/resume/menu buttons
//   - Integrates volume slider control
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "pause.h"
#include "cprocessing.h"
#include "buttons/buttonCode.h"
#include "scenes/mainmenu.h"
#include "scenes/settings.h"

/* Sound Settings */
extern float volume;
extern float masterVolume;
CP_Font myFont;

static int s_paused = 0;  // pause state flag
static int s_menuRequest = 0; // menu request flag
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

/* Pause_IsPaused()
Input:
    None
Output:
    int - 1 if paused, 0 otherwise
Description:
    - Returns current pause state
*/

int Pause_IsPaused(void) { return s_paused; }

/* Pause_SetPaused()
Input:
    on - 1 to enable pause, 0 to disable
Output:
    None
Description:
    - Sets pause state explicitly
*/

void Pause_SetPaused(int on) { s_paused = (on != 0); }

/* Pause_Dt()
Input:
    dt - delta time (seconds)
Output:
    float - adjusted delta time
Description:
    - Returns 0.0f if paused
    - Returns original delta time if not paused
*/

float Pause_Dt(float dt) { return s_paused ? 0.0f : dt; }

/* Pause_TakeMenuRequest()
Input:
    None
Output:
    int - menu request flag
Description:
    - Checks if player requested to open pause menu
    - Resets flag after returning
*/

int Pause_TakeMenuRequest(void) { int r = s_menuRequest; s_menuRequest = 0; return r; }

Slider slider; // volume slider

/* Pause_Init()
Input:
    None
Output:
    None
Description:
    - Initializes pause system state
    - Loads button assets and overlay
    - Creates volume slider
*/

void Pause_Init(void)
{
    const float H = (float)CP_System_GetWindowHeight();
    const float W = (float)CP_System_GetWindowWidth();
    unit = H / 100.0f;
    
    Button_Sound_Load(&s_pauseSound,
        "Assets/Sound_Effects/ClickSound.wav",
        "Assets/Sound_Effects/hoverSound.mp3",
        "Assets/Sound_Effects/ReleaseSound.wav");
    unit = CP_System_GetWindowWidth() / 192.0f;
    Button_Load(&s_btnPause, &s_pauseSound,
        (W / unit - 2.5f - 3.0f) * unit, (2.5f + 3.0f) * unit,
        6.0f * unit, 6.0f * unit, 0.0f,
        PAUSE_N, PAUSE_H, PAUSE_C, 1);

    Button_Load(&s_btnResume, &s_pauseSound,
        97.0f * unit, 49.0f * unit,
        23.0f * unit, 8.0f * unit, 0.0f,
        RESUME_N, RESUME_H, RESUME_C, 1);

    Button_Load(&s_btnMenu, &s_pauseSound,
        97.0f * unit, 63.0f * unit,
        23.0f * unit, 8.0f * unit, 0.0f,
        MENU_N, MENU_H, MENU_C, 1);

    // Pause overlay and font where all button will be at.
    s_overlay = CP_Image_Load("Assets/Buttons/pause/PauseOverlay.png");
    myFont = CP_Font_Load("Assets/Fonts/QuinnDoodle.ttf");

    // Centered slider
    float sliderWidth = 2000;
    float sliderHeight = 300;
    float sliderX = (292 * unit / 2) - (sliderWidth / 2);
    float sliderY = 80 * unit;
    Slider_Create(&slider, sliderX, sliderY, sliderWidth, sliderHeight, &volume, 0.0f, 1.0f, "Assets/Sound/Sound.png");

}

/* Pause_UpdateAndDraw()
Input:
    None
Output:
    None
Description:
    - Updates pause system logic
    - Draws pause overlay, buttons, and volume slider
    - Handles button clicks for resume and menu
*/

void Pause_UpdateAndDraw(void)
{
    float W = (float)CP_System_GetWindowWidth();
    float H = (float)CP_System_GetWindowHeight();
    float cx = W * 0.5f;
    float cy = H * 0.5f;
    float buttonScale = 0.58f;

    // If not paused, only update pause button
    if (!s_paused)
    {
        Button_Behavior(&s_btnPause);
        if (s_btnPause.isClicked) { s_paused = 1; s_btnPause.isClicked = 0; }
        return;
    }

    CP_Settings_ImageMode(CP_POSITION_CENTER);
    CP_Image_Draw(s_overlay, cx, cy, 65 * unit, 85 * unit, 255);

    int nativeW = CP_Image_GetWidth(s_btnResume.buttonNormal);
    int nativeH = CP_Image_GetHeight(s_btnResume.buttonNormal);

    // Scale buttons based on artwork size
    s_btnResume.buttonWidth = nativeW * buttonScale;
    s_btnResume.buttonHeight = nativeH * buttonScale;
    s_btnMenu.buttonWidth = nativeW * buttonScale;
    s_btnMenu.buttonHeight = nativeH * buttonScale;

    Button_Behavior(&s_btnResume);
    Button_Behavior(&s_btnMenu);

    float sliderWidth = 300;
    float sliderX = (192 * unit / 2) - (sliderWidth / 2);
    slider.x = sliderX;
    slider.y = 60 * unit; // vertical position
    slider.width = sliderWidth;

    Slider_Draw(&slider);
    char volumeText[32];
    sprintf_s(volumeText, sizeof(volumeText), "Volume: %.2f", volume);
    CP_Settings_TextSize(34.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText(volumeText, slider.x + 140, slider.y + 200);
    // Update master volume
    masterVolume = volume;
    CP_Sound_SetGroupVolume(0, masterVolume); // assuming group 0 is your main sound group
    CP_Sound_SetGroupVolume(1, masterVolume);

    if (s_btnResume.isClicked) { s_paused = 0; s_btnResume.isClicked = 0; }
    if (s_btnMenu.isClicked) { s_menuRequest = 1; s_btnMenu.isClicked = 0; s_paused = 0; }
}


/* Pause_Exit()
Input:
    None
Output:
    None
Description:
    - Cleans up pause system resources
    - Resets pause state and menu request
*/

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
