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

/*
This function loads all your button after you declare it in your struct.
It assigns all the data to its equivalent struct data
*/
void buttonLoad(buttonInfo* newbtn, float posX, float posY, float width, float height, float diameter, const char* buttonNormalPath, const char* buttonFeedbackPath, const char* buttonHighlightPath) { //this loads the button data from the computer
	newbtn -> buttonPos = CP_Vector_Set(posX, posY);
	newbtn -> buttonWidth = width;
	newbtn -> buttonHeight = height;
	newbtn->buttonDiameter = diameter;
	newbtn -> buttonNormal = CP_Image_Load(buttonNormalPath);
	newbtn -> buttonFeedback = CP_Image_Load(buttonFeedbackPath);
	newbtn -> buttonHighlight = CP_Image_Load(buttonHighlightPath);
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
void drawButtonNormal(buttonInfo* btnname) {
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(btnname->buttonNormal, btnname->buttonPos.x, btnname->buttonPos.y, btnname->buttonWidth, btnname->buttonHeight, 255);
}

/*
This function pulls your data and draws the clicked frame when you have pressed it AND let go
In order to make it function please insert a valid image or else it will turn transparent
*/
void drawButtonFeedback(buttonInfo* btnname) {
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(btnname->buttonFeedback, btnname->buttonPos.x, btnname->buttonPos.y, btnname->buttonWidth, btnname->buttonHeight, 255);
}

/*
This function pulls your data and draws the Highlight frame when you hover over it.
In order to make it function please insert a valid image or else it will turn transparent
*/
void drawButtonHighlight(buttonInfo* btnname) {
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(btnname->buttonHighlight, btnname->buttonPos.x, btnname->buttonPos.y, btnname->buttonWidth, btnname->buttonHeight, 255);
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

/*
This function checks if your mouse is hovering over the area. It accounts for both circles and rectangles and squares (if its a square input no diameter input please)
*/
int isAnyButtonHovered(buttonInfo* btnname, float mousex, float mousey) {
	if (btnname->buttonDiameter) {
		return (sqrt((mousex - btnname->buttonPos.x) * (mousex - btnname->buttonPos.x) + (mousey - btnname->buttonPos.y) * (mousey - btnname->buttonPos.y)) <= btnname->buttonDiameter / 2);
	}
	else if (btnname->buttonWidth && btnname->buttonHeight) {
		if ((mousex <= (btnname->buttonPos.x + (btnname->buttonWidth / 2.0)))
			&& (mousex >= (btnname->buttonPos.x - (btnname->buttonWidth / 2.0)))
			&& (mousey <= (btnname->buttonPos.y + (btnname->buttonHeight / 2.0)))
			&& (mousex >= (btnname->buttonPos.y - (btnname->buttonHeight / 2.0))))
		{
			return 1;

		}
	}
	return 0;
}

/*
This function checks if your mouse is pressing the area. It will trigger constantly while your mouse is down.
*/
int isButtonPressed(buttonInfo* btnname, int isHovered) {

	 if ((CP_Input_MouseDown(MOUSE_BUTTON_LEFT)) && isHovered ==1) {
		return 1;
		
	}
	return 0;
}

/*
This function checks if your mouse has lifted up. Your mouse must still be hovering over the area when it releases to return a positive input)
*/
int isButtonReleased(buttonInfo* btnname, int isHovered) {
	if (CP_Input_MouseClicked() && isHovered == 1) {
		printf("Released");
		return 1;
	}
	return 0;
}

/*
This whole function accounts for button behavior. It will draw and return outputs based on if nothing is happening.its hovering or you clicked it.

In order to code button behavior. Use the isHovered variable if behavior happens if it happens when you hover like this.
if (buttonName.isSel ==1) {
desired behavior;
}

In order to code button behavior. Use the isClicked variable if behavior happens if it happens when you click AND THEN RELEASE
if (buttonName.isClicked ==1) {
desired behavior;
}

*/
void buttonBehavior(buttonInfo* btnname) {

	if (isButtonPressed(btnname, isAnyButtonHovered(btnname, CP_Input_GetMouseX(), CP_Input_GetMouseY()))) { //draw the clicked frame if you press down
		drawButtonFeedback(btnname);
	}

	else {
		if (isButtonReleased(btnname, isAnyButtonHovered(btnname, CP_Input_GetMouseX(), CP_Input_GetMouseY()))) { //only return isClicked =1 on release
			btnname->isClicked = 1;
		}

		else { //if its not being clicked or released draw the highlight frame and return isSel =1;
			if (isAnyButtonHovered(btnname, CP_Input_GetMouseX(), CP_Input_GetMouseY()) == 1) {
				drawButtonHighlight(btnname);
				btnname->isSel = 1;
			}

			else { //if nothing else is happening just draw the Normal Frame and set both isSel and isClicked to negative
				drawButtonNormal(btnname);
				btnname->isSel = 0;
				btnname->isClicked = 0;
				}
			}
		}
	}
