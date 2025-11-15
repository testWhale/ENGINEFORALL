#ifndef PAUSE_H_INCLUDED
#define PAUSE_H_INCLUDED

#include "cprocessing.h"


void Pause_Init(void);
void Pause_UpdateAndDraw(void);
int   Pause_IsPaused(void);
void  Pause_SetPaused(int on);
float Pause_Dt(float dt);
int   Pause_TakeMenuRequest(void);
void Pause_exit(void);

#endif 
