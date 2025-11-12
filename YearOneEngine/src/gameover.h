#ifndef GAME_OVER_H
#define GAME_OVER_H

#include "cprocessing.h"

typedef struct {
    int   isActive;
    float finalTime;
    int   goals;
    float fade;     
    float timer;    
    CP_Font  font;  
    CP_Sound sound; 
} GameOverSystem;

extern GameOverSystem gGameOver;

void GameOver_Init(GameOverSystem* go);
void GameOver_SetData(GameOverSystem* go, float finalTime, int goals);
void GameOver_Activate(GameOverSystem* go);
void GameOver_Update(GameOverSystem* go);       
void GameOver_Draw(const GameOverSystem* go);
void GameOver_Exit(GameOverSystem* go);
void GameOver_State_Init(void);
void GameOver_State_Update(void);
void GameOver_State_Exit(void);
#endif
