/*!
@file buttonCode.h
@author Quak June Hao (quak.j)
@course Software Engineering Project (CSD1401)
@section A
@GAM 100
@date 28/10/25
@links this file has a function file that is named buttonCode.c
@brief This header file has functions that helps handle button behavior and feedback
*/

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
    }ButtonInfo;

void Button_Load(ButtonInfo* newbtn, 
    ButtonSound* soundPreset, 
    float posX, float posY, 
    float width, float height, 
    float diameter, 
    const char* buttonNormalPath, 
    const char* buttonFeedbackPath, 
    const char* buttonHighlightPath); 	//this loads the button data from the computer
    //this loads the button data from the computer

void Button_Sound_Load(ButtonSound* soundPreset, const char* soundClickPath, const char* soundHoverPath, const char* soundReleasePath);

void Draw_Button_Normal(ButtonInfo* btnname);
void Draw_Button_Feedback(ButtonInfo* btnname);
void Draw_Button_Highlight(ButtonInfo* btnname);

//int isSquareButtonHovered(buttonInfo* btnname, float mousex, float mousey);
//int isCircleButtonHovered(buttonInfo* btnname, float mousex, float mousey);
int Is_Any_Button_Hovered(ButtonInfo* btnname, float mousex, float mousey);
int Is_Button_Pressed(ButtonInfo* btnname, int isHovered);
int Is_Button_Released(ButtonInfo* btnname, int isHovered);

void Button_Behavior(ButtonInfo* btnname);
