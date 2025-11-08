#include <cprocessing.h>
#include "utils/utils.h"
#include "scenes/mainmenu.h"
#include "buttons/buttonCode.h"

CP_Font myFont;
CP_Image MainMenuBackground,Sam;
ButtonInfo BackButton;
ButtonSound defaultSound;
char CreditsString[100];
float unit;


void Credits_Init(void)
{
    CP_System_Fullscreen();
    unit = CP_System_GetWindowWidth() / 192.0f;
    myFont = CP_Font_Load("Assets/Fonts/QuinnDoodle.ttf");
    MainMenuBackground = CP_Image_Load("Assets/Misc/MenuScreen.png");
    Sam = CP_Image_Load("Assets/buttonTesters/Catboy.png");

    Button_Sound_Load(&defaultSound,
        "Assets/soundTesters/ClickSound.wav",
        "Assets/soundTesters/HoverSound.wav",
        "Assets/soundTesters/ReleaseSound.wav");

    Button_Load(&BackButton, &defaultSound,
        156 * unit, 92 * unit,
        55 * unit, 19.5 * unit,
        0 * unit,
        "Assets/Buttons/MainMenu/QuitNormal.png",
        "Assets/Buttons/MainMenu/QuitHighlight.png",
        "Assets/Buttons/MainMenu/QuitClicked.png");
}

void Credits_Update(void)
{

    CP_Graphics_ClearBackground(CP_Color_Create(255, 128, 128, 255));
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(MainMenuBackground, 0, 0, 192 * unit, 108 * unit, 255);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(4 * unit);
    sprintf_s(CreditsString, 100, "We do not have credits yet, for now please enjoy this picture");

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText(CreditsString, 70 * unit, 90 * unit);
    CP_Image_Draw(Sam, 100 * unit, 10 * unit, 70 * unit, 70 * unit, 255);
  
    Button_Behavior(&BackButton);

   

    if (BackButton.isClicked)
    {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
   
    

}

void Credits_Exit(void)
{
	CP_Font_Free(myFont);
    Button_Free(&BackButton);
    Button_Sound_Free(&defaultSound);
}