#include "mouse.h"
float mouseX = 0.0f;
float mouseY = 0.0f;
float prevMouseX = 0.0f;
float prevMouseY = 0.0f;

bool mousePrevClick = false;
bool mousePrev2Click = false;
bool mouseClick1 = false;
bool mouseClick2 = false;

MouseClickState mouseState = FirstClick;
//so when clicked first, orev click turn true 
//then when clicked second mouse2 turns tru
//then if clicked again, clear all

int saveMousePos(MouseSave* nMouse, LineSave* nLine) {
	if (CP_Input_MouseDoubleClicked()) {
		// fill the pixel white
		printf("Mouse Clicked at X: %.2f, Y: %.2f\n", CP_Input_GetMouseX(), CP_Input_GetMouseY());
		nMouse->x = CP_Input_GetMouseX();
		nMouse->y = CP_Input_GetMouseY();
		switch (mouseState) {
			case FirstClick:
				nLine->x1 = nMouse->x;
				nLine->y1 = nMouse->y;
				printf("Point 1: %.2f, Y: %.2f\n", nLine->x1, nLine->y1);
				mouseState = SecondClick;
				break;
			case SecondClick:
				nLine->x2 = nMouse->x;
				nLine->y2 = nMouse->y;
				printf("Point 2: %.2f, Y: %.2f\n", nLine->x2, nLine->y2);
				nLine->isActive = true;
				mouseState = Reset;
				break;
			case Reset:
				nLine->x1 = -1;
				nLine->y1 = -1;
				nLine->x2 = -1;
				nLine->y2 = -1;
				nLine->isActive = false;
				printf("LINE DEACTIVATED \n");
				mouseState = FirstClick;
				break;
		}

	}
}

int drawSketchLine(LineSave* nLine) {
	if (nLine && nLine->isActive) {
		// draw a line from the origin to the mouse position
			CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
			CP_Graphics_DrawLine(nLine->x1, nLine->y1, nLine->x2, nLine->y2);
	}
}

int MouseManager(MouseSave* nMouse, LineSave* nLine) {
	if (nLine->isActive == true) {
		drawSketchLine(nLine);
		if (CP_Input_MouseDoubleClicked()) {
			saveMousePos(nMouse, nLine);
		}
	}
	else {
		saveMousePos(nMouse, nLine);
	}
}