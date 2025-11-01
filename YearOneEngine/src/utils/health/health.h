#ifndef HEALTH_H_INCLUDED
#define HEALTH_H_INCLUDED

#include "cprocessing.h"
#include "utils/arr.h"

void Hearts_Init(int max_hearts);
void Hearts_Update(float dt);
void Hearts_Draw(void);
void Hearts_TakeDamage(void);
int  Hearts_Get(void);

void HealthAudio_Load(const char* hitSfxPath, const char* loseSfxPath);
void HealthAudio_Free(void);

typedef void (*GO_SetDataFn)(float timeSec, int goals);
typedef void (*StateFn)(void);
void Health_BindGameOver(GO_SetDataFn setData, StateFn init, StateFn update, StateFn exit);

void  HealthTimer_Reset(void);
void  HealthTimer_Update(float dt);
float HealthTimer_Get(void);

void Health_DrawEnemyBar(const ActiveEntity* e, float barW, float barH, float yOffset);
void Health_DrawAllEnemyBars(const TestArr* A, float barW, float barH, float yOffset);
void Health_ProcessLeftGoal(TestArr* A, float goalColumnX);

#endif /* HEALTH_H_INCLUDED */
