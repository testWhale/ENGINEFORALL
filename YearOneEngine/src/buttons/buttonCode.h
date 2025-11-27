//---------------------------------------------------------
// file:	buttonCode.h
// author:	[Quak June Hao (Quinn)]
// email:	[quak.j@digipen.edu]
//
// brief:	This code contains declaration for the button behavior and generation system
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------


#include "cprocessing.h"
typedef struct ButtonSound {
    CP_Sound onHover, onClick, onRelease;
}ButtonSound;

typedef struct ButtonInfo 
    {
    CP_Vector buttonPos;
    float buttonWidth, buttonHeight,buttonDiameter;
    CP_Image buttonNormal, buttonFeedback, buttonHighlight;
    int isSel, isClicked, wasHovered;
    ButtonSound *soundEffect;
    int isDisplayingText;
    //EXTRAS
    int alive;
    int transparency_Value;
    }ButtonInfo;

/// <summary>
/// This function loads the button with all the data you pass into it.
/// </summary>
/// <param name="newBtn">Just insert your specific button name</param>
/// <param name="soundPreset">Choose from the specific pre-loaded presets for the sound feedback</param>
/// <param name="posX">The buttons X position. Please use units</param>
/// <param name="posY">The buttons Y position. Please use units</param>
/// <param name="width">The button's width. Please use units</param>
/// <param name="height">The button's Length. Please use units</param>
/// <param name="diameter">The button's diameter.Please input 0 if its a square button. Please use units</param>
/// <param name="buttonNormalPath">Insert the pathname for the button's normal frame as a string here</param>
/// <param name="buttonFeedbackPath">Insert the pathname for the button's Clicked frame as a string here</param>
/// <param name="buttonHighlightPath">Insert the pathname for the button's Highlight frame as a string here</param>
void Button_Load(ButtonInfo* newbtn,
    ButtonSound* soundPreset,
    float posX, float posY,
    float width, float height,
    float diameter,
    const char* buttonNormalPath,
    const char* buttonFeedbackPath,
    const char* buttonHighlightPath,
    int alive );

/// <summary>
/// This frees up all relevant assets with your button
/// </summary>
/// <param name="newbtn">insert button name here</param>
void Button_Free(ButtonInfo* newbtn);


/// <summary>
/// This Loads your soundpack for your buttons
/// </summary>
/// <param name="soundPreset">Insert Preset Name</param>
/// <param name="soundClickPath">insert path as a string</param>
/// <param name="soundHoverPath">insert path as a string</param>
/// <param name="soundReleasePath">insert path as a string/param>
void Button_Sound_Load(ButtonSound* soundPreset, const char* soundClickPath, const char* soundHoverPath, const char* soundReleasePath);

/// <summary>
/// This frees up the soundpack
/// </summary>
/// <param name="soundPreset">insert soundpack name</param>
void Button_Sound_Free(ButtonSound* soundPreset);


//this 3 functions handle behavior of drawing the buttons
//insert the button name as necessaru
void Draw_Button_Normal(ButtonInfo* btnname);
void Draw_Button_Feedback(ButtonInfo* btnname);
void Draw_Button_Highlight(ButtonInfo* btnname);


//helper functions to help check for behavior in a button
int Is_Any_Button_Hovered(ButtonInfo* btnname, float mousex, float mousey);
int Is_Button_Pressed(ButtonInfo* btnname, int isHovered);
int Is_Button_Released(ButtonInfo* btnname, int isHovered);

/// <summary>
/// this renders the whole behavior of a button
/// </summary>
/// <param name="btnname">insert the button struct name</param>
void Button_Behavior(ButtonInfo* btnname);
