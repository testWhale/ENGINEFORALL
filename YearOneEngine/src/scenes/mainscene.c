#include "cprocessing.h"
#include "utils/utils.h"
#include "mainscene.h"
#include "test.h"
#include "economy/economyCode.h"
#include "clicker/clickCode.h"
#include "buttons/buttonCode.h"
#include "utils/arr.h"
#include <stdio.h>
CP_Image Overlay;

ButtonInfo ClickerButton, SettingButton;
ButtonInfo ClickerUpgrade1, ClickerUpgrade2, ClickerUpgrade3;
ButtonInfo TroopButton1, TroopButton2, TroopButton3;
ButtonSound defaultSound;
CP_Font myFont;
float winWidth;
float winHeight;
float unit;


void Main_Scene_Init(void)
{   
    CP_System_Fullscreen();
    winHeight = CP_System_GetWindowHeight();
    winWidth = CP_System_GetWindowWidth();
    unit = CP_System_GetWindowWidth()/ 192.0f;
    printf("%f \n %f\n %f\n", winHeight, winWidth,unit );
    Overlay = CP_Image_Load("Assets/ConceptArt.jpg");
    myFont = CP_Font_Load("Assets/Fonts/Exo2-Regular.ttf");

    Button_Sound_Load(&defaultSound, 
        "Assets/soundTesters/ClickSound.wav", 
        "Assets/soundTesters/HoverSound.wav", 
        "Assets/soundTesters/ReleaseSound.wav");


    Button_Load(&ClickerButton, &defaultSound, 
        25 * unit, 40 * unit, 
        40 * unit, 40 * unit,
        40 * unit,
        "Assets/buttons/Clicker.png", 
        "Assets/buttonTesters/CircleClicked.png", 
        "Assets/buttonTesters/CircleHighlight.png");

    Button_Load(&SettingButton, &defaultSound, 
        182 * unit, 10 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/buttonTesters/NormalImage.jpg", 
        "Assets/buttonTesters/HighlightImage.jpg", 
        "Assets/buttonTesters/ClickedImage.jpg");


    Button_Load(&ClickerUpgrade1, &defaultSound,
        10 * unit, 75 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/buttonTesters/NormalImage.jpg",
        "Assets/buttonTesters/HighlightImage.jpg",
        "Assets/buttonTesters/ClickedImage.jpg");

    Button_Load(&ClickerUpgrade2, &defaultSound,
        25 * unit, 75 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/buttonTesters/NormalImage.jpg",
        "Assets/buttonTesters/HighlightImage.jpg",
        "Assets/buttonTesters/ClickedImage.jpg");

    Button_Load(&ClickerUpgrade3, &defaultSound,
        40 * unit, 75 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/buttonTesters/NormalImage.jpg",
        "Assets/buttonTesters/HighlightImage.jpg",
        "Assets/buttonTesters/ClickedImage.jpg");

    Button_Load(&TroopButton1, &defaultSound,
        10 * unit, 95 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/buttonTesters/NormalImage.jpg",
        "Assets/buttonTesters/HighlightImage.jpg",
        "Assets/buttonTesters/ClickedImage.jpg");

    Button_Load(&TroopButton2, &defaultSound,
        25 * unit, 95 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/buttonTesters/NormalImage.jpg",
        "Assets/buttonTesters/HighlightImage.jpg",
        "Assets/buttonTesters/ClickedImage.jpg");

    Button_Load(&TroopButton3, &defaultSound,
        40 * unit, 95 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/buttonTesters/NormalImage.jpg",
        "Assets/buttonTesters/HighlightImage.jpg",
        "Assets/buttonTesters/ClickedImage.jpg");
}


void Main_Scene_Update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(255, 128, 128, 255));

    Button_Behavior(&ClickerButton);
    Button_Behavior(&SettingButton);
    Button_Behavior(&ClickerUpgrade1);
    Button_Behavior(&ClickerUpgrade2);
    Button_Behavior(&ClickerUpgrade3);
    Button_Behavior(&TroopButton1);
    Button_Behavior(&TroopButton2);
    Button_Behavior(&TroopButton3);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(12*unit);
    sprintf_s(moneyString, 10, "%.0f", currentMoney);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText(moneyString,25*unit, 10*unit);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BOTTOM);
    CP_Settings_TextSize(3 * unit);
    sprintf_s(statisticString, 100, "Click Power : %d Passive Income : %.0f ", clickPower,passiveIncome);
    CP_Font_DrawText(statisticString, 24 * unit, 65 * unit);

    CP_Settings_TextSize(4 * unit);
    CP_Font_DrawText("50", 10 * unit, 70 * unit);
    CP_Font_DrawText("Cost 2", 25 * unit, 70 * unit);
    CP_Font_DrawText("Cost 3", 40 * unit, 70 * unit);
    CP_Font_DrawText("Cost 4", 10 * unit, 90 * unit);
    CP_Font_DrawText("Cost 5", 25 * unit, 90 * unit);
    CP_Font_DrawText("Cost 6", 40 * unit, 90 * unit);

    if (ClickerButton.isClicked == 1) {
        One_Click(&currentMoney);
    }

    if (ClickerUpgrade1.isClicked == 1)
    {
        if (Purchase_System(&currentMoney, 50))
        {
            Click_Upgrade();
        }
        else
        {
        }
    }

    if (CP_Input_KeyDown(KEY_Q))CP_Engine_Terminate();

}

void Main_Scene_Exit(void)
{
	CP_Font_Free(myFont);
    Button_Free(&ClickerButton);
    Button_Free(&SettingButton);
    Button_Free(&ClickerUpgrade1);
    Button_Free(&ClickerUpgrade2);
    Button_Free(&ClickerUpgrade3);
    Button_Free(&TroopButton1);
    Button_Free(&TroopButton2);
    Button_Free(&TroopButton3);
}