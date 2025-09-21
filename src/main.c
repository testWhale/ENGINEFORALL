#include "cprocessing.h"
#include "./state/logo.h"
#include <stdio.h>

int main(void)
{
	CP_System_SetWindowSize(1600, 900);
	CP_Engine_SetNextGameState(logo_init, logo_update, logo_exit);
	CP_Engine_Run(1);
	return 0;
}
