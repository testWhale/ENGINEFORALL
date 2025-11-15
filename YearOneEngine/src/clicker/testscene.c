#include "cprocessing.h"
#include "utils/utils.h"
#include "testscene.h"
#include "test.h"
#include "economy/economyCode.h"
#include "buttons/buttonCode.h"
#include "utils/arr.h"
#include <stdio.h>
CP_Image Overlay;

ButtonInfo testbutton, purchaseButton, purchaseButton2, arrayButton;
ButtonSound defaultSound;
CP_Font myFont;
float winWidth;
float winHeight;
float unit;


void Test_Scene_Init(void)
{   
    CP_System_Fullscreen();
    winHeight = CP_System_GetWindowHeight();
    winWidth = CP_System_GetWindowWidth();
    unit = CP_System_GetWindowWidth()/ 192.0f;
    printf("%f \n %f\n %f\n", winHeight, winWidth,unit );
    Overlay = CP_Image_Load("Assets/ConceptArt.jpg");
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");

    Button_Sound_Load(&defaultSound, "Assets/soundTesters/ClickSound.wav", "Assets/soundTesters/HoverSound.wav", "Assets/soundTesters/ReleaseSound.wav");
    Button_Load(&purchaseButton, &defaultSound, 800, 800, 200, 200, 200, "Assets/buttonTesters/CircleNormal.png", "Assets/buttonTesters/CircleClicked.png", "Assets/buttonTesters/CircleHighlight.png");
    Button_Load(&purchaseButton2, &defaultSound, 1100, 800, 200, 200, 200, "Assets/buttonTesters/CircleNormal.png", "Assets/buttonTesters/CircleClicked.png", "Assets/buttonTesters/CircleHighlight.png");
    Button_Load(&testbutton, &defaultSound, 500, 500, 300, 300, 0, "Assets/buttonTesters/NormalImage.jpg", "Assets/buttonTesters/HighlightImage.jpg", "Assets/buttonTesters/ClickedImage.jpg");
    Button_Load(&arrayButton, &defaultSound, 1000, 500, 300, 300, 0, "Assets/buttonTesters/Catboy3.jpg", "Assets/buttonTesters/Catboy.png", "Assets/buttonTesters/Catboy2.jpg");
    
}


void Test_Scene_Update(void)
{


    CP_Graphics_ClearBackground(CP_Color_Create(255, 128, 128, 255));

    CP_Settings_TextSize(20.0f);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    sprintf_s(moneyString, 100, "Money: %.0f\n Click Power:%d\n Passive Income:%.0f\n ", currentMoney, clickPower, passiveIncome);

    // 3. Now, draw the string that's in your buffer
    CP_Font_DrawText(moneyString, winWidth/2, winHeight/2);
    Passive_System(&currentMoney);
   


    



    Button_Behavior(&purchaseButton2);
    Button_Behavior(&purchaseButton);
    Button_Behavior(&testbutton);
    Button_Behavior(&arrayButton);
    if (testbutton.isClicked ==1) {
        One_Click(&currentMoney);
    }

    if (purchaseButton.isClicked == 1) 
    {
        if(Purchase_System(&currentMoney, 50))
        {
         Click_Upgrade();
         clickPurchaseAmount += 1;
        }
    }

    if (purchaseButton2.isClicked == 1)
    {
        if (Purchase_System(&currentMoney, 100))
        {
            Passive_Upgrade();
        }
    }
   CP_Settings_ImageMode(CP_POSITION_CORNER);
   CP_Image_Draw(Overlay, 0, 0, 192 * unit, 108 * unit, 51);
    if (CP_Input_KeyDown(KEY_Q))CP_Engine_Terminate();
}

void Test_Scene_Exit(void)
{
	CP_Font_Free(myFont);
}