//---------------------------------------------------------
// file: goal.c
// author: Xavier Lim
// email: yipfengxavier.lim@digipen.edu
//
// brief: Implements the Goal system.
//   - Initializes goal positions from the tile map
//   - Detects collisions between enemies and goals
//   - Applies damage to the health system when goals are hit
//   - Provides debug drawing for visualization
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "goal.h"
#include "utils/arr.h"   

// -------------------- Variables --------------------
static CP_Vector s_goalCenters[GOAL_COUNT];
static float     s_goalRadius[GOAL_COUNT];

/* CirclesOverlap()
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
    - Used for collision detection between enemies and goals
*/

static int CirclesOverlap(float x1, float y1, float r1,
    float x2, float y2, float r2)
{
    float dx = x1 - x2, dy = y1 - y2; // difference in x and y
    float rr = r1 + r2;               // sum of radii
    return (dx * dx + dy * dy) <= (rr * rr);  // overlap if distance^2 <= (r1+r2)^2
}

/* Goal_InitFromTileMap()
Input:
    radiusScale - scale factor for goal radius
    marginScale - scale factor for margin spacing
Output:
    None
Description:
    - Initializes goal positions based on the tile map layout
    - Places goals to the left of the first column of tiles
    - Applies scaling factors to radius and margin
*/
void Goal_InitFromTileMap(float radiusScale, float marginScale)
{
    if (radiusScale <= 0.0f) radiusScale = 0.45f;
    if (marginScale <= 0.0f) marginScale = 0.25f;

    const float cellW = g_TileMap[0][0].dim.x;
    const float cellH = g_TileMap[0][0].dim.y;
    const float cell = (cellW < cellH) ? cellW : cellH;  // pick smaller dimension

    const float radius = radiusScale * cell;
    const float margin = marginScale * cell;
    
    // Find left edge of tile map
    const float leftEdgeX = g_TileMap[0][0].centerPos.x - 0.5f * g_TileMap[0][0].dim.x;

    // Place goals offset to the left by radius + margin
    const float goalX = leftEdgeX - (radius + margin);

    // Assign each goal’s position and radius
    for (int r = 0; r < GOAL_COUNT; ++r) {
        s_goalCenters[r].x = goalX;
        s_goalCenters[r].y = g_TileMap[r][0].centerPos.y;
        s_goalRadius[r] = radius;
    }
}

/* ProcessGoalHits()
Input:
    hs - pointer to HealthSystem
Output:
    None
Description:
    - Iterates through all active enemies
    - Checks if any enemy overlaps with a goal circle
    - If touched:
        Take one heart away from health system
        Removes the enemy from the active array
*/

void ProcessGoalHits(HealthSystem* hs)
{
    if (!hs) return;

    for (size_t i = 0; i < enemyArr.used; ) {
        ActiveEntity* e = &enemyArr.ActiveEntityArr[i];
        // Skip dead entities or player units
        if (!e->alive || e->unit.isPlayer) { ++i; continue; }

        // Enemy circle data
        const float ex = e->unit.centerPos.x;
        const float ey = e->unit.centerPos.y;
        const float er = 0.5f * e->unit.diameter;

        int touched = 0;
        // Check against all goals
        for (int g = 0; g < GOAL_COUNT; ++g) {
            if (CirclesOverlap(ex, ey, er, s_goalCenters[g].x, s_goalCenters[g].y, s_goalRadius[g])) {
                touched = 1;
                break;
            }
        }

        if (touched) {
            HealthSystem_TakeDamage(hs);
            Arr_Del(&enemyArr, e->id); // remove enemy that hit the goal
            continue;  // don’t increment i
        }

        ++i;  // increment when no deletion
    }
}
