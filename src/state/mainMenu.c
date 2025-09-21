
#include "mainMenu.h"
#include "../system/mouse.h"
#include "../system/buttonSystem.h"

// Define buttons
#define NUM_BUTTONS 4
ButtonComponent buttons[NUM_BUTTONS];

CP_Font my_awesome_font;
MouseSave nMouse = { 0,0, "Assets/mouse.png" };
*nMousePtr = &nMouse;

LineSave nLine = { 0,0,0,0,false };
LineSave* nLinePtr = &nLine;
CP_BOOL cursor = TRUE;

void mMenu_Init(void) {

	my_awesome_font = CP_Font_Load("Assets/Fonts/Exo2/Exo2-Regular.ttf");
	if (my_awesome_font == NULL)
	{
		printf("Failed to load image\n");
	}
	CP_Font_Set(my_awesome_font);
	// Tells CProcessing that when drawing text in the future (via CP_Font_DrawText),
	// the position given to it is the center of the text horizontally and vertically.
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	// Tells CProcessing that when drawing text in the future (via CP_Font_DrawText),
	// We use size 72 font height.
	CP_Settings_TextSize(72.f);
	nMouse.sprite = CP_Image_Load("Assets/mouse1.png");
	if (nMouse.sprite == NULL)
	{
		printf("Failed to load image\n");
	}
}

void mMenu_Update(void) {
	float mouse_x = CP_Input_GetMouseX();
	float mouse_y = CP_Input_GetMouseY();
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();
	char buffer[256];

	sprintf_s(buffer, sizeof(buffer), "mouse X: %.2f, mouse_y: %.2f", mouse_x, mouse_y);
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 250, 255));
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Font_DrawText(buffer, (float)CP_System_GetWindowWidth() / 2, (float)CP_System_GetWindowHeight() / 2);
	//CP_System_ShowCursor(cursor);
	CP_Image_Draw(nMouse.sprite, mouse_x, mouse_y, 255, 255, 255);
	for (int i = 0; i < NUM_BUTTONS; i++) {
		buttons[i].id = i;
		buttons[i].sprite = CP_Image_Load("Assets/DigiPen_Singapore_WEB_BLACK.png");
		buttons[i].width = 100;
		buttons[i].height = 100;
		buttons[i].cx = 200.0f + i * 150.0f; // Example positioning
	}
	ButtonUpdate(ButtonComponent buttons[], mouse_x, mouse_y);
	
	MouseManager(nMousePtr, nLinePtr);


}

void mMenu_Exit(void) {
	CP_Font_Free(my_awesome_font);
}

