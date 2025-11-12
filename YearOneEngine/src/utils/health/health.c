
#include "health.h"
#include "cprocessing.h"

void HealthSystem_Init(HealthSystem* hs, int maxHearts, int maxhealth)
{
    if (!hs) return;

  
    if (maxHearts < 1) maxHearts = 1;
    if (maxHearts > MAX_HEARTS_CAP) maxHearts = MAX_HEARTS_CAP;

    hs->maxHearts = maxHearts;
    hs->currentHearts = maxHearts;

    
    hs->timer = 0.0f;


    if (maxhealth < 1) maxhealth = 1;
    hs->maxhealth = (float)maxhealth;
    hs->health = (float)maxhealth;

 
    for (int i = 0; i < MAX_HEARTS_CAP; ++i) {
        hs->alpha[i] = 0.0f;
        hs->flashTimer[i] = 0.0f;
    }
}

void HealthSystem_Update(HealthSystem* hs, float deltaTime)
{
    if (!hs) return;

    hs->timer += deltaTime;

    for (int i = 0; i < hs->maxHearts; ++i) {
        float t = hs->flashTimer[i];
        if (t > 0.0f) {
            t -= deltaTime;
            if (t <= 0.0f) {
                t = 0.0f;
                hs->alpha[i] = 0.0f;
            }
            else {
                float u = t / HEART_FLASH_TIME; 
                if (u < 0.0f) u = 0.0f;
                if (u > 1.0f) u = 1.0f;
                hs->alpha[i] = u * u;           
            }
            hs->flashTimer[i] = t;
        }
    }

    if (hs->currentHearts < 0) hs->currentHearts = 0;
    if (hs->currentHearts > hs->maxHearts) hs->currentHearts = hs->maxHearts;

    if (hs->health < 0.0f) hs->health = 0.0f;
    if (hs->health > hs->maxhealth) hs->health = hs->maxhealth;
}

void HealthSystem_ResetTimer(HealthSystem* hs)
{
    if (!hs) return;
    hs->timer = 0.0f;
}

float HealthSystem_GetTimer(const HealthSystem* hs)
{
    if (!hs) return 0.0f;
    return hs->timer;
}

void HealthSystem_TakeDamage(HealthSystem* hs)
{
    if (!hs) return;
    if (hs->currentHearts <= 0) return;

    int lostIndex = hs->currentHearts - 1;

    hs->currentHearts -= 1;

    if (lostIndex >= 0 && lostIndex < hs->maxHearts) {
        hs->flashTimer[lostIndex] = HEART_FLASH_TIME;
        hs->alpha[lostIndex] = 1.0f;
    }
}

int HealthSystem_GetHearts(const HealthSystem* hs)
{
    if (!hs) return 0;
    return hs->currentHearts;
}

void HealthSystem_DrawHearts(const HealthSystem* hs)
{
    if (!hs) return;

    const float startX = 50.0f;
    const float y = 50.0f;
    const float gap = 60.0f;
    const float r = 20.0f;

    for (int i = 0; i < hs->maxHearts; ++i) {
        float x = startX + i * gap;

        CP_Settings_Fill(CP_Color_Create(60, 60, 60, 255));
        CP_Graphics_DrawCircle(x, y, r);

        if (i < hs->currentHearts) {
            CP_Settings_Fill(CP_Color_Create(220, 40, 40, 255));
            CP_Graphics_DrawCircle(x, y, r - 3.0f);
        }

        if (hs->alpha[i] > 0.0f) {
            float a = hs->alpha[i] * 255.0f;
            if (a < 0.0f) a = 0.0f;
            if (a > 255.0f) a = 255.0f;
            CP_Settings_Fill(CP_Color_Create(255, 255, 255, (int)a));
            CP_Graphics_DrawCircle(x, y, r);
        }
    }
}

void HealthSystem_DrawBar(const HealthSystem* hs, float x, float y, float width, float height)
{
    if (!hs) return;
    CP_Settings_RectMode(CP_POSITION_CORNER);

    float pct = (hs->maxhealth > 0.0f) ? (hs->health / hs->maxhealth) : 0.0f;
    if (pct < 0.0f) pct = 0.0f;
    if (pct > 1.0f) pct = 1.0f;

    float filled = width * pct;
    CP_Settings_NoStroke();
    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255));
    CP_Graphics_DrawRect(x, y, width, height);
    CP_Settings_Fill(CP_Color_Create(0, 200, 0, 255));
    CP_Graphics_DrawRect(x + (width - filled), y, filled, height);
    CP_Settings_NoFill();
    CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255));
    CP_Graphics_DrawRect(x, y, width, height);
    CP_Settings_NoStroke();
}


