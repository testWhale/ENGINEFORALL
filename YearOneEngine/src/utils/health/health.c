//---------------------------------------------------------
// file: health.c
// author: Xavier Lim
// email: yipfengxavier.lim@digipen.edu
//
// brief: Implements the HealthSystem.
//   - Manages player health using hearts and health bar
//   - Handles flashing hearts when damaged
//   - Plays audio feedback for hits and health loss
//   - Detects collisions between players and enemies
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "health.h"
#include "cprocessing.h"
#include <math.h>
#include "entity/ent.h"
#include "utils/arr.h"
#include "tile/tile.h"


//----------assets------------
static CP_Sound s_hitSfx = 0;
static CP_Sound s_loseSfx = 0;
static CP_Image s_fullHeart = 0;
static CP_Image s_emptyHeart = 0;
extern float unit;

/* HealthSystem_Init()
Input:
    hs        - pointer to HealthSystem
    maxHearts - maximum number of hearts
    maxhealth - maximum health value
Output:
    None
Description:
    - Initializes the health system with given hearts and health
    - Clamps values to valid ranges
    - Resets timers and flashing states
*/

void HealthSystem_Init(HealthSystem* hs, int maxHearts, int maxhealth)
{
    if (!hs) return;

    // Clamp heart count between 1 and MAX_HEARTS_CAP
    if (maxHearts < 1)              maxHearts = 1;
    if (maxHearts > MAX_HEARTS_CAP) maxHearts = MAX_HEARTS_CAP;

    hs->maxHearts = maxHearts;
    hs->currentHearts = maxHearts;
    hs->timer = 0.0f;

    // Clamp health to at least 1
    if (maxhealth < 1) maxhealth = 1;
    hs->maxhealth = (float)maxhealth;
    hs->health = (float)maxhealth;

    // Reset flashing state
    for (int i = 0; i < MAX_HEARTS_CAP; ++i) {
        hs->alpha[i] = 0.0f;
        hs->flashTimer[i] = 0.0f;
    }
}

/* HealthImage_Load()
Input:
    fullPath  - path to full heart image
    emptyPath - path to empty heart image
Output:
    None
Description:
    - Loads heart images 
    - If paths are invalid, defaults to 0
*/

void HealthImage_Load(const char* fullPath, const char* emptyPath)
{
    s_fullHeart = (fullPath && *fullPath) ? CP_Image_Load(fullPath) : 0;
    s_emptyHeart = (emptyPath && *emptyPath) ? CP_Image_Load(emptyPath) : 0;
}

/* HealthSystem_Update()
Input:
    hs        - pointer to HealthSystem
    deltaTime - time step (seconds)
Output:
    None
Description:
    - Advances internal timer
    - Updates flashing effect for damaged hearts
    - Clamps hearts and health values to valid ranges
*/

void HealthSystem_Update(HealthSystem* hs, float deltaTime)
{
    if (!hs) return;

    hs->timer += deltaTime;

    // Update flashing effect for each heart
    for (int i = 0; i < hs->maxHearts; ++i) {
        float t = hs->flashTimer[i];
        if (t > 0.0f) {
            t -= deltaTime;
            if (t <= 0.0f) {
                t = 0.0f;
                hs->alpha[i] = 0.0f;
            }
            else {
                // Normalize flash time into [0,1]
                float u = t / HEART_FLASH_TIME;
                if (u < 0.0f) u = 0.0f;
                if (u > 1.0f) u = 1.0f;
                hs->alpha[i] = u * u; 
            }
            hs->flashTimer[i] = t;
        }
    }

    // Clamp values to valid ranges
    if (hs->currentHearts < 0)              hs->currentHearts = 0;
    if (hs->currentHearts > hs->maxHearts)  hs->currentHearts = hs->maxHearts;
    if (hs->health < 0.0f)                  hs->health = 0.0f;
    if (hs->health > hs->maxhealth)         hs->health = hs->maxhealth;
}

/* HealthSystem_ResetTimer()
Input:
    hs - pointer to HealthSystem
Output:
    None
Description:
    - Resets the health system’s timer to zero
*/

void HealthSystem_ResetTimer(HealthSystem* hs)
{
    if (!hs) return;
    hs->timer = 0.0f;
}

/* HealthSystem_GetTimer()
Input:
    hs - pointer to HealthSystem
Output:
    float - current timer value
Description:
    - Returns the current timer value
    - Returns 0.0f if system is invalid
*/

float HealthSystem_GetTimer(const HealthSystem* hs)
{
    if (!hs) return 0.0f;
    return hs->timer;
}

/* HealthSystem_TakeDamage()
Input:
    hs - pointer to HealthSystem
Output:
    None
Description:
    - Reduces heart count by one
    - Plays lose sound effect 
    - Triggers flashing effect on lost heart
*/

void HealthSystem_TakeDamage(HealthSystem* hs)
{
    if (!hs) return;
    if (hs->currentHearts <= 0) return;

    int lostIndex = hs->currentHearts - 1;
    hs->currentHearts -= 1;

    if (s_loseSfx) CP_Sound_Play(s_loseSfx);

    if (lostIndex >= 0 && lostIndex < hs->maxHearts) {
        hs->flashTimer[lostIndex] = HEART_FLASH_TIME;
        hs->alpha[lostIndex] = 1.0f;
    }
}

/* Health_PlayHitSfx()
Input:
    None
Output:
    None
Description:
    - Plays hit sound effect when player unit is damaged
*/

void Health_PlayHitSfx(void)
{
    if (s_hitSfx) CP_Sound_Play(s_hitSfx);
}

/* HealthSystem_GetHearts()
Input:
    hs - pointer to HealthSystem
Output:
    int - current number of hearts
Description:
    - Returns current heart count
    - Returns 0 if system is invalid
*/

int HealthSystem_GetHearts(const HealthSystem* hs)
{
    if (!hs) return 0;
    return hs->currentHearts;
}

/* HealthSystem_DrawHearts()
Input:
    hs - pointer to HealthSystem
Output:
    None
Description:
    - Draws heart icons representing current health
    - Uses images if loaded, otherwise draws fallback circles
    - Applies flashing overlay for damaged hearts
*/

void HealthSystem_DrawHearts(const HealthSystem* hs)
{
    if (!hs) return;

    const float startX = 74.0f * unit;
    const float y = 12.5f * unit;
    const float gap = 14.0f * unit;
    const float size = 14.0f * unit;

    for (int i = 0; i < hs->maxHearts; ++i) {
        float x = startX + i * gap;

        // Draw empty heart 
        CP_Image_Draw(s_emptyHeart, x, y, size, size, 255);

        // Overlay full heart if still alive
        if (i < hs->currentHearts)
            CP_Image_Draw(s_fullHeart, x, y, size, size, 255);

        // Flash overlay 
        int a = (int)(hs->alpha[i] * 255.0f);
        if (a > 0) {
            if (a > 255) a = 255;
            CP_Image_Draw((i < hs->currentHearts) ? s_fullHeart : s_emptyHeart,
                x, y, size, size, a);
        }
    }
}

/* HealthSystem_DrawBar()
Input:
    hs     - pointer to HealthSystem
    x,y    - position of bar
    width  - width of bar
    height - height of bar
Output:
    None
Description:
    - Draws a rectangular health bar
    - Background is gray, filled portion is green
    - Filled width scales with health percentage
*/


void HealthSystem_DrawBar(const HealthSystem* hs,
    float x, float y, float width, float height)
{
    if (!hs || hs->maxhealth <= 0.0f) return;

    // Clamp percentage between 0 and 1
    float pct = hs->health / hs->maxhealth;
    if (pct < 0.0f) pct = 0.0f;
    if (pct > 1.0f) pct = 1.0f;

    CP_Settings_RectMode(CP_POSITION_CORNER);

    // Background bar (gray)
    CP_Settings_Fill(CP_Color_Create(60, 60, 60, 255));
    CP_Graphics_DrawRect(x, y, width, height);

    // Filled portion (green) proportional to health percentage
    float filledW = width * pct;
    CP_Settings_Fill(CP_Color_Create(57, 255, 20, 255));
    CP_Graphics_DrawRect(x, y, filledW, height);
}

/* HealthAudio_Load()
Input:
    hitSfxPath  - path to hit sound effect
    loseSfxPath - path to lose sound effect
Output:
    None
Description:
    - Loads audio assets for hit and lose events
    - Defaults to 0 if paths are invalid
*/

void HealthAudio_Load(const char* hitSfxPath, const char* loseSfxPath)
{
    s_hitSfx = (hitSfxPath && *hitSfxPath) ? CP_Sound_Load(hitSfxPath) : 0;
    s_loseSfx = (loseSfxPath && *loseSfxPath) ? CP_Sound_Load(loseSfxPath) : 0;
}

/* circles_overlap()
Input:
    x1, y1 - center of first circle
    r1     - radius of first circle
    x2, y2 - center of second circle
    r2     - radius of second circle
Output:
    1 or 0
Description:
    - Returns 1 if the two circles overlap or touch
    - Returns 0 otherwise
    - Used for collision detection between players and enemies
*/

static int circles_overlap(float x1, float y1, float r1,
    float x2, float y2, float r2)
{
    float dx = x1 - x2;
    float dy = y1 - y2;
    float rr = r1 + r2;
    return (dx * dx + dy * dy) <= (rr * rr);
}

/* Health_DamagePlayersOnEnemyCollisions()
Input:
    dmgPerTick     - damage applied per tick
    maxContactTime - maximum allowed contact time
    dt             - delta time (seconds)
Output:
    None
Description:
    - Checks collisions between enemies and players
    - Applies damage over time while in contact
    - Plays hit sound effect when damage occurs
    - clear tile if health reach 0
*/

void Health_DamagePlayersOnEnemyCollisions(int dmgPerTick,
    float maxContactTime,
    float dt)
{
    if (maxContactTime <= 0.0f) maxContactTime = 3.0f;

    const float tickInterval = 0.5f; // damage applied every 0.5s while touching

    // Tile map dimensions used to check row/column overlap
    const float tileStartX = g_TileMap[0][0].startPos.x;
    const float tileStartY = g_TileMap[0][0].startPos.y;
    const float tileW = g_TileMap[0][0].dim.x;
    const float tileH = g_TileMap[0][0].dim.y;

    for (size_t ei = 0; ei < enemyArr.used; ++ei) {
        ActiveEntity* enemy = &enemyArr.ActiveEntityArr[ei];
        if (!enemy->alive || enemy->unit.isPlayer) continue;

        int touching = 0;

        float ex = enemy->unit.centerPos.x;
        float ey = enemy->unit.centerPos.y;
        float er = 0.5f * enemy->unit.diameter;

        // Check against all players
        for (size_t pi = 0; pi < playerArr.used; ++pi) {
            ActiveEntity* pl = &playerArr.ActiveEntityArr[pi];
            if (!pl->alive || !pl->unit.isPlayer) continue;

            float px = pl->unit.centerPos.x;
            float py = pl->unit.centerPos.y;
            float pr = 0.5f * pl->unit.diameter;

            // Row/column check ensures they are in same tile cell
            int eRow = (int)((ey - tileStartY) / tileH);
            int pRow = (int)((py - tileStartY) / tileH);
            int eCol = (int)((ex - tileStartX) / tileW);
            int pCol = (int)((px - tileStartX) / tileW);
            if (eRow != pRow || eCol != pCol) continue;

            // Circle overlap check for actual collision
            if (!circles_overlap(ex, ey, er, px, py, pr)) continue;

            touching = 1;

            float prevTime = enemy->contactTime;
            enemy->isHitting = 1;
            enemy->contactTime += dt;

            // Stop hitting if contact exceeds maxContactTime
            if (enemy->contactTime > maxContactTime) {
                enemy->isHitting = 0;
                enemy->contactTime = 0.0f;
                break;
            }

            // Damage applied every tickInterval (0.5s)
            int prevTick = (int)(prevTime / tickInterval);
            int currTick = (int)(enemy->contactTime / tickInterval);

            if (currTick > prevTick && pl->alive) {
                pl->health -= dmgPerTick;
                Health_PlayHitSfx();

                // If player dies, mark dead and clear tile
                if (pl->health <= 0) {
                    pl->health = 0;
                    pl->alive = 0;

                    for (int r = 0; r < TILE_ROWS; ++r) {
                        for (int c = 0; c < TILE_COLUMNS; ++c) {
                            Tile* t = &g_TileMap[r][c];
                            if (!t->hasEntity) continue;
                            if (t->centerPos.x == pl->unit.centerPos.x &&
                                t->centerPos.y == pl->unit.centerPos.y) {
                                t->hasEntity = 0;
                                t->entity = NULL;
                                t->tsel = 0;
                                t->currHovered = 0;
                                t->nextTileCheck = 0;
                                r = TILE_ROWS; // break outer loop
                                break;
                            }
                        }
                    }
                }
            }
            break; // stop checking other players once collision found
        }

        // Reset contact state if not touching any player
        if (!touching) {
            enemy->isHitting = 0;
            enemy->contactTime = 0.0f;
        }
    }
}
