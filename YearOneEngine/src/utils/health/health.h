#ifndef HEALTH_H_INCLUDED 
#define HEALTH_H_INCLUDED 

#define MAX_HEARTS_CAP 6 
#define HEART_FLASH_TIME 1.5f 

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
int HealthSystem_GetHearts(const HealthSystem* hs);
void HealthSystem_ResetTimer(HealthSystem* hs);
float HealthSystem_GetTimer(const HealthSystem* hs);
void HealthSystem_DrawHearts(const HealthSystem* hs);
void HealthSystem_DrawBar(const HealthSystem* hs, float x, float y, float width, float height);
void Health_DamagePlayersOnEnemyCollisions(int dmgPerHit);
void HealthAudio_Load(const char* hitSfxPath, const char* loseSfxPath);
void HealthAudio_Free(void);
#endif 