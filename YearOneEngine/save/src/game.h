#include "cprocessing.h"
#include <stdio.h>

// Horizontal position of the square
float x_pos;

void game_init()
{
    // Start the square at the left of the screen
    x_pos = 0;
    // Set the square to draw yellow
    CP_Settings_Fill(CP_Color_Create(255, 255, 0, 255));
}

void game_update()
{
    // Set background to black
    CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
    // Draw the square
    CP_Graphics_DrawRect(x_pos, CP_System_GetWindowHeight() / 2.0f, 100, 100);
    x_pos += 2;
    // If space pressed, reset the state
    if (CP_Input_KeyTriggered(KEY_SPACE))
        CP_Engine_SetNextGameStateForced(game_init, game_update, NULL);
    else if (CP_Input_KeyTriggered(KEY_Q))
        CP_Engine_Terminate();
}