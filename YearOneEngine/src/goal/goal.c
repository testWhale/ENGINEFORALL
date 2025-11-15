#include "goal.h"
#include "utils/SM.h"
#include "utils/arr.h"
#include "health.h"
#include <math.h>

static int       g_drawGoals = 1;
static float     g_goalRadius = 0.0f;
extern int IsCircleClicked(float cx, float cy, float diameter, float mx, float my);


int CirclesOverlap(float x1, float y1, float r1, float x2, float y2, float r2)
{
    float dx = x1 - x2, dy = y1 - y2;
    float rr = r1 + r2;
    return (dx * dx + dy * dy) <= (rr * rr);
}

void setGoal() {
    float cell = (g_TileMap[0][0].dim.x < g_TileMap[0][0].dim.y) ? g_TileMap[0][0].dim.x : g_TileMap[0][0].dim.y;
    g_goalRadius = 0.45f * cell;

    float goalMargin = 0.25f * cell;
    float leftEdgeX = g_TileMap[0][0].centerPos.x - 0.5f * g_TileMap[0][0].dim.x;
    goalMargin = 0.25f * cell;

    for (int r = 0; r < TILE_ROWS; ++r) {
        g_goalCenters[r].x = leftEdgeX - (g_goalRadius + goalMargin);
        g_goalCenters[r].y = g_TileMap[r][0].centerPos.y;
    }

    g_drawGoals = 1;

    for (int k = 0; k < (int)(sizeof(g_enemyHitCD) / sizeof(g_enemyHitCD[0])); ++k)
        g_enemyHitCD[k] = 0.0f;
}

void DamageEnemiesOnPlayerCollisions(int dmgPerHit, float cd, float dt)
{
    for (size_t i = 0; i < enemyArr.used; ++i) {
        int id = enemyArr.ActiveEntityArr[i].id;
        if (id >= 0 && id < (int)(sizeof(g_enemyHitCD) / sizeof(g_enemyHitCD[0])) &&
            g_enemyHitCD[id] > 0.0f)
        {
            g_enemyHitCD[id] -= dt;
        }
    }

    for (size_t i = 0; i < enemyArr.used;) {
        ActiveEntity* e = &enemyArr.ActiveEntityArr[i];
        if (!e->alive || e->unit.isPlayer) { ++i; continue; }

        int   id = e->id;
        float ex = e->unit.centerPos.x;
        float ey = e->unit.centerPos.y;
        float er = 0.5f * e->unit.diameter;

        int removed = 0;

        for (size_t p = 0; p < playerArr.used; ++p) {
            ActiveEntity* pl = &playerArr.ActiveEntityArr[p];
            if (!pl->alive || !pl->unit.isPlayer) continue;

            float px = pl->unit.centerPos.x;
            float py = pl->unit.centerPos.y;
            float pr = 0.5f * pl->unit.diameter;

            if (CirclesOverlap(ex, ey, er, px, py, pr)) {
                if (id >= 0 && id < (int)(sizeof(g_enemyHitCD) / sizeof(g_enemyHitCD[0])) &&
                    g_enemyHitCD[id] <= 0.0f)
                {
                    e->health -= dmgPerHit;
                    if (e->health <= 0) {
                        Arr_Del(&enemyArr, id);
                        removed = 1;
                    }
                    else {
                        g_enemyHitCD[id] = cd;
                    }
                }
                break;
            }
        }

        if (!removed) ++i;
    }
}


void ProcessGoalHits(void)
{
    for (size_t i = 0; i < enemyArr.used; ) {
        ActiveEntity* e = &enemyArr.ActiveEntityArr[i];
        if (!e->alive || e->unit.isPlayer) { ++i; continue; }


        int row = 0;
        float best = 1e9f;
        for (int r = 0; r < TILE_ROWS; ++r) {
            float dy = fabsf(e->unit.centerPos.y - g_goalCenters[r].y);
            if (dy < best) { best = dy; row = r; }
        }

        float ex = e->unit.centerPos.x;
        float ey = e->unit.centerPos.y;
        float er = 0.5f * e->unit.diameter;

        if (CirclesOverlap(ex, ey, er, g_goalCenters[row].x, g_goalCenters[row].y, g_goalRadius)) {
            Hearts_TakeDamage();
            Arr_Del(&enemyArr, e->id);
            continue;
        }

        ++i;
    }
}