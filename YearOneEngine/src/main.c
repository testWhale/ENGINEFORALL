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
#include "mainmenu.h"
#include "clicker/testscene.h"
 
 //test
// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_Engine_SetNextGameState(Test_Scene_Init, Test_Scene_Update, Test_Scene_Exit);
	CP_System_SetWindowSize(1600, 900);
	CP_Engine_Run(1);
	return 0;
}
