
#include "health.h"
#include "cprocessing.h"
#include <math.h>
#include "entity/ent.h"
#include "utils/arr.h"

static CP_Sound s_hitSfx = 0;
static CP_Sound s_loseSfx = 0;
static int      s_playedLose = 0;

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
    s_playedLose = 0;
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
    if (s_hitSfx)
        CP_Sound_Play(s_hitSfx);

    if (lostIndex >= 0 && lostIndex < hs->maxHearts) {
        hs->flashTimer[lostIndex] = HEART_FLASH_TIME;
        hs->alpha[lostIndex] = 1.0f;
    }
    if (hs->currentHearts <= 0 && !s_playedLose) {
        if (s_loseSfx)
            CP_Sound_Play(s_loseSfx);
        s_playedLose = 1;
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


static int circles_overlap(float x1, float y1, float r1,
    float x2, float y2, float r2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float rr = r1 + r2;
    return (dx * dx + dy * dy) <= (rr * rr);
}

void Health_DamagePlayersOnEnemyCollisions(int dmgPerHit)
{
    for (size_t i = 0; i < enemyArr.used; ++i) {
        ActiveEntity* en = &enemyArr.ActiveEntityArr[i];
        if (!en->alive || en->unit.isPlayer) continue;

        float ex = en->unit.centerPos.x;
        float ey = en->unit.centerPos.y;
        float er = 0.5f * en->unit.diameter;

        for (size_t p = 0; p < playerArr.used; ++p) {
            ActiveEntity* pl = &playerArr.ActiveEntityArr[p];
            if (!pl->alive || !pl->unit.isPlayer) continue;

            float px = pl->unit.centerPos.x;
            float py = pl->unit.centerPos.y;
            float pr = 0.5f * pl->unit.diameter;

            if (circles_overlap(ex, ey, er, px, py, pr)) {
                pl->health -= dmgPerHit;
                if (pl->health <= 0) {
                    pl->health = 0;
                    pl->alive = 0;

                }
            }
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

void HealthAudio_Load(const char* hitSfxPath, const char* loseSfxPath)
{
    if (s_hitSfx) { CP_Sound_Free(s_hitSfx);  s_hitSfx = 0; }
    if (s_loseSfx) { CP_Sound_Free(s_loseSfx); s_loseSfx = 0; }

    if (hitSfxPath && *hitSfxPath)
        s_hitSfx = CP_Sound_Load(hitSfxPath);

    if (loseSfxPath && *loseSfxPath)
        s_loseSfx = CP_Sound_Load(loseSfxPath);

    s_playedLose = 0;
}

void HealthAudio_Free(void)
{
    if (s_hitSfx) {
        CP_Sound_Free(s_hitSfx);
        s_hitSfx = 0;
    }
    if (s_loseSfx) {
        CP_Sound_Free(s_loseSfx);
        s_loseSfx = 0;
    }
    s_playedLose = 0;
}

