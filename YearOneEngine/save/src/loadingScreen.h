#include "cprocessing.h"
#include <stdio.h>
#include "./game.h"

CP_Image logo_A;
static float timer = 0;

void loadScrn_init()
{
	logo_A = CP_Image_Load("Assets/DigiPen_Singapore_WEB_RED.png");
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);

	CP_System_SetWindowSize(CP_Image_GetWidth(logo_A), CP_Image_GetHeight(logo_A));

}

//app loop
void loadScrn_update()
{

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Image_Draw(logo_A, 0.f, 0.f, CP_Image_GetWidth(logo_A), CP_Image_GetHeight(logo_A), 255);
	timer += CP_System_GetDt();
	printf("%f", timer);
	if (timer >= 1.5) {
		CP_Engine_SetNextGameStateForced(game_init, game_update, NULL);
	}
	/*CP_Graphics_DrawRect(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50, 50);*/
}

void loadScrn_exit()
{
	CP_Image_Free(logo_A);
}

