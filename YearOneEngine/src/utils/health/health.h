#ifndef HEALTH_H_INCLUDED
#define HEALTH_H_INCLUDED

#include "cprocessing.h"
#include "utils/arr.h"

/* Game Over binding */
typedef void (*GO_SetDataFn)(float timeSec, int goals);
typedef void (*StateFn)(void);
void Health_BindGameOver(GO_SetDataFn setData, StateFn init, StateFn update, StateFn exit);

/* Hearts HUD */
void Hearts_Init(int max_hearts);
void Hearts_Update(float dt);
void Hearts_Draw(void);
void Hearts_TakeDamage(void);
int  Hearts_Get(void);

/* Audio */
void HealthAudio_Load(const char* hitSfxPath, const char* loseSfxPath);
void HealthAudio_Free(void);

/* Timer */
void  HealthTimer_Reset(void);
void  HealthTimer_Update(float dt);
float HealthTimer_Get(void);
#define HealthTimer_Seconds HealthTimer_Get  /* keep old callers working */

/* Enemy HP bars */
void Health_DrawEnemyBar(const ActiveEntity* e, float barW, float barH, float yOffset);
void Health_DrawAllEnemyBars(const TestArr* A, float barW, float barH, float yOffset);

/* Goal circle based heart-loss check */
void Health_ProcessGoalCircle(TestArr* enemies, CP_Vector goalCenter, float goalRadius);

#endif /* HEALTH_H_INCLUDED */
