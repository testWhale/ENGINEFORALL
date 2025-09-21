#pragma once
#include "cprocessing.h"
#include <stdbool.h>
typedef struct ButtonTem {
	float cx;
	float cy;
	float width;
	float height;
	bool isMouseInside;
	CP_Image sprite;

	const char* label;
	int id;
} ButtonComponent; 

//typedef union {
//	ButtonTem button;
//	int id;
//}ButtonComponent;

void ButtonInit(ButtonComponent Buttons[], int num_buttons, float win_width, float win_height);
void ButtonUpdate(ButtonComponent Buttons[], int num_buttons,float mouseX, float mouseY);
void isMouseInsideButton(ButtonComponent* mbutton,float mouseX, float mouseY);
void ButtonShutdown();

// Function to create a button with grid-based positioning
create_button();