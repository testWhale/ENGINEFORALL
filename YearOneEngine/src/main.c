//---------------------------------------------------------
// file:	main.c
// author:	[NAME]
// email:	[DIGIPEN EMAIL ADDRESS]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// Copyright � 2020 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "scenes/mainmenu.h"
#include "scenes/mainscene.h"
 //test
// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_Engine_SetNextGameState(Main_Scene_Init, Main_Scene_Update, Main_Scene_Exit);
	
	CP_System_SetWindowSize(1920, 1080);
	
	CP_Engine_Run(1);
	return 0;
}
