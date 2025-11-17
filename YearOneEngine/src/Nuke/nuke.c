#include "nuke.h"
#include <stdio.h>
#include <stdlib.h>
#include "cprocessing.h"

static float nukeX;
static float nukeY;
float nukeDropSpeed;


void Nuke_Init(void) {
	nukeX = 1920 / 2.0f;
	nukeY = 0.0f;
	nukeDropSpeed = 80.0f;
}

void Nuke_Update(void) {
	float dt = CP_System_GetDt();
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	
	CP_Settings_Fill(CP_Color_Create(0, 255, 0, 255));
	CP_Graphics_DrawCircle(nukeX, nukeY, 60);

	nukeY += nukeDropSpeed * dt;

	if (nukeY >= 1080 / 2.0f) {
		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
		CP_Graphics_DrawCircle(nukeX, nukeY, 500);

		CP_Engine_Terminate();
	}

}

void Nuke_Exit(void) {

}