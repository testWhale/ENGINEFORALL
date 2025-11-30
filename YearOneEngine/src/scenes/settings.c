//---------------------------------------------------------
// file:	settings.c
// author:	Zachary Ng
// email:	zacharyhuaen.n@digipen.edu
//
// brief:	Contains the function definitions for 
//			sound slider implementation
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "buttons/buttonCode.h"
#include "scenes/settings.h"
#include "mainmenu.h"

bool settingsTabOpen = true;
float masterVolume = 1.0f;
//extern int unit;
float volume = 0.5f;
CP_Font myFont;
CP_Image MainMenuBackground;
ButtonInfo MuteButton;
ButtonSound defaultSound;

/* Slider_Create()
Input:
    slider     - pointer to an allocated Slider struct
    x, y       - top-left position of slider
    width, height - size of slider
    value      - pointer to the float this slider controls
    minVal     - minimum allowed value
    maxVal     - maximum allowed value
    knobSprite - path to knob image file
Output:
    Returns the same Slider pointer after initialization
*/
Slider* Slider_Create(Slider* slider, float x, float y, float width, float height, float* value, float minVal, float maxVal, char* knobSprite) {
    slider->x = x;
    slider->y = y;
    slider->width = width;
    slider->height = height;
    slider->value = value;
    slider->minValue = minVal;
    slider->maxValue = maxVal;
    slider->dragging = false;
    slider->knob = CP_Image_Load(knobSprite);
    return slider;
}

/* Slider_Draw()
Input:
    s - pointer to a Slider
Output:
    void
Brief:
    Draws the track and knob, clamps the value, and responds to mouse input.
*/
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
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(s->knob, knobX - knobSize / 2, s->y + s->height / 2 - knobSize / 2, knobSize, knobSize, 255);

    if (!mousePressed) s->dragging = false;
}


/* Slider_Free()
Input:
    s - pointer to a Slider
Output:
    None
Description:
    Frees the knob sprite loaded for this slider
*/
void Slider_Free(Slider* s) {
    CP_Image_Free(s->knob);
}


/* Sd_Settings_Exit()
Input:
    None
Output:
    void
Brief:
    Releases fonts and images used by the tab.
*/
void Sd_Settings_Exit() {
    CP_Font_Free(myFont);
    CP_Image_Free(MainMenuBackground);

}