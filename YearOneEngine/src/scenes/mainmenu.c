//---------------------------------------------------------
// file:	mainmenu.c
// author:	[Quak June Hao (Quinn)][Zachary Ng][Ding Yi Chaw Maung]
// email:	[quak.j@digipen.edu][zacharyhuaen.n@digipen.edu][dingyichaw.maung@digipen.edu]
//
// brief:	Contains the function definitions for 
//			all in game behaviour
//
// Copyright 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include "utils/utils.h"
#include "mainmenu.h"
#include "scenes/mainscene.h"
#include "scenes/credits.h"
#include "buttons/buttonCode.h"
#include "scenes/tutorial.h"
#include "scenes/settings.h"



CP_Font myFont;
CP_Image MainMenuBackground;
ButtonInfo PlayButton, CreditsButton, QuitButton, SettingsButton;
ButtonSound defaultSound;
CP_Sound menuMusic;

void Main_Menu_Init(void)
{
    menuMusic = CP_Sound_LoadMusic("Assets/Sound_Effects/mainmenu.wav");
    CP_Sound_PlayAdvanced(menuMusic, 1.0f, 1.0f, TRUE, CP_SOUND_GROUP_0);

    //CP_System_Fullscreen();
    unit = CP_System_GetWindowWidth() / 192.0f;
    myFont = CP_Font_Load("Assets/Fonts/QuinnDoodle.ttf");
    MainMenuBackground = CP_Image_Load("Assets/Misc/MenuScreen.png");


    Button_Sound_Load(&defaultSound,
        "Assets/Sound_Effects/ClickSound.wav",
        "Assets/Sound_Effects/HoverSound.wav",
        "Assets/Sound_Effects/ReleaseSound.wav");

    Button_Load(&PlayButton, &defaultSound,
        36 * unit, 92 * unit,
        55 * unit, 19.5 * unit,
        0 * unit,
        "Assets/Buttons/MainMenu/PlayNormal.png",
        "Assets/Buttons/MainMenu/PlayHighlight.png",
        "Assets/Buttons/MainMenu/PlayClicked.png", 1);

    Button_Load(&CreditsButton, &defaultSound,
        96 * unit, 92 * unit,
        55 * unit, 19.5 * unit,
        0 * unit,
        "Assets/Buttons/MainMenu/CreditsNormal.png",
        "Assets/Buttons/MainMenu/CreditsHighlight.png",
        "Assets/Buttons/MainMenu/CreditsClicked.png", 1);

    Button_Load(&QuitButton, &defaultSound,
        156 * unit, 92 * unit,
        55 * unit, 19.5 * unit,
        0 * unit,
        "Assets/Buttons/MainMenu/QuitNormal.png",
        "Assets/Buttons/MainMenu/QuitHighlight.png",
        "Assets/Buttons/MainMenu/QuitClicked.png", 1);
}

void Main_Menu_Update(void)
{

    CP_Graphics_ClearBackground(CP_Color_Create(255, 128, 128, 255));
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(MainMenuBackground, 0, 0, 192 * unit, 108 * unit, 255);


    Button_Behavior(&PlayButton);
    Button_Behavior(&CreditsButton);
    Button_Behavior(&QuitButton);

    if (PlayButton.isClicked)
    {
        CP_Engine_SetNextGameState(Tutorial_Init, Tutorial_Update, Tutorial_Exit);
    }

    if (CreditsButton.isClicked)
    {
        CP_Engine_SetNextGameState(Credits_Init, Credits_Update, Credits_Exit);
    }


    if (QuitButton.isClicked)
    {
        CP_Engine_Terminate();
    }
}

void Main_Menu_Exit(void)
{
    CP_Font_Free(myFont);
    Button_Free(&PlayButton);
    Button_Free(&CreditsButton);
    Button_Free(&QuitButton);
    CP_Sound_Free(menuMusic);
    CP_Image_Free(MainMenuBackground);

    Button_Sound_Free(&defaultSound);
}