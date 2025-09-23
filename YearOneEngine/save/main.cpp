#include "cprocessing.h"
#include <stdio.h>
#include "./src/loadingScreen.h" 


void preUpdate()
{
    
    // Change the fill color
    CP_Settings_Fill(CP_Color_Create(187, 24, 211, 255));
}

int main(void)
{
    // Set the initial game state
    CP_Engine_SetNextGameState(loadScrn_init, loadScrn_update, NULL);
    
    // Run the program
    CP_Engine_Run(1);
}


