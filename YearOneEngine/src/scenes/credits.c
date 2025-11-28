//---------------------------------------------------------
// file:	credits.h
// author:	[Quak June Hao (Quinn)]
// email:	[quak.j@digipen.edu]
//
// brief:	This code contains the behavior for the credits section of the game
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include "utils/utils.h"
#include "scenes/mainmenu.h"
#include "buttons/buttonCode.h"

CP_Font myFont;
CP_Image MainMenuBackground,Credits;
ButtonInfo BackButton;
ButtonSound defaultSound;
char CreditsString[100];
float unit;
float CreditsY;
CP_Image logo = NULL;
static float elapsed = 0.0f;          // time since screen started
static const float FADE_DURATION = 3.0f;  // 3 seconds fade
static float fadeOutStart = 3.0f;      // seconds
static float fadeOutDuration = 0.5f;   // quick fade-out
CP_Sound creditMusic;

void Credits_Init(void)
{
    creditMusic = CP_Sound_LoadMusic("Assets/Sound_Effects/cred.mp3");
    CP_Sound_PlayAdvanced(creditMusic, 1.0f, 1.0f, TRUE, CP_SOUND_GROUP_0);

    unit = CP_System_GetWindowWidth() / 192.0f;
    myFont = CP_Font_Load("Assets/Fonts/QuinnDoodle.ttf");
    MainMenuBackground = CP_Image_Load("Assets/Misc/MenuScreen2.png");
    Credits = CP_Image_Load("Assets/Misc/Credits.png");
    CreditsY = 150 * unit;

    Button_Sound_Load(&defaultSound,
        "Assets/Sound_Effects/clickSound.mp3",
        "Assets/Sound_Effects/hoverSound.mp3",
        "Assets/Sound_Effects/releaseSound.mp3");

    Button_Load(&BackButton, &defaultSound,
        156 * unit, 92 * unit,
        55 * unit, 19.5 * unit,
        0 * unit,
        "Assets/Buttons/Back/BackNormal.png",
        "Assets/Buttons/Back/BackHighlighted.png",
        "Assets/Buttons/Back/BackClicked.png", 1);
    
    elapsed = 0; // reset timer
    logo = CP_Image_Load("Assets/Misc/DigiPen_BLACK.png");
    if (logo == NULL)
    {
        CP_System_SetWindowTitle("Error: Failed to load DigiPen_BLACK.png");
    }
}

void Credits_Update(void)
{
    

    CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(MainMenuBackground, 0, 0, 192 * unit, 108 * unit, 255);
    
    elapsed += CP_System_GetDt();

    float alpha = 0.0f;

    if (elapsed < FADE_DURATION)
    {
        // Fade in: 0 to 255
        alpha = (elapsed / FADE_DURATION) * 255.0f;
    }
    else if (elapsed < fadeOutStart)
    {
        // Hold full visibility
        alpha = 255.0f;
    }
    else
    {
        // Fade out: 255 to 0
        float t = (elapsed - fadeOutStart) / fadeOutDuration;
        if (t > 1.0f) t = 1.0f;

        alpha = (1.0f - t) * 255.0f;
    }

    int width = CP_System_GetWindowWidth();
    int height = CP_System_GetWindowHeight();

    // scale logo to 60% of screen width
    float drawW = width * 0.6f;
    float aspect = 445.0f / 1525.0f;
    float drawH = drawW * aspect;

    
    CP_Settings_ImageMode(CP_POSITION_CENTER);
    /* draw centered */
    CP_Image_Draw(logo,
        width * 0.5f,
        height * 0.5f,
        drawW,
        drawH,
        alpha);

    CP_Settings_ImageMode(CP_POSITION_CORNER);
    CP_Image_Draw(Credits, 0, CreditsY, 168 * unit, 700 * unit, 255);


    CreditsY -= 0.3 * unit;
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
    CP_Sound_Free(creditMusic);
    CP_Image_Free(logo);
    CP_Image_Free(Credits);
    CP_Image_Free(MainMenuBackground);
    CP_Image_Free(Credits);
    CP_Image_Free(MainMenuBackground);
}