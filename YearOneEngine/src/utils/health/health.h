//---------------------------------------------------------
// file: health.h
// author: Xavier Lim
// email: yipfengxavier.lim@digipen.edu
//
// brief: Funcion declaration for the HealthSystem interface.
//  
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#ifndef HEALTH_H_INCLUDED 
#define HEALTH_H_INCLUDED 

#define MAX_HEARTS_CAP 6  // for future proofing max amount of heart is 6 but only using 3
#define HEART_FLASH_TIME 1.5f // heart flash for 1.5s when damage

/* health struct
Description:
    - Stores player health state
    - Tracks hearts, timers, alpha transparency for flashing
Members:
    maxHearts     - maximum number of hearts allowed
    currentHearts - current number of hearts remaining
    timer         - general timer for health events
    health        - current health value
    maxhealth     - maximum health value
    alpha[]       - transparency values for each heart
    flashTimer[]  - timers for flashing effect per heart
*/

typedef struct {
	int maxHearts;
	int currentHearts;
	float timer;
	float health;
	float maxhealth;
	float alpha[MAX_HEARTS_CAP];
	float flashTimer[MAX_HEARTS_CAP];
} HealthSystem;

void HealthSystem_Init(HealthSystem* hs, int maxHearts, int maxhealth);
void HealthSystem_Update(HealthSystem* hs, float deltaTime);
void HealthSystem_TakeDamage(HealthSystem* hs);
void Health_PlayHitSfx(void);
int HealthSystem_GetHearts(const HealthSystem* hs);
void HealthSystem_ResetTimer(HealthSystem* hs);
float HealthSystem_GetTimer(const HealthSystem* hs);
void HealthSystem_DrawHearts(const HealthSystem* hs);
void HealthSystem_DrawBar(const HealthSystem* hs, float x, float y, float width, float height);
void Health_DamagePlayersOnEnemyCollisions(int dmgPerTick,float maxContactTime,float dt);
void HealthAudio_Load(const char* hitSfxPath, const char* loseSfxPath);
void HealthImage_Load(const char* fullPath, const char* emptyPath);
#endif 