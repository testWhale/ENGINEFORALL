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
#include "Utils/UI/Pause.h"
#include "nuke/nuke.h"
#include "health.h"
#include "utils/wave/wave.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "gameover.h"
#include "mainmenu.h"

CP_Image Overlay;
CP_Image Background, TileMap;
CP_Image ClickerInfo,PassiveInfo,BlankInfo,PoisonInfo,NormalInfo,WinInfo;

ButtonInfo ClickerButton, PauseButton;
ButtonInfo ClickerUpgrade1, ClickerUpgrade2, ClickerUpgrade3;
ButtonInfo TroopButton1, TroopButton2, TroopButton3;
ButtonSound defaultSound;
CP_Font myFont;
float unit;

static HealthSystem gHealth;

void Main_Scene_Init(void)
{
    srand((unsigned)time(NULL));

    unit = CP_System_GetWindowWidth() / 192.0f;
    myFont = CP_Font_Load("Assets/Fonts/QuinnDoodle.ttf");
    Background = CP_Image_Load("Assets/Misc/BackgroundArt.png");
    TileMap = CP_Image_Load("Assets/Misc/TileMap.jpg");

    ClickerInfo = CP_Image_Load("Assets/Misc/InfoBoxes/ClickPowerInfo.png");
    PassiveInfo = CP_Image_Load("Assets/Misc/InfoBoxes/PassivePowerInfo.png");
    BlankInfo = CP_Image_Load("Assets/Misc/InfoBoxes/EMPTYINFO.png");
    PoisonInfo = CP_Image_Load("Assets/Misc/InfoBoxes/RadioCat.png");
    NormalInfo = CP_Image_Load("Assets/Misc/InfoBoxes/NormalCatInfo.png");
    WinInfo = CP_Image_Load("Assets/Misc/InfoBoxes/WinInfo.png");

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
        "Assets/Buttons/Clicker/ClickerClicked2.png", 1);

    Button_Load(&PauseButton, &defaultSound,
        182 * unit, 10 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/Pause/PauseNormal.png",
        "Assets/Buttons/Pause/PauseHighlight.png",
        "Assets/Buttons/Pause/PauseClicked.png", 1);

    Button_Load(&ClickerUpgrade1, &defaultSound,
        10 * unit, 80 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/ClickerUpgrade1/ClickerUpgradeNormal.png",
        "Assets/Buttons/ClickerUpgrade1/ClickerUpgradeHighlight.png",
        "Assets/Buttons/ClickerUpgrade1/ClickerUpgradeClicked.png", 1);

    Button_Load(&ClickerUpgrade2, &defaultSound,
        25 * unit, 80 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/ClickerUpgrade2/ClickerUpgrade2Normal.png",
        "Assets/Buttons/ClickerUpgrade2/ClickerUpgrade2Highlight.png",
        "Assets/Buttons/ClickerUpgrade2/ClickerUpgrade2Clicked.png", 1);

    Button_Load(&ClickerUpgrade3, &defaultSound,
        40 * unit, 80 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/ClickerUpgrade3/NukeNormal.png",
        "Assets/Buttons/ClickerUpgrade3/NukeHighlight.png",
        "Assets/Buttons/ClickerUpgrade3/NukeClicked.png", 1);

    Button_Load(&TroopButton1, &defaultSound,
        10 * unit, 100 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/Troops1/PoisonCatNormal.png",
        "Assets/Buttons/Troops1/PoisonCatHighlight.png",
        "Assets/Buttons/Troops1/PoisonCatClicked.png", 1);

    Button_Load(&TroopButton2, &defaultSound,
        25 * unit, 100 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/Troops2/NormalCatNormal.png",
        "Assets/Buttons/Troops2/NormalCatHighlight.png",
        "Assets/Buttons/Troops2/NormalCatClicked.png", 1);

    Button_Load(&TroopButton3, &defaultSound,
        40 * unit, 100 * unit,
        10 * unit, 10 * unit,
        0 * unit,
        "Assets/Buttons/Troops3/Troops3Normal.png",
        "Assets/Buttons/Troops3/Troops3Highlight.png",
        "Assets/Buttons/Troops3/Troops3Clicked.png", 1);

    Load_TempText();
    Map_Init((CP_Vector) { 66 * unit, 24 * unit }, 108 * unit, 72 * unit);
    Init_PlayerDemo();

    HealthSystem_Init(&gHealth, 3, 3);
    HealthAudio_Load(
        "Assets/soundTesters/Metal Ping by timgormly Id-170957.wav",
        "Assets/soundTesters/Glass Break by unfa Id-221528.wav");
    HealthSystem_ResetTimer(&gHealth);

    Goal_InitFromTileMap(0.45f, 0.25f);

    Pause_Init();
    setup("Assets/Map/TM2.png", "Assets/Map/Test3.png");
}

void Main_Scene_Update(void)
{
    CP_Graphics_ClearBackground(CP_Color_Create(255, 128, 128, 255));
    float dt = Pause_Dt(CP_System_GetDt());

    Button_Behavior(&PauseButton);
    if (PauseButton.isClicked)
    {
        Pause_SetPaused(1);
        PauseButton.isClicked = 0;
    }

    HealthSystem_Update(&gHealth, dt);

    if (!Pause_IsPaused()) {
        ProcessGoalHits(&gHealth);
        Health_DamagePlayersOnEnemyCollisions(
            10, 
            3.0f,   
            dt);
    }

    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(Background, 0, 0, 192 * unit, 108 * unit, 255);

    CP_Settings_ImageMode(CP_POSITION_CENTER);
    CP_Image_Draw(TileMap, 120 * unit, 60 * unit, 108 * unit, 72 * unit, 255);

    Map_Update();
    //draw(120, 60, 108, 72, 255);

    Draw_Entities();    


    if (CP_Input_KeyDown(KEY_T))
    {
        Kill_NewWave();
    }
    if (!Pause_IsPaused())
    {
        Button_Behavior(&ClickerButton);
        Button_Behavior(&ClickerUpgrade1);
        Button_Behavior(&ClickerUpgrade2);
        Button_Behavior(&ClickerUpgrade3);
        Button_Behavior(&TroopButton1);
        Button_Behavior(&TroopButton2);
        Button_Behavior(&TroopButton3);
    }
    else
    {
        Draw_Button_Normal(&ClickerButton);
        Draw_Button_Normal(&ClickerUpgrade1);
        Draw_Button_Normal(&ClickerUpgrade2);
        Draw_Button_Normal(&ClickerUpgrade3);
        Draw_Button_Normal(&TroopButton1);
        Draw_Button_Normal(&TroopButton2);
        Draw_Button_Normal(&TroopButton3);
    }

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(9 * unit);
    sprintf_s(moneyString, 10, "%.0f$", currentMoney);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Font_DrawText(moneyString, 25 * unit, 10 * unit);

    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_BOTTOM);
    CP_Settings_TextSize(4 * unit);
    sprintf_s(statisticString, 100, "Click Power : %d ", clickPower);
    sprintf_s(statisticString2, 100, "Passive Income : %.1f", passiveIncome);
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
    CP_Font_DrawText("1000$", 40 * unit, 75 * unit);
    CP_Font_DrawText("50", 10 * unit, 95 * unit);
    CP_Font_DrawText("50", 25 * unit, 95 * unit);
    CP_Font_DrawText("50", 40 * unit, 95 * unit);

    if (!Pause_IsPaused())
    {
        if (ClickerUpgrade1.isSel == 1)
        {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(ClickerInfo, 30 * unit, 75 * unit, 32 * unit, 21 * unit, 255);
        }

        if (ClickerUpgrade2.isSel == 1)
        {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(PassiveInfo, 45 * unit, 75 * unit, 32 * unit, 21 * unit, 255);
        }

        if (ClickerUpgrade3.isSel == 1)
        {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(WinInfo, 60 * unit, 75 * unit, 32 * unit, 21 * unit, 255);
        }

        if (TroopButton1.isSel == 1)
        {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(PoisonInfo, 30 * unit, 95 * unit, 32 * unit, 21 * unit, 255);
        }

        if (TroopButton2.isSel == 1)
        {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(NormalInfo, 45 * unit, 95 * unit, 32 * unit, 21 * unit, 255);
        }

        if (TroopButton3.isSel == 1)
        {
            CP_Settings_ImageMode(CP_POSITION_CENTER);
            CP_Image_Draw(BlankInfo, 60 * unit, 95 * unit, 32 * unit, 21 * unit, 255);
        }

        //click for currency
        if (ClickerButton.isClicked == 1) {
            One_Click(&currentMoney);
        }

        //normal click upgrade
        if (ClickerUpgrade1.isClicked == 1) {
            if (Purchase_System(&currentMoney, Scaling_Cost(clickerUpgrade1Count, 50))) {
                clickerUpgrade1Count += 1;
                Click_Upgrade();
            }
        }

        //passive income upgrade
        if (ClickerUpgrade2.isClicked == 1) {
            if (Purchase_System(&currentMoney, Scaling_Cost(clickerUpgrade2Count, 10))) {
                clickerUpgrade2Count += 1;
                Passive_Upgrade();
            }
        }

        //nuke
        if (ClickerUpgrade3.isClicked == 1) {
            if (Purchase_System(&currentMoney, 1000)) {
                CP_Engine_SetNextGameState(Nuke_Init, Nuke_Update, Nuke_Exit);
            }
        }

        //poison turret
        if (TroopButton1.isClicked == 1) {
            if (Purchase_System(&currentMoney,  50)) {
                GameEntity player = Make_Template("poison");
                // compute layout
                int spacing = 60;
                int iconsPerRow = 12;

                int offset = playerArr.used;
                int row = offset % 3;
                int col = offset / 3;

                player.centerPos.x = 550 + col * spacing;
                player.centerPos.y = 50 + row * 50;

                Arr_Insert(&playerArr, (ActiveEntity) {
                    playerArr.used,
                        player, (StateMachine) { .currState = IdleState },
                        .maxHealth = 100, .health = 100,
                        .alive = 1, .hasScored = 0, .lastLeftmostX = 0
                });
                troop1Count += 1;
            }
        }

        //normal turret
        if (TroopButton2.isClicked == 1) {
            if (Purchase_System(&currentMoney, 50)) {
                GameEntity player = Make_Template("player");

                // compute layout
                int spacing = 60;
                int iconsPerRow = 12;

                int offset = playerArr.used;
                int row = offset % 3;
                int col = offset / 3;

                player.centerPos.x = 550 + col * spacing;
                player.centerPos.y = 50 + row * 50;

                Arr_Insert(&playerArr, (ActiveEntity) {
                    playerArr.used,
                        player, (StateMachine) { .currState = IdleState },
                        .maxHealth = 100, .health = 100,
                        .alive = 1, .hasScored = 0, .lastLeftmostX = 0
                });
                troop2Count += 1;
            }
        }

        //stun turret
        if (TroopButton3.isClicked == 1) {
            if (Purchase_System(&currentMoney,50)) {
                printf("WORDS\n");
                GameEntity player = Make_Template("stun");
                // compute layout
                int spacing = 60;
                int iconsPerRow = 12;

                int offset = playerArr.used;
                int row = offset % 3;
                int col = offset / 3;

                player.centerPos.x = 550 + col * spacing;
                player.centerPos.y = 50 + row * 50;

                Arr_Insert(&playerArr, (ActiveEntity) {
                    playerArr.used,
                        player, (StateMachine) { .currState = IdleState },
                        .maxHealth = 100, .health = 100,
                        .alive = 1, .hasScored = 0, .lastLeftmostX = 0
                });
                troop3Count += 1;
            }
    }
    Passive_System(&currentMoney);

    if (CP_Input_KeyDown(KEY_Q)) CP_Engine_Terminate();  
    if (CP_Input_KeyDown(KEY_W)) currentMoney += 1000;
}   

    if (HealthSystem_GetHearts(&gHealth) <= 0) {
        float finalTime = HealthSystem_GetTimer(&gHealth);
        int   moneyEarn = (int)currentMoney;

        GameOver_SetData(finalTime, moneyEarn);
        CP_Engine_SetNextGameState(GameOver_Init, GameOver_Update, GameOver_Exit);
        return;
    }

    HealthSystem_DrawHearts(&gHealth);

    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
    CP_Settings_TextSize(28.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_TOP);

    char tbuf[48];
    snprintf(tbuf, sizeof(tbuf), "Time: %.1fs", HealthSystem_GetTimer(&gHealth));
    CP_Font_DrawText(tbuf, (float)CP_System_GetWindowWidth() * 0.6f, 8.0f);

    Pause_UpdateAndDraw();
    if (Pause_TakeMenuRequest()) {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
        return;
    }

    /* UI ELEMENTS */
    Draw_WaveCounter();

    /* POPUPS DOWN Here */
    Draw_TempText(dt);
}

void Main_Scene_Exit(void)
{
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
    Del_TempText();
    wave = 0;
    currentMoney = 0;
    clickPower = 1;
    passiveIncome = 0;
    clickerUpgrade1Count = 0;
    clickerUpgrade2Count = 0;
}
