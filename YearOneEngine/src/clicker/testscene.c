#include "cprocessing.h"
#include "utils/utils.h"
#include "testscene.h"
#include "test.h"
#include "economy/economyCode.h"
#include "clicker/clickCode.h"
#include "buttons/buttonCode.h"
#include "utils/arr.h"

ButtonInfo testbutton, purchaseButton, purchaseButton2, arrayButton;
ButtonSound defaultSound;
CP_Font myFont;
float winWidth;
float winHeight;


void Test_Scene_Init(void)
{
    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");

    Button_Sound_Load(&defaultSound, "Assets/soundTesters/ClickSound.wav", "Assets/soundTesters/HoverSound.wav", "Assets/soundTesters/ReleaseSound.wav");
    Button_Load(&purchaseButton, &defaultSound, 800, 800, 200, 200, 200, "Assets/buttonTesters/CircleNormal.png", "Assets/buttonTesters/CircleClicked.png", "Assets/buttonTesters/CircleHighlight.png");
    Button_Load(&purchaseButton2, &defaultSound, 1100, 800, 200, 200, 200, "Assets/buttonTesters/CircleNormal.png", "Assets/buttonTesters/CircleClicked.png", "Assets/buttonTesters/CircleHighlight.png");
    Button_Load(&testbutton, &defaultSound, 500, 500, 300, 300, 0, "Assets/buttonTesters/NormalImage.jpg", "Assets/buttonTesters/HighlightImage.jpg", "Assets/buttonTesters/ClickedImage.jpg");
    Button_Load(&arrayButton, &defaultSound, 1000, 500, 300, 300, 0, "Assets/buttonTesters/NormalImage.jpg", "Assets/buttonTesters/HighlightImage.jpg", "Assets/buttonTesters/ClickedImage.jpg");
    
}


void Test_Scene_Update(void)
{

    winHeight = CP_System_GetWindowHeight();
    winWidth = CP_System_GetWindowWidth();
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

}

void Test_Scene_Exit(void)
{
	CP_Font_Free(myFont);
}