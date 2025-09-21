#include "logo.h"
#include "mainMenu.h"
#include <stdio.h>
#include <math.h> // Required for exp()

struct LOGO {
	CP_Image logo;
	float img_startX;
	float img_startY;
};
struct LOGO DigiPenLOGO = { NULL,0,0 };
static float timer = 0;
static float time_sec = 0;
double result = 0.0;


void logo_init(void)
{
	//declare and initialize variables: logo
	DigiPenLOGO.logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
	if (DigiPenLOGO.logo == NULL)
	{
		printf("Failed to load image\n");
	}
	DigiPenLOGO.img_startX = 0.0f;
	DigiPenLOGO.img_startY = 0.0f;
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

}

void logo_update(void)
{
	//current time in seconds
	timer = CP_System_GetDt();
	//clear background to black
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	//update player variables
	int width = CP_System_GetWindowWidth();
	int height = CP_System_GetWindowHeight();
	//draw image every frame	
	time_sec = CP_System_GetSeconds();
	printf("%f\n", time_sec);
	result = exp(time_sec-2); // Calculates e^1
	CP_Image_Draw(DigiPenLOGO.logo, DigiPenLOGO.img_startX, DigiPenLOGO.img_startY, width, height, 255 - (result * 50));

	if (time_sec >= 4)
	{
		// this will pause mySound, but not mySecondSound, because mySecondSound is not in CP_SOUND_GROUP_3
		CP_Engine_SetNextGameState(mMenu_Init, mMenu_Update, mMenu_Exit);
	}
}

void logo_exit(void)
{
	//free resources loaded (unload)
	CP_Image_Free(DigiPenLOGO.logo);

	
}