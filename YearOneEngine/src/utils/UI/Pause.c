#include "pause.h"
#include "cprocessing.h"
#include "buttons/buttonCode.h"
#include "scenes/mainmenu.h"
#include "scenes/settings.h"



static int s_paused = 0;
static int s_menuRequest = 0;

/* Sound Settings */
extern float volume;
extern float masterVolume;
CP_Font myFont;

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
Slider slider;

void Pause_Init(void)
{
    const float H = (float)CP_System_GetWindowHeight();
    const float W = (float)CP_System_GetWindowWidth();
    unit = H / 100.0f;
    
    Button_Sound_Load(&s_pauseSound,
        "Assets/soundTesters/ClickSound.wav",
        "Assets/soundTesters/HoverSound.wav",
        "Assets/soundTesters/ReleaseSound.wav");
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

    s_overlay = CP_Image_Load("Assets/Buttons/pause/PauseOverlay.png");
    myFont = CP_Font_Load("Assets/Fonts/QuinnDoodle.ttf");
    // Centered slider
    float sliderWidth = 2000;
    float sliderHeight = 300;
    float sliderX = (292 * unit / 2) - (sliderWidth / 2);
    float sliderY = 80 * unit;
    Slider_Create(&slider,sliderX, sliderY, sliderWidth, sliderHeight, &volume, 0.0f, 1.0f);

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
    CP_Image_Draw(s_overlay, cx, cy, 65 * unit, 85 * unit, 255);

    int nativeW = CP_Image_GetWidth(s_btnResume.buttonNormal);
    int nativeH = CP_Image_GetHeight(s_btnResume.buttonNormal);

    // Apply size to both buttons (assuming same artwork size)
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
