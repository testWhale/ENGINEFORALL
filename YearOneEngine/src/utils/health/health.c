
#include "cprocessing.h"
#include "utils/arr.h"
#include "health.h"

#define MAX_HEARTS_CAP    6           // Maximum number of hearts allowed, only using 3 right now but having 6 for future proofing 
#define HEART_FLASH_TIME  1.5f        // Time for heart flash animation after damage

static float g_elapsed = 0.0f;        // Tracks elapsed time for gameplay timer

// Timer functions for tracking game duration
void HealthTimer_Reset(void) { g_elapsed = 0.0f; }
void HealthTimer_Update(float dt) { g_elapsed += dt; }
float HealthTimer_Get(void) { return g_elapsed; }

// Heart system state
static int   s_maxHearts = 3;         // Maximum hearts for player
static int   s_curHearts = 3;         // Current hearts remaining
static float s_hx[MAX_HEARTS_CAP], s_hy[MAX_HEARTS_CAP]; // Heart positions
static float s_alpha[MAX_HEARTS_CAP], s_timer[MAX_HEARTS_CAP]; // Flash alpha and timer

// Audio for hit and lose events
static CP_Sound s_sndHit = 0;
static CP_Sound s_sndLose = 0;

// Game over state callbacks
static GO_SetDataFn s_goSetData = 0;
static StateFn      s_goInit = 0, s_goUpd = 0, s_goExit = 0;

static float s_lossLockUntilSec = 0.0f; // Prevents multiple damage hits in quick succession

// Draws a single heart with alpha transparency
static void drawHeart(float x, float y, float a) {
    CP_Color c = CP_Color_Create(255, 0, 0, (int)(a * 255));
    CP_Settings_Stroke(c);
    CP_Settings_Fill(c);
    CP_Graphics_DrawCircle(x - 7, y, 10);
    CP_Graphics_DrawCircle(x + 7, y, 10);
    float x1 = x - 14, y1 = y;
    float x2 = x + 14, y2 = y;
    float x3 = x, y3 = y + 20;
    CP_Graphics_DrawTriangleAdvanced(x1, y1, x2, y2, x3, y3, 0.0f);
}

// Initializes hearts and positions
void Hearts_Init(int max_hearts) {
    if (max_hearts < 1)              max_hearts = 1;
    if (max_hearts > MAX_HEARTS_CAP) max_hearts = MAX_HEARTS_CAP;
    s_maxHearts = max_hearts;
    s_curHearts = s_maxHearts;
    for (int i = 0; i < s_maxHearts; ++i) {
        s_hx[i] = 50.0f + i * 60.0f; // Horizontal spacing
        s_hy[i] = 50.0f;
        s_alpha[i] = 0.0f;
        s_timer[i] = 0.0f;
    }
    s_lossLockUntilSec = 0.0f;
}

// Handles player taking damage and triggers game over if hearts reach zero
void Hearts_TakeDamage(void) {
    if (s_curHearts <= 0) return;

    s_curHearts--; // Reduce heart count

    // Flash all hearts for visual feedback
    for (int i = 0; i < s_maxHearts; ++i) {
        s_alpha[i] = 1.0f;
        s_timer[i] = HEART_FLASH_TIME;
    }

    if (s_sndHit) CP_Sound_Play(s_sndHit);

    // If no hearts left, trigger game over state
    if (s_curHearts <= 0) {
        if (s_sndLose) CP_Sound_Play(s_sndLose);
        if (s_goSetData) s_goSetData(HealthTimer_Get(), 0);
        if (s_goInit && s_goUpd && s_goExit)
            CP_Engine_SetNextGameState(s_goInit, s_goUpd, s_goExit);
    }
}

// Updates heart flash timers
void Hearts_Update(float dt) {
    for (int i = 0; i < s_maxHearts; ++i) {
        if (s_alpha[i] > 0.0f) {
            s_timer[i] -= dt;
            if (s_timer[i] <= 0.0f) {
                s_timer[i] = 0.0f;
                s_alpha[i] = 0.0f;
            }
        }
    }
}

// Draws hearts based on current health
void Hearts_Draw(void) {
    for (int i = 0; i < s_maxHearts; ++i) {
        if (s_alpha[i] > 0.0f) {
            float a = (i < s_curHearts) ? 1.0f : 0.3f; // Dim hearts if lost
            drawHeart(s_hx[i], s_hy[i], a);
        }
    }
}

int Hearts_Get(void) { return s_curHearts; }

// Loads and frees audio for health events
void HealthAudio_Load(const char* hitSfxPath, const char* loseSfxPath) {
    if (hitSfxPath && *hitSfxPath)  s_sndHit = CP_Sound_Load(hitSfxPath);
    if (loseSfxPath && *loseSfxPath) s_sndLose = CP_Sound_Load(loseSfxPath);
}
void HealthAudio_Free(void) {
    if (s_sndHit) { CP_Sound_Free(s_sndHit);  s_sndHit = 0; }
    if (s_sndLose) { CP_Sound_Free(s_sndLose); s_sndLose = 0; }
}

// Binds game over state functions
void Health_BindGameOver(GO_SetDataFn setData, StateFn init, StateFn update, StateFn exit) {
    s_goSetData = setData;
    s_goInit = init;
    s_goUpd = update;
    s_goExit = exit;
}

// Draws health bar for an enemy entity
void Health_DrawEnemyBar(const ActiveEntity* e, float barW, float barH, float yOffset) {
    if (!e || !e->alive || e->maxHealth <= 0) return;

    int hp = e->health;
    if (hp < 0) hp = 0;
    if (hp > e->maxHealth) hp = e->maxHealth;

    float pct = (float)hp / (float)e->maxHealth;
    float r = e->unit.diameter * 0.5f;
    float x = e->unit.centerPos.x - barW * 0.5f;
    float y = e->unit.centerPos.y - r - yOffset;

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255)); // Background bar
    CP_Graphics_DrawRect(x, y, barW, barH);

    CP_Settings_Fill(CP_Color_Create(0, 200, 0, 255)); // Health bar
    CP_Graphics_DrawRect(x, y, barW * pct, barH);
}

// Draws health bars for all enemies
void Health_DrawAllEnemyBars(const TestArr* A, float barW, float barH, float yOffset) {
    if (!A || !A->ActiveEntityArr) return;
    for (size_t i = 0; i < A->used; ++i)
        Health_DrawEnemyBar(&A->ActiveEntityArr[i], barW, barH, yOffset);
}

// Processes goal circle collision: if enemy reaches goal, player loses a heart
void Health_ProcessGoalCircle(TestArr* enemies, CP_Vector goalCenter, float goalRadius)
{
    if (!enemies || enemies->used == 0) return;

    const float now = HealthTimer_Get();
    if (now < s_lossLockUntilSec) return; // Prevent rapid multiple hits

    const float R = goalRadius;

    for (size_t i = 0; i < enemies->used; ) {
        ActiveEntity* e = &enemies->ActiveEntityArr[i];

        if (!e->alive || e->unit.isPlayer) { ++i; continue; }

        const float ex = e->unit.centerPos.x;
        const float ey = e->unit.centerPos.y;
        const float er = 0.5f * e->unit.diameter;

        const float dx = ex - goalCenter.x;
        const float dy = ey - goalCenter.y;
        const float rr = er + R;

        // If enemy overlaps goal circle, take damage and remove enemy
        if (dx * dx + dy * dy <= rr * rr) {
            Hearts_TakeDamage();
            Arr_Del(enemies, e->id);
            s_lossLockUntilSec = now + 0.35f; // Lock damage for short time
            return;
        }

        ++i;
    }
}
