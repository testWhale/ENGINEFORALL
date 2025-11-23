#include "cprocessing.h"
#include "buttons/buttonCode.h"
#include "mainmenu.h"
#include <stdbool.h>
#include <stdio.h>

bool settingsTabOpen = true;
float masterVolume = 1.0f;
extern int unit;

CP_Font myFont;
CP_Image MainMenuBackground;
ButtonInfo MuteButton;
ButtonSound defaultSound;
float volume = 0.5f;

typedef struct {
    float x, y;       // top-left of slider
    float width, height;
    float* value;     // pointer to controlled variable
    float minValue;
    float maxValue;
    bool dragging;
} Slider;
Slider s;
Slider Slider_Create(float x, float y, float width, float height, float* value, float minVal, float maxVal) {
    s.x = x;
    s.y = y;
    s.width = width;
    s.height = height;
    s.value = value;
    s.minValue = minVal;
    s.maxValue = maxVal;
    s.dragging = false;
    return s;
}

void Slider_Draw(Slider* s) {
    float mx = CP_Input_GetMouseX();
    float my = CP_Input_GetMouseY();
    bool mousePressed = CP_Input_MouseDown(0);

    // Clamp value
    if (*s->value < s->minValue) *s->value = s->minValue;
    if (*s->value > s->maxValue) *s->value = s->maxValue;

    // Normalized value (0..1)
    float t = (*s->value - s->minValue) / (s->maxValue - s->minValue);

    // Track
    float trackHeight = 30;
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(150, 150, 150, 255));
    CP_Graphics_DrawRect(s->x, s->y + s->height / 2 - trackHeight / 2, s->width, trackHeight);

    // Filled portion (expands only to the right)
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRect(s->x, s->y + s->height / 2 - trackHeight / 2, s->width * t, trackHeight);

    // Knob
    float knobSize = 50; // big knob
    float knobX = s->x + s->width * t;

    // Clamp knob inside bar
    if (knobX < s->x) knobX = s->x;
    if (knobX > s->x + s->width) knobX = s->x + s->width;
    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(knobX - knobSize / 2, s->y + s->height / 2 - knobSize / 2, knobSize, knobSize);

    // Input handling: drag knob or click on track
    bool overKnob = (mx >= knobX - knobSize / 2 && mx <= knobX + knobSize / 2 &&
        my >= s->y + s->height / 2 - knobSize / 2 && my <= s->y + s->height / 2 + knobSize / 2);

    bool overTrack = (mx >= s->x && mx <= s->x + s->width &&
        my >= s->y + s->height / 2 - trackHeight / 2 &&
        my <= s->y + s->height / 2 + trackHeight / 2);

    if (mousePressed && (overKnob || s->dragging || overTrack)) {
        s->dragging = true;
        float newT = (mx - s->x) / s->width;
        if (newT < 0) newT = 0;
        if (newT > 1) newT = 1;
        *s->value = s->minValue + newT * (s->maxValue - s->minValue);
    }

    if (!mousePressed) s->dragging = false;
}


// Initialize the sound settings system
void Sd_Settings_Init() {
    //CP_System_Fullscreen();
    
    myFont = CP_Font_Load("Assets/Fonts/QuinnDoodle.ttf");
    MainMenuBackground = CP_Image_Load("Assets/Misc/MenuScreen.png");
    Button_Sound_Load(&defaultSound,
        "Assets/soundTesters/ClickSound.wav",
        "Assets/soundTesters/HoverSound.wav",
        "Assets/soundTesters/ReleaseSound.wav");

    Button_Load(&MuteButton, &defaultSound,
        36 * unit, 92 * unit,
        55 * unit, 19.5 * unit,
        0 * unit,
        "Assets/Buttons/MainMenu/PlayNormal.png",
        "Assets/Buttons/MainMenu/PlayHighlight.png",
        "Assets/Buttons/MainMenu/PlayClicked.png", 1);

    // Centered slider
    float sliderWidth = 800;
    float sliderHeight = 100;
    float sliderX = (192 * unit / 2) - (sliderWidth / 2);
    float sliderY = 80 * unit;
    s = Slider_Create(sliderX, sliderY, sliderWidth, sliderHeight, &volume, 0.0f, 1.0f);

}



// Draw settings tab for all CP_Sound groups
void Sd_Settings_Update() {
    if (!settingsTabOpen) return;

    CP_Graphics_ClearBackground(CP_Color_Create(255, 128, 128, 255));
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(MainMenuBackground, 0, 0, 192 * unit, 108 * unit, 255);
    // Center slider horizontally
    float sliderWidth = 200;
    float sliderX = (192 * unit / 2) - (sliderWidth / 2);
    s.x = sliderX;
    s.y = 80 * unit; // vertical position
    s.width = sliderWidth;
    // Draw slider
    Slider_Draw(&s);
    // Draw label above slider
    CP_Settings_TextSize(28.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Volume Slider", s.x, s.y - 20);

    char volumeText[32];
    sprintf_s(volumeText, sizeof(volumeText), "Volume: %.2f", volume);
    CP_Settings_TextSize(28.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText(volumeText, s.x, s.y + 30);
    // Update master volume
    masterVolume = volume;
    CP_Sound_SetGroupVolume(0, masterVolume); // assuming group 0 is your main sound group


    if (CP_Input_KeyDown(KEY_Q))
    {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }

}

// Draw the settings tab (call every frame)
void Sd_Settings_Exit() {
    CP_Font_Free(myFont);
    CP_Image_Free(MainMenuBackground);

}

