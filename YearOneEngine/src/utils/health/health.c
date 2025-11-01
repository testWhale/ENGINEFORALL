#include "health.h"

/* Hearts */
#define MAX_HEARTS_CAP   6
#define HEART_FLASH_TIME 1.5f
static float g_elapsed = 0.0f;

void HealthTimer_Reset(void) { g_elapsed = 0.0f; }
void HealthTimer_Update(float dt) { g_elapsed += dt; }
float HealthTimer_Seconds(void) { return g_elapsed; }

static int   s_maxHearts = 3;
static int   s_curHearts = 3;
static float s_hx[MAX_HEARTS_CAP], s_hy[MAX_HEARTS_CAP];
static float s_alpha[MAX_HEARTS_CAP], s_timer[MAX_HEARTS_CAP];

static CP_Sound s_sndHit = 0;
static CP_Sound s_sndLose = 0;

static GO_SetDataFn s_goSetData = 0;
static StateFn      s_goInit = 0, s_goUpd = 0, s_goExit = 0;
static float        s_gameTime = 0.0f;

static void drawHeart(float x, float y, float a) {
    CP_Color c = CP_Color_Create(255, 0, 0, (int)(a * 255));
    CP_Settings_Stroke(c);
    CP_Settings_Fill(c);
    CP_Graphics_DrawCircle(x - 7, y, 10);
    CP_Graphics_DrawCircle(x + 7, y, 10);
    float x1 = x - 14, y1 = y, x2 = x + 14, y2 = y, x3 = x, y3 = y + 20;
    CP_Graphics_DrawTriangleAdvanced(x1, y1, x2, y2, x3, y3, 0.0f);
}

void Hearts_Init(int max_hearts) {
    if (max_hearts < 1) max_hearts = 1;
    if (max_hearts > MAX_HEARTS_CAP) max_hearts = MAX_HEARTS_CAP;
    s_maxHearts = max_hearts;
    s_curHearts = s_maxHearts;
    for (int i = 0; i < s_maxHearts; ++i) {
        s_hx[i] = 50.0f + i * 60.0f;
        s_hy[i] = 50.0f;
        s_alpha[i] = 0.0f;
        s_timer[i] = 0.0f;
    }
}

void Hearts_TakeDamage(void) {
    if (s_curHearts <= 0) return;
    s_curHearts--;
    for (int i = 0; i < s_maxHearts; ++i) { s_alpha[i] = 1.0f; s_timer[i] = HEART_FLASH_TIME; }
    CP_Sound_Play(s_sndHit);
    if (s_curHearts <= 0) {
        CP_Sound_Play(s_sndLose);
        if (s_goSetData) s_goSetData(s_gameTime, 0);
        if (s_goInit && s_goUpd && s_goExit)
            CP_Engine_SetNextGameState(s_goInit, s_goUpd, s_goExit);
    }
}

void Hearts_Update(float dt) {
    for (int i = 0; i < s_maxHearts; ++i) {
        if (s_alpha[i] > 0.0f) {
            s_timer[i] -= dt;
            if (s_timer[i] <= 0.0f) { s_timer[i] = 0.0f; s_alpha[i] = 0.0f; }
        }
    }
}

void Hearts_Draw(void) {
    for (int i = 0; i < s_maxHearts; ++i) {
        if (s_alpha[i] > 0.0f) {
            float a = (i < s_curHearts) ? 1.0f : 0.3f;
            drawHeart(s_hx[i], s_hy[i], a);
        }
    }
}

int Hearts_Get(void) { return s_curHearts; }

void HealthAudio_Load(const char* hitSfxPath, const char* loseSfxPath) {
    if (hitSfxPath)  s_sndHit = CP_Sound_Load(hitSfxPath);
    if (loseSfxPath) s_sndLose = CP_Sound_Load(loseSfxPath);
}
void HealthAudio_Free(void) {
    CP_Sound_Free(s_sndHit);
    CP_Sound_Free(s_sndLose);
}

void Health_BindGameOver(GO_SetDataFn setData, StateFn init, StateFn update, StateFn exit) {
    s_goSetData = setData;
    s_goInit = init; s_goUpd = update; s_goExit = exit;
}




void Health_DrawEnemyBar(const ActiveEntity* e, float barW, float barH, float yOffset) {
    if (!e || !e->alive || e->maxHealth <= 0) return;
    int hp = e->health; if (hp < 0) hp = 0; if (hp > e->maxHealth) hp = e->maxHealth;
    float pct = (float)hp / (float)e->maxHealth;
    float r = e->unit.diameter * 0.5f;
    float x = e->unit.centerPos.x - barW * 0.5f;
    float y = e->unit.centerPos.y - r - yOffset;

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(80, 80, 80, 255));
    CP_Graphics_DrawRect(x, y, barW, barH);
    CP_Settings_Fill(CP_Color_Create(0, 200, 0, 255));
    CP_Graphics_DrawRect(x, y, barW * pct, barH);
}

void Health_DrawAllEnemyBars(const TestArr* A, float barW, float barH, float yOffset) {
    if (!A || !A->ActiveEntityArr) return;
    for (size_t i = 0; i < A->used; ++i)
        Health_DrawEnemyBar(&A->ActiveEntityArr[i], barW, barH, yOffset);
}


float HealthTimer_Seconds(void);   

void Health_ProcessLeftGoal(TestArr* A, float goalX)
{
    if (!A || !A->ActiveEntityArr) return;

    if (HealthTimer_Seconds() < 0.50f)   // grace: first 0.5s never deduct
        return;

    for (size_t i = 0; i < A->used; ++i) {
        ActiveEntity* e = &A->ActiveEntityArr[i];

        if (!e->alive)              continue;       // not active
        if (e->unit.isPlayer)       continue;       // skip UI/player pieces
        if (e->maxHealth <= 0)      continue;       // malformed

        const float leftmost = e->unit.centerPos.x - 0.5f * e->unit.diameter;
        if (leftmost <= goalX) {
            e->alive = 0;                             // despawn
            Hearts_TakeDamage();
            Arr_Del(A, (int)i);                       // keep array compact (optional)
            break;
        }
    }
}