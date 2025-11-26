//---------------------------------------------------------
// file:	main.c
// author:	[Zachary Ng][Quak June Hao (Quinn)]
// email:	[zacharyhuaen.n@digipen.edu][quak.j@digipen.edu]
//
// brief:	Main entry point for the sample project
//			of the CProcessing library
//
// Copyright � 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "scenes/mainmenu.h"
#include "scenes/mainscene.h"
#include "scenes/logo.h"
#include "scenes/tutorial.h"
 //test
// main() the starting point for the program
// CP_Engine_SetNextGameState() tells CProcessing which functions to use for init, update and exit
// CP_Engine_Run() is the core function that starts the simulation
int main(void)
{
	CP_Engine_SetNextGameState(Logo_Init, Logo_Update, Logo_Exit);
	
	CP_System_SetWindowSize(1920, 1080);
	
	CP_Engine_Run(1);
	return 0;
}
