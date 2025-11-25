#ifndef SET_H
#define SET_H
#include <stdbool.h>

typedef struct {
    float x, y;       // top-left of slider
    float width, height;
    float* value;     // pointer to controlled variable
    float minValue;
    float maxValue;
    bool dragging;
    CP_Image knob;
} Slider;
Slider s;
Slider* Slider_Create(Slider* slider, float x, float y, float width, float height, float* value, float minVal, float maxVal, char* knobSprite);
void Slider_Draw(Slider* s);
void Slider_Free(Slider* s);

void Sd_Settings_Init();

// Draw settings tab for all CP_Sound groups
void Sd_Settings_Update();

// Draw the settings tab (call every frame)
void Sd_Settings_Exit();

#endif