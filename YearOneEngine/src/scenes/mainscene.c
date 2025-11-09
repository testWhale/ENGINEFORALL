#include "cprocessing.h"
#include "utils/utils.h"
#include "mainscene.h"

#include "economy/economyCode.h"
#include "clicker/clickCode.h"
#include "buttons/buttonCode.h"
#include "utils/arr.h"
#include "tile/tile.h"
#include "entity/ent.h"
#include "goal/goal.h"

/*Cleanup Xav*/
//#include "test.h"
#include "health.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
CP_Image Overlay;
CP_Image Background,TileMap;

ButtonInfo ClickerButton, PauseButton;
ButtonInfo ClickerUpgrade1, ClickerUpgrade2, ClickerUpgrade3;
ButtonInfo TroopButton1, TroopButton2, TroopButton3;
ButtonSound defaultSound;
CP_Font myFont;
float unit;

int g_drawGoals = 1;
float g_goalRadius = 0.0f;

void Main_Scene_Init(void)
{   
    //CP_System_Fullscreen();
    srand((unsigned)time(NULL));
    /*CP_System_Fullscreen();*/
    float winHeight = CP_System_GetWindowHeight();
    float winWidth = CP_System_GetWindowWidth();
    //CP_System_Fullscreen();
    unit = CP_System_GetWindowWidth()/ 192.0f;
    myFont = CP_Font_Load("Assets/Fonts/QuinnDoodle.ttf");
    Background = CP_Image_Load("Assets/Misc/BackgroundArt.png");
    TileMap = CP_Image_Load("Assets/Misc/TileMap.jpg");


    Button_Sound_Load(&defaultSound, 
        "Assets/soundTesters/ClickSound.wav", 
        "Assets/soundTesters/HoverSound.wav", 
        "Assets/soundTesters/ReleaseSound.wav");


    Button_Load(&ClickerButton, &defaultSound, 
        25 * unit, 40 * unit, 
        40 * unit, 40 * unit,
        40 * unit,
        "Assets/Buttons/Clicker/ClickerNormal.png", 
        "Assets/Buttons/Clicker/ClickerHighlight.png", 
        "Assets/Buttons/Clicker/ClickerClicked2.png");

    Button_Load(&PauseButton, &defaultSound, 
        182 * unit, 10 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/Pause/PauseNormal.png", 
        "Assets/Buttons/Pause/PauseHighlight.png",
        "Assets/Buttons/Pause/PauseClicked.png");


    Button_Load(&ClickerUpgrade1, &defaultSound,
        10 * unit, 80 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/ClickerUpgrade1/ClickerUpgrade1Normal.png",
        "Assets/Buttons/ClickerUpgrade1/ClickerUpgrade1Highlight.png",
        "Assets/Buttons/ClickerUpgrade1/ClickerUpgrade1Clicked.png");

    Button_Load(&ClickerUpgrade2, &defaultSound,
        25 * unit, 80 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/ClickerUpgrade2/ClickerUpgrade2Normal.png",
        "Assets/Buttons/ClickerUpgrade2/ClickerUpgrade2Highlight.png",
        "Assets/Buttons/ClickerUpgrade2/ClickerUpgrade2Clicked.png");

    Button_Load(&ClickerUpgrade3, &defaultSound,
        40 * unit, 80* unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/ClickerUpgrade3/ClickerUpgrade3Normal.png",
        "Assets/Buttons/ClickerUpgrade3/ClickerUpgrade3Highlight.png",
        "Assets/Buttons/ClickerUpgrade3/ClickerUpgrade3Clicked.png");

    Button_Load(&TroopButton1, &defaultSound,
        10 * unit, 100 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/Troops1/Troops1Normal.png",
        "Assets/Buttons/Troops1/Troops1Highlight.png",
        "Assets/Buttons/Troops1/Troops1Clicked.png");

    Button_Load(&TroopButton2, &defaultSound,
        25 * unit, 100* unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/Troops2/Troops2Normal.png",
        "Assets/Buttons/Troops2/Troops2Highlight.png",
        "Assets/Buttons/Troops2/Troops2Clicked.png");

    Button_Load(&TroopButton3, &defaultSound,
        40 * unit, 100 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/Troops3/Troops3Normal.png",
        "Assets/Buttons/Troops3/Troops3Highlight.png",
        "Assets/Buttons/Troops3/Troops3Clicked.png");
    Map_Init((CP_Vector) {66*unit, 24*unit },108*unit, 72*unit);
    initPlayerDemo();

    /* HEALTH FUNCTIONS */
    Hearts_Init(3);
    HealthAudio_Load("Assets/Metal Ping by timgormly Id-170957.wav",
        "Assets/Glass Break by unfa Id-221528.wav");

    extern void GameOver_SetData(float, int);
    extern void GameOver_Init(void);
    extern void GameOver_Update(void);
    extern void GameOver_Exit(void);
    Health_BindGameOver(GameOver_SetData, GameOver_Init, GameOver_Update, GameOver_Exit);
    HealthTimer_Reset();
    setGoal();
    /*Test_Init();*/
        
}


void Main_Scene_Update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(255, 128, 128, 255));
    float dt = CP_System_GetDt();
   
    HealthTimer_Update(dt); /*Health Icons*/
    Hearts_Update(dt); /*Health Icons*/

    DamageEnemiesOnPlayerCollisions(34, 0.30f, dt);
    ProcessGoalHits();

    if (g_drawGoals) {
            /*CP_Settings_Fill(CP_Color_Create(0, 0, 0, 0));
            CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 160));
            CP_Settings_StrokeWeight(3.0f);*/
            for (int r = 0; r < TILE_ROWS; ++r)
            CP_Graphics_DrawCircle(g_goalCenters[r].x, g_goalCenters[r].y, g_goalRadius * 2.0f);
    }

    Hearts_Draw();

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(28.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_RIGHT, CP_TEXT_ALIGN_V_TOP);

    char tbuf[48];
    snprintf(tbuf, sizeof(tbuf), "Time: %.1fs", HealthTimer_Seconds());

    float pad = 12.0f;
    float tx = (float)CP_System_GetWindowWidth() - pad;
    CP_Font_DrawText(tbuf, tx, pad);
    //done
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(Background, 0, 0, 192 * unit, 108 * unit, 255);
    CP_Settings_ImageMode(CP_POSITION_CENTER);
    CP_Image_Draw(TileMap, 120*unit, 60*unit, 108 * unit, 72 * unit, 255);
    //Test_Update();

    Button_Behavior(&ClickerButton);
    Button_Behavior(&PauseButton);
    Button_Behavior(&ClickerUpgrade1);
    Button_Behavior(&ClickerUpgrade2);
    Button_Behavior(&ClickerUpgrade3);
    Button_Behavior(&TroopButton1);
    Button_Behavior(&TroopButton2);
    Button_Behavior(&TroopButton3);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(9*unit);
    sprintf_s(moneyString, 10, "%.0f$", currentMoney);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText(moneyString,25*unit, 10*unit);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BOTTOM);
    CP_Settings_TextSize(4 * unit);
    sprintf_s(statisticString, 100, "Click Power : %d ", clickPower);
    sprintf_s(statisticString2, 100, "Passive Income : %.1f", passiveIncome/5);
    CP_Font_DrawText(statisticString, 24 * unit, 65 * unit);
    CP_Font_DrawText(statisticString2, 24 * unit, 70 * unit);

    CP_Settings_TextSize(4 * unit);

    sprintf_s(clicker1Cost, 100, "%.0f$ ", Scaling_Cost(clickerUpgrade1Count, 50));
    sprintf_s(clicker2Cost, 100, "%.0f$ ", Scaling_Cost(clickerUpgrade2Count, 10));
    sprintf_s(troop1Cost, 100, "%.0f$ ", Scaling_Cost(troop1Count, 50));
    sprintf_s(troop2Cost, 100, "%.0f$ ", Scaling_Cost(troop2Count, 50));
    sprintf_s(troop3Cost, 100, "%.0f$ ", Scaling_Cost(troop3Count, 50));
    CP_Font_DrawText(clicker1Cost, 10 * unit, 75 * unit);
    CP_Font_DrawText(clicker2Cost, 25 * unit, 75 * unit);
    CP_Font_DrawText("Cost 3", 40 * unit, 75 * unit);
    CP_Font_DrawText(troop1Cost, 10 * unit, 95 * unit);
    CP_Font_DrawText(troop2Cost, 25 * unit, 95 * unit);
    CP_Font_DrawText(troop3Cost, 40 * unit, 95 * unit);

    Map_Update(); /*Tile Map*/

    DrawEntities(); /*Draw Players & Enemies*/
    
    Draw_TempText(dt); /* Flag check that displays a temporary msg/ reward */

    if (ClickerButton.isClicked == 1) {
        One_Click(&currentMoney);
    }

    if (ClickerUpgrade1.isClicked == 1)
    {
        if (Purchase_System(&currentMoney, Scaling_Cost(clickerUpgrade1Count, 50)))
        {
            clickerUpgrade1Count += 1;
            Click_Upgrade();
        }
    }

    if (ClickerUpgrade2.isClicked == 1)
    {
        if (Purchase_System(&currentMoney, Scaling_Cost(clickerUpgrade2Count, 10)))
        {
            clickerUpgrade2Count += 1;
            Passive_Upgrade();
        }
    }
    if (TroopButton1.isClicked == 1)
    {
        if (Purchase_System(&currentMoney, Scaling_Cost(troop1Count, 50)))
        {
            GameEntity player = MakeTemplate("player");
            Arr_Insert(&playerArr, (ActiveEntity) {
                playerArr.used,
                    player, (StateMachine) { .currState = IdleState },
                    .maxHealth=100, .health = 100, .alive = 1, .hasScored = 0, .lastLeftmostX = 0
            });
            troop1Count += 1;
        }
    }

    if (TroopButton2.isClicked == 1)
    {
        if (Purchase_System(&currentMoney, Scaling_Cost(troop2Count, 50)))
        {
            GameEntity player = MakeTemplate("player");
            Arr_Insert(&playerArr, (ActiveEntity) { playerArr.used, 
                player, (StateMachine) { .currState = IdleState },
                .maxHealth = 100, .health = 100, .alive = 1, .hasScored = 0, .lastLeftmostX = 0
            });
            troop2Count += 1;
        }
    }

    if (TroopButton3.isClicked == 1)
    {
        if (Purchase_System(&currentMoney, Scaling_Cost(troop3Count, 50)))
        {
            GameEntity player = MakeTemplate("player");
            Arr_Insert(&playerArr, (ActiveEntity) { playerArr.used, 
                player, (StateMachine) { .currState = IdleState },
                .maxHealth = 100, .health = 100, .alive = 1, .hasScored = 0, .lastLeftmostX = 0
            });
            troop3Count += 1;
        }
    }
    


    Passive_System(&currentMoney);
    if (CP_Input_KeyDown(KEY_Q))CP_Engine_Terminate();

   

}

void Main_Scene_Exit(void)
{
    //Test_Exit();
	CP_Font_Free(myFont);
    Button_Free(&ClickerButton);
    Button_Free(&PauseButton);
    Button_Free(&ClickerUpgrade1);
    Button_Free(&ClickerUpgrade2);
    Button_Free(&ClickerUpgrade3);
    Button_Free(&TroopButton1);
    Button_Free(&TroopButton2);
    Button_Free(&TroopButton3);
    Button_Sound_Free(&defaultSound);
}