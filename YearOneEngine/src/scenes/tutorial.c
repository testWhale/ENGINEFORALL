#include <cprocessing.h>
#include "utils/utils.h"
#include "scenes/mainscene.h"
#include "scenes/mainmenu.h"
#include "buttons/buttonCode.h"

#define instructions 24
CP_Image Tutorial[instructions];
const char* TutorialString[instructions];
int tutcounter = 0;


void Tutorial_Init(void)
{
	unit = CP_System_GetWindowWidth() / 192.0f;
	TutorialString[0] = "Assets/Tutorial/Page1.png";
	TutorialString[1] = "Assets/Tutorial/Page2.png";
	TutorialString[2] = "Assets/Tutorial/Page3.png";
	TutorialString[3] = "Assets/Tutorial/Page4.png";
	TutorialString[4] = "Assets/Tutorial/Page5.png";
	TutorialString[5] = "Assets/Tutorial/Page6.png";
	TutorialString[6] = "Assets/Tutorial/Page7.png";
	TutorialString[7] = "Assets/Tutorial/Page8.png";
	TutorialString[8] = "Assets/Tutorial/Page9.png";
	TutorialString[9] = "Assets/Tutorial/Page10.png";
	TutorialString[10] = "Assets/Tutorial/Page11.png";
	TutorialString[11] = "Assets/Tutorial/Page12.png";
	TutorialString[12] = "Assets/Tutorial/Page13.png";
	TutorialString[13] = "Assets/Tutorial/Page14.png";
	TutorialString[14] = "Assets/Tutorial/Page15.png";
	TutorialString[15] = "Assets/Tutorial/Page16.png";
	TutorialString[16] = "Assets/Tutorial/Page17.png";
	TutorialString[17] = "Assets/Tutorial/Page18.png";
	TutorialString[18] = "Assets/Tutorial/Page19.png";
	TutorialString[19] = "Assets/Tutorial/Page20.png";
	TutorialString[20] = "Assets/Tutorial/Page21.png";
	TutorialString[21] = "Assets/Tutorial/Page22.png";
	TutorialString[22] = "Assets/Tutorial/Page23.png";
	TutorialString[23] = "Assets/Tutorial/Page24.png";

	for (int i = 0; i < instructions; i++)
	{
		Tutorial[i] = CP_Image_Load(TutorialString[i]);
	}

}

void Tutorial_Update(void)
{
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(Tutorial[tutcounter], 0, 0, 192 * unit, 108 * unit, 255);
	if (CP_Input_MouseTriggered(MOUSE_BUTTON_LEFT)) tutcounter += 1;
	if (tutcounter ==24)CP_Engine_SetNextGameState(Main_Scene_Init, Main_Scene_Update, Main_Scene_Exit);

}

void Tutorial_Exit(void)
{
	for (int i = 0; i < instructions; i++)
	{
		CP_Image_Free(Tutorial[i]);
	}
}