/*!
@file buttonCode.c
@author Quak June Hao (quak.j)
@course Software Engineering Project (CSD1401)
@section A
@GAM 100
@date 28/10/25
@links this file has a header file connected named buttonCode.h 
@brief This file contains buttons code that handles button behavior and feedback
*/

#include "cprocessing.h"
#include "buttonCode.h"
#include <math.h>


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
void Button_Load(ButtonInfo* newBtn,
	ButtonSound* soundPreset,
	float posX, float posY,
	float width, float height,
	float diameter,
	const char* buttonNormalPath,
	const char* buttonHighlightPath,
	const char* buttonFeedbackPath,
	int alive
	)
	{	
	newBtn -> buttonPos = CP_Vector_Set(posX, posY);
	newBtn -> buttonWidth = width;
	newBtn -> buttonHeight = height;
	newBtn->buttonDiameter = diameter;
	newBtn -> buttonNormal = CP_Image_Load(buttonNormalPath);
	newBtn -> buttonFeedback = CP_Image_Load(buttonFeedbackPath);
	newBtn -> buttonHighlight = CP_Image_Load(buttonHighlightPath);
	newBtn->soundEffect = soundPreset;
	newBtn->alive = alive;
	}

void Button_Free(ButtonInfo* newBtn)
{
	//CP_Image_Free(newBtn->buttonNormal);
	//CP_Image_Free(newBtn->buttonFeedback);
	/*CP_Image_Free(newBtn->buttonHighlight);
	CP_Sound_Free(newBtn->soundEffect->onClick);
	CP_Sound_Free(newBtn->soundEffect->onHover);
	CP_Sound_Free(newBtn->soundEffect->onRelease);*/
}

void Button_Sound_Load
	(ButtonSound* soundPreset, 
	const char* soundClickPath, 
	const char* soundHoverPath, 
	const char* soundReleasePath) 
	{
	soundPreset->onClick = CP_Sound_Load(soundClickPath);
	soundPreset->onHover = CP_Sound_Load(soundHoverPath);
	soundPreset->onRelease = CP_Sound_Load(soundReleasePath);
	}

void Button_Sound_Free
(ButtonSound* soundPreset)
{
	CP_Sound_Free(soundPreset->onClick);
	CP_Sound_Free(soundPreset->onHover);
	CP_Sound_Free(soundPreset->onRelease);
}

//void drawSquareButtonNormal(buttonInfo*btnname) {
//CP_Settings_ImageMode(CP_POSITION_CENTER);
//CP_Image_Draw( btnname->buttonNormal, btnname->buttonPos.x, btnname->buttonPos.y, btnname->buttonWidth, btnname->buttonHeight, 255);
//}
//
//void drawSquareButtonFeedback(buttonInfo* btnname) {
//	CP_Settings_ImageMode(CP_POSITION_CENTER);
//	CP_Image_Draw(btnname->buttonFeedback, btnname->buttonPos.x, btnname->buttonPos.y, btnname->buttonWidth, btnname->buttonHeight, 255);
//}
//
//void drawSquareButtonHighlight(buttonInfo* btnname) {
//	CP_Settings_ImageMode(CP_POSITION_CENTER);
//	CP_Image_Draw(btnname->buttonHighlight, btnname->buttonPos.x, btnname->buttonPos.y, btnname->buttonWidth, btnname->buttonHeight, 255);
//}
/*
This function pulls your data and draws the normal frame where nothing is happening.
In order to make it function please insert a valid image or else it will turn transparent
*/
void Draw_Button_Normal(ButtonInfo* btnName) {
	if (btnName->alive) {
		btnName->transparency_Value = 255;
	}
	else btnName->transparency_Value = 0;
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(	btnName->buttonNormal, 
					btnName->buttonPos.x, btnName->buttonPos.y, 
					btnName->buttonWidth, btnName->buttonHeight, btnName->transparency_Value);
}

/// <summary>
/// This function draws the feedback frame for the specific button
/// </summary>
/// <param name="btnName">Just insert your specific button name</param>
void Draw_Button_Feedback(ButtonInfo* btnName) {
	if (btnName->alive) {
		btnName->transparency_Value = 255;
	}
	else btnName->transparency_Value = 0;
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(	btnName->buttonFeedback, 
					btnName->buttonPos.x, btnName->buttonPos.y, 
					btnName->buttonWidth, btnName->buttonHeight, btnName->transparency_Value);
}

/*
This function pulls your data and draws the Highlight frame when you hover over it.
In order to make it function please insert a valid image or else it will turn transparent
*/
void Draw_Button_Highlight(ButtonInfo* btnname) {
	if (btnname->alive) {
		btnname->transparency_Value = 255;
	}
	else btnname->transparency_Value = 0;
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(btnname->buttonHighlight, btnname->buttonPos.x, btnname->buttonPos.y, btnname->buttonWidth, btnname->buttonHeight, btnname->transparency_Value);
}
//int isCircleButtonHovered(buttonInfo* btnname, float mousex, float mousey) {
//	return (sqrt((mousex - btnname->buttonPos.x) * (mousex - btnname->buttonPos.x) + (mousey - btnname->buttonPos.y) * (mousey - btnname->buttonPos.y)) <= btnname->buttonDiameter / 2);
//}
//
//int isSquareButtonHovered(buttonInfo* btnname, float mousex, float mousey){
//		if ((mousex <= (btnname->buttonPos.x + (btnname->buttonWidth / 2.0)))
//			&& (mousex >= (btnname->buttonPos.x - (btnname->buttonWidth / 2.0)))
//				&& (mousey <= (btnname->buttonPos.y + (btnname->buttonHeight / 2.0)))
//					&& (mousex >= (btnname->buttonPos.y - (btnname->buttonHeight / 2.0))))
//			{
//			return 1;
//			
//			}
//
//		return 0;
//}

/// <summary>
/// This function checks if you're hovering over the button
/// </summary>
/// <param name="btnName">Insert the name of your button here</param>
/// <param name="mouseX">Just use CP_Get_MouseX</param>
/// <param name="mouseY"></param>
/// <returns></returns>
int Is_Any_Button_Hovered(ButtonInfo* btnName, float mouseX, float mouseY) {
	if (btnName->buttonDiameter) {
		return (sqrt((mouseX - btnName->buttonPos.x) * (mouseX - btnName->buttonPos.x) + (mouseY - btnName->buttonPos.y) * (mouseY - btnName->buttonPos.y)) <= btnName->buttonDiameter / 2);
	}
	else if (btnName->buttonWidth && btnName->buttonHeight) 
	{
		if    ((mouseX <= (btnName->buttonPos.x + (btnName->buttonWidth / 2.0)))
			&& (mouseX >= (btnName->buttonPos.x - (btnName->buttonWidth / 2.0)))
			&& (mouseY <= (btnName->buttonPos.y + (btnName->buttonHeight / 2.0)))
			&& (mouseY >= (btnName->buttonPos.y - (btnName->buttonHeight / 2.0))))
		{
			return 1;

		}
	}
	return 0;
}

/*
This function checks if your mouse is pressing the area. It will trigger constantly while your mouse is down.
*/
int Is_Button_Pressed(ButtonInfo* btnName, int isHovered) {

	 if ((CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) && isHovered ==1) {
		return 1;
		
	}
	return 0;
}

/*
This function checks if your mouse has lifted up. Your mouse must still be hovering over the area when it releases to return a positive input)
*/
int Is_Button_Released(ButtonInfo* btnName, int isHovered) {
	if (CP_Input_MouseClicked() && isHovered == 1) {
		return 1;
	}
	return 0;
}

/*
This whole function accounts for button behavior. It will draw and return outputs based on if nothing is happening.its hovering or you clicked it.

In order to code button behavior. Use the isSel to return output when you hover like this.
if (buttonName.isSel ==1) {
desired behavior;
}

In order to code button behavior. Use the isClicked variable to return output when you click AND THEN RELEASE
if (buttonName.isClicked ==1) {
desired behavior;
}

*/
void Button_Behavior(ButtonInfo* btnname) {
	if (btnname->alive)
	{
		Draw_Button_Highlight(btnname);
		if (Is_Button_Pressed(btnname, Is_Any_Button_Hovered(btnname, CP_Input_GetMouseX(), CP_Input_GetMouseY()))) { //draw the clicked frame if you press down
			Draw_Button_Feedback(btnname);
			if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) {
				CP_Sound_Play(btnname->soundEffect->onClick);
				printf("1");
			}

		}

		else {
			if (Is_Button_Released(btnname, Is_Any_Button_Hovered(btnname, CP_Input_GetMouseX(), CP_Input_GetMouseY())))
			{ //only return isClicked =1 on release
				CP_Sound_Play(btnname->soundEffect->onRelease);
				btnname->isClicked = 1;
				printf("2");
			}

			else { //if its not being clicked or released draw the highlight frame and return isSel =1;
				if (Is_Any_Button_Hovered(btnname, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1)
				{
					Draw_Button_Highlight(btnname);
					if (!btnname->wasHovered) {

						CP_Sound_Play(btnname->soundEffect->onHover);
					}
					btnname->isSel = 1;
					btnname->isClicked = 0;
				}
				else
				{ //if nothing else is happening just draw the Normal Frame and set both isSel and isClicked to negative
					Draw_Button_Normal(btnname);
					if (btnname->wasHovered) {
						CP_Sound_StopAll();
					}
					btnname->isSel = 0;
					btnname->isClicked = 0;
					btnname->isDisplayingText = 1;
				}
			}
		}
		btnname->wasHovered = (Is_Any_Button_Hovered(btnname, CP_Input_GetMouseX(), CP_Input_GetMouseY()));
	}
}
