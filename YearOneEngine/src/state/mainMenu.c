
#include "mainMenu.h"
#include "../system/mouse.h"
#include "../system/buttonSystem.h"

// Define buttons
#define NUM_BUTTONS 4


#define MAX_LABEL_LENGTH 32 // Maximum length for label
#define MAX_PATH_LENGTH 256 // Maximum length for image path

CP_Font my_awesome_font;
MouseSave nMouse = { 0,0, "Assets/mouse.png" };
*nMousePtr = &nMouse;

LineSave nLine = { 0,0,0,0,false };
LineSave* nLinePtr = &nLine;
CP_BOOL cursor = TRUE;
// Manually initialize buttons
ButtonComponent Buttons[NUM_BUTTONS] = {
	{0, "Start", "Assets/buttons/StartGame.png", NULL, 0.0f, 0.0f, 100.0f, 100.0f, false, CenterMiddle, 0.0f, 0.0f},
	{1, "Settings", "Assets/buttons/Settings.png", NULL, 0.0f, 0.0f, 100.0f, 100.0f, false, CenterMiddle, 0.0f, 120.0f},
	{2, "Exit", "Assets/buttons/Exit.png", NULL, 0.0f, 0.0f, 100.0f, 100.0f, false, CenterMiddle, 0.0f, 240.0f},
	{3, "Dev Mode", "Assets/buttons/DevMode.png", NULL, 0.0f, 0.0f, 100.0f, 100.0f, false, CenterMiddle, 0.0f, 360.0f}
};

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
	

	ButtonInit(Buttons, NUM_BUTTONS, CP_System_GetWindowWidth(), CP_System_GetWindowHeight());
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

	ButtonUpdate(Buttons, NUM_BUTTONS ,mouse_x, mouse_y);
	
	MouseManager(nMousePtr, nLinePtr);
	CP_Image_Draw(nMouse.sprite, mouse_x, mouse_y, 255, 255, 255);


}

void mMenu_Exit(void) {
	CP_Font_Free(my_awesome_font);
}

