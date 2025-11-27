//---------------------------------------------------------
// file:	settings.h
// author:	Zachary Ng
// email:	zacharyhuaen.n@digipen.edu
//
// brief:	Contains the declaration functions for 
//			sound slider implementation
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

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
/* Slider_Create()
Input:
    slider - slider struct to fill
    x, y, width, height - geometry
    value - pointer to the target float
    minVal, maxVal - clamp range
    knobSprite - knob texture path
Output:
    Slider* same pointer passed in
Brief:
    Sets up the slider fields and loads its knob texture.
*/
Slider* Slider_Create(Slider* slider, float x, float y, float width, float height, float* value, float minVal, float maxVal, char* knobSprite);
/* Slider_Draw()
Input:
    s - slider to draw
Output:
    void
Brief:
    Draws the track/knob and lets the user drag to update the value.
*/
void Slider_Draw(Slider* s);
/* Slider_Free()
Input:
    s - slider to free
Output:
    void
Brief:
    Releases the knob texture.
*/
void Slider_Free(Slider* s);

/* Sd_Settings_Init()
Input:
    None
Output:
    void
Brief:
    Prepares the settings tab resources.
*/
void Sd_Settings_Init();

/* Sd_Settings_Update()
Input:
    None
Output:
    void
Brief:
    Draws the settings UI when the tab is open.
*/
void Sd_Settings_Update();

/* Sd_Settings_Exit()
Input:
    None
Output:
    void
Brief:
    Cleans up fonts and textures used by the tab.
*/
void Sd_Settings_Exit();

#endif