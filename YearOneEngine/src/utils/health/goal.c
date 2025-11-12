#include "goal.h"
#include "utils/arr.h"   

static CP_Vector s_goalCenters[GOAL_COUNT];
static float     s_goalRadius[GOAL_COUNT];

static int CirclesOverlap(float x1, float y1, float r1,
    float x2, float y2, float r2)
{
    float dx = x1 - x2, dy = y1 - y2;
    float rr = r1 + r2;
    return (dx * dx + dy * dy) <= (rr * rr);
}

void Goal_InitFromTileMap(float radiusScale, float marginScale)
{
    if (radiusScale <= 0.0f) radiusScale = 0.45f;
    if (marginScale <= 0.0f) marginScale = 0.25f;

    const float cellW = g_TileMap[0][0].dim.x;
    const float cellH = g_TileMap[0][0].dim.y;
    const float cell = (cellW < cellH) ? cellW : cellH;

    const float radius = radiusScale * cell;
    const float margin = marginScale * cell;

    const float leftEdgeX = g_TileMap[0][0].centerPos.x - 0.5f * g_TileMap[0][0].dim.x;
    const float goalX = leftEdgeX - (radius + margin);

    // TILE_ROWS is guaranteed == GOAL_COUNT (5), so fill all five directly.
    for (int r = 0; r < GOAL_COUNT; ++r) {
        s_goalCenters[r].x = goalX;
        s_goalCenters[r].y = g_TileMap[r][0].centerPos.y;
        s_goalRadius[r] = radius;
    }
}

void ProcessGoalHits(HealthSystem* hs)
{
    if (!hs) return;

    for (size_t i = 0; i < enemyArr.used; ) {
        ActiveEntity* e = &enemyArr.ActiveEntityArr[i];
        if (!e->alive || e->unit.isPlayer) { ++i; continue; }

        const float ex = e->unit.centerPos.x;
        const float ey = e->unit.centerPos.y;
        const float er = 0.5f * e->unit.diameter;

        int touched = 0;
        for (int g = 0; g < GOAL_COUNT; ++g) {
            if (CirclesOverlap(ex, ey, er, s_goalCenters[g].x, s_goalCenters[g].y, s_goalRadius[g])) {
                touched = 1;
                break;
            }
        }

        if (touched) {
            HealthSystem_TakeDamage(hs); 
            Arr_Del(&enemyArr, e->id);    
            continue;                    
        }

        ++i;
    }
}

void Goal_DebugDraw(void)
{
    for (int i = 0; i < GOAL_COUNT; ++i) {
        CP_Settings_NoStroke();
        CP_Settings_Fill(CP_Color_Create(50, 150, 255, 40));
        CP_Graphics_DrawCircle(s_goalCenters[i].x, s_goalCenters[i].y, s_goalRadius[i]);

        CP_Settings_NoFill();
        CP_Settings_Stroke(CP_Color_Create(50, 150, 255, 200));
        CP_Graphics_DrawCircle(s_goalCenters[i].x, s_goalCenters[i].y, s_goalRadius[i]);
        CP_Settings_NoStroke();
    }
}
