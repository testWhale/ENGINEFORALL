#pragma once
#include "cprocessing.h"
#include <stdbool.h>
#include "../state/grid.h"
//typedef enum GridPosition {
//	GRID_LEFT, GRID_CENTER, GRID_RIGHT,
//	GRID_TOP, GRID_MIDDLE, GRID_BOTTOM
//};

typedef struct {
	int id;
	const char* label;
	const char* pathToSprite;
	CP_Image sprite;
	float cx;
	float cy;
	float width;
	float height;
	bool isMouseInside;
	Placement grid_pos;
	float offsetX;
	float offsetY;
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