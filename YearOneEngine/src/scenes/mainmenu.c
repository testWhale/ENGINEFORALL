#include <cprocessing.h>
#include "utils/utils.h"
#include "scenes/mainmenu.h"
#include "test.h"

CP_Font myFont;
float winWidth;
float winHeight;
float firstButtonCx;
float firstButtonCy;
float secButtonCx;
float secButtonCy;
CP_TEXT_ALIGN_HORIZONTAL horizontal = CP_TEXT_ALIGN_H_CENTER;
CP_TEXT_ALIGN_VERTICAL vertical = CP_TEXT_ALIGN_V_MIDDLE;
//Button buttons[2] = { {0.0f,0.0f,0.0f,}, {} };

void Main_Menu_Init(void)
{
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");

}

void Main_Menu_Update(void)
{
    winHeight = CP_System_GetWindowHeight();
    winWidth = CP_System_GetWindowWidth();
    CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));

    //Draw Rectangle 
    // draw a 100x100 rectangle
    firstButtonCx = winWidth / 2.0f;
    firstButtonCy = (winHeight / 2.0f) -200.0f;
	CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(firstButtonCx, firstButtonCy,
        300.0f,200.0f);
    CP_Font_Set(myFont);
    CP_Settings_TextAlignment(horizontal, vertical);
    CP_Settings_TextSize(60.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Play", firstButtonCx, firstButtonCy);
    if (IsAreaClicked(firstButtonCx, firstButtonCy, 300.0f, 200.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())){   
        CP_Engine_SetNextGameState(Test_Init, Test_Update, NULL);
    }
    
   


    //2nd Text Box
    secButtonCx = winWidth / 2.0f;
    secButtonCy = (winHeight / 2.0f) + 200.0f;
    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
    CP_Graphics_DrawRect(secButtonCx, secButtonCy,
        300.0f, 200.0f);
    CP_Font_Set(myFont);
    CP_Settings_TextAlignment(horizontal, vertical);
    CP_Settings_TextSize(60.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText("Exit", secButtonCx, secButtonCy);
    if (IsAreaClicked(secButtonCx, secButtonCy, 300.0f, 200.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
        CP_Engine_Terminate();
    }

}

void Main_Menu_Exit(void)
{
	CP_Font_Free(myFont);
}