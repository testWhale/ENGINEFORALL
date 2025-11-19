//#include "state/pickup.h"
//#include "utils/utils.h"
//#include "utils/container.h"
//#include "utils/arr.h"
//#include "utils/SM.h"
//#include "utils/readTxt.h"
//#include "utils/wave/wave.h"
//#include "tile/tile.h"
//#include "utils/health/health.h"
//#include "utils/UI/Pause.h"
//#include <stdlib.h>
//#include <time.h>
//#include <math.h>
//#include <stdio.h>
//
//
//#define minWidth  0.0f
//#define maxWidth  1400.0f
//#define extraBars 10
//
//
//CP_Sound mySound = NULL;
//
//
//float winWidth;
//float winHeight;
//
//GameEntity  players[1];
//GameEntity* Player;
//GameEntity  _player;
//StateMachine* _SM;
//
//Color Blue = { 0,   0, 255, 255 };
//Color Green = { 0, 255,   0, 255 };
//Color Red = { 255, 0,   0, 255 };
//Color White = { 0,   0,   0, 255 };
//
//typedef void (*funcArea)(CP_Vector, CP_Vector);
//
//typedef struct {
//    int       id;
//    CP_Vector centerPos;
//    float     diameter;
//    Color     color;
//    funcArea  inArea;
//} Circle;
//
//static Circle circles[2];
//static float  width = maxWidth;
//static float  startPoint = 100.0f;
//static int    maxed;
//static int    minimum;
//static int    indent = 146;
//static int    size = 80;
//static int    i_g;
//static CP_Font myFont;
//
//
//static CP_Vector g_goalCenters[TILE_ROWS];
//static float     g_goalRadius = 0.0f;
//
//static int       g_drawGoals = 1;
//
//
//static float     g_enemyHitCD[1024];
//
//
//extern int Is_Mouse_Released(float cx, float cy, float diameter, float mx, float my);
//
//
//static int CirclesOverlap(float x1, float y1, float r1, float x2, float y2, float r2)
//{
//    float dx = x1 - x2, dy = y1 - y2;
//    float rr = r1 + r2;
//    return (dx * dx + dy * dy) <= (rr * rr);
//}
//
//
//static void DamageEnemiesOnPlayerCollisions(int dmgPerHit, float cd, float dt)
//{
//    for (size_t i = 0; i < enemyArr.used; ++i) {
//        int id = enemyArr.ActiveEntityArr[i].id;
//        if (id >= 0 && id < (int)(sizeof(g_enemyHitCD) / sizeof(g_enemyHitCD[0])) &&
//            g_enemyHitCD[id] > 0.0f)
//        {
//            g_enemyHitCD[id] -= dt;
//        }
//    }
//
//    for (size_t i = 0; i < enemyArr.used;) {
//        ActiveEntity* e = &enemyArr.ActiveEntityArr[i];
//        if (!e->alive || e->unit.isPlayer) { ++i; continue; }
//
//        int   id = e->id;
//        float ex = e->unit.centerPos.x;
//        float ey = e->unit.centerPos.y;
//        float er = 0.5f * e->unit.diameter;
//
//        int removed = 0;
//
//        for (size_t p = 0; p < playerArr.used; ++p) {
//            ActiveEntity* pl = &playerArr.ActiveEntityArr[p];
//            if (!pl->alive || !pl->unit.isPlayer) continue;
//
//            float px = pl->unit.centerPos.x;
//            float py = pl->unit.centerPos.y;
//            float pr = 0.5f * pl->unit.diameter;
//
//            if (CirclesOverlap(ex, ey, er, px, py, pr)) {
//                if (id >= 0 && id < (int)(sizeof(g_enemyHitCD) / sizeof(g_enemyHitCD[0])) &&
//                    g_enemyHitCD[id] <= 0.0f)
//                {
//                    e->health -= dmgPerHit;
//                    if (e->health <= 0) {
//                        Arr_Del(&enemyArr, id);
//                        removed = 1;
//                    }
//                    else {
//                        g_enemyHitCD[id] = cd;
//                    }
//                }
//                break;
//            }
//        }
//
//        if (!removed) ++i;
//    }
//}
//
//
//static void ProcessGoalHits(void)
//{
//    for (size_t i = 0; i < enemyArr.used; ) {
//        ActiveEntity* e = &enemyArr.ActiveEntityArr[i];
//        if (!e->alive || e->unit.isPlayer) { ++i; continue; }
//
//
//        int row = 0;
//        float best = 1e9f;
//        for (int r = 0; r < TILE_ROWS; ++r) {
//            float dy = fabsf(e->unit.centerPos.y - g_goalCenters[r].y);
//            if (dy < best) { best = dy; row = r; }
//        }
//
//        float ex = e->unit.centerPos.x;
//        float ey = e->unit.centerPos.y;
//        float er = 0.5f * e->unit.diameter;
//
//        if (CirclesOverlap(ex, ey, er, g_goalCenters[row].x, g_goalCenters[row].y, g_goalRadius)) {
//            Hearts_TakeDamage();
//            Arr_Del(&enemyArr, e->id);
//            continue;
//        }
//
//        ++i;
//    }
//}
//
//
//void initPlayerDemo(void)
//{
//    GameEntity template = (GameEntity){
//        .centerPos = (CP_Vector){100, 100}, .rotation = 0, .isPlayer = 1,
//        .forwardVector = (CP_Vector){0, 0}, .color = (Color){255, 0, 0, 255},
//        .diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "Fire"
//    };
//    GameEntity enemy = (GameEntity){
//        .centerPos = (CP_Vector){100, 400}, .rotation = 0, .isPlayer = 0,
//        .forwardVector = (CP_Vector){0, 0}, .color = (Color){255, 255, 0, 255},
//        .diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "Enemy"
//    };
//
//    Arr_Init(2, &playerArr);
//    Arr_Init(32, &enemyArr);
//
//    /* players */
//    for (int i = 0; i < 4; i++) {
//        ActiveEntity ae;
//        ae.id = i;
//        ae.unit = template;
//        ae.fsm = (StateMachine){ .currState = IdleState };
//        ae.maxHealth = 100;
//        ae.health = 100;
//        ae.alive = 1;
//        ae.hasScored = 0;
//        ae.lastLeftmostX = 0.0f;
//
//        Arr_Insert(&playerArr, ae);
//        playerArr.ActiveEntityArr[i].unit.centerPos.x = template.centerPos.x + i * 100.0f;
//        //playerArr.ActiveEntityArr[i].unit.id = i;
//    }
//
//    /* enemies using your wave spawner */
//    for (int i = 0; i < 11; i++) {
//        ActiveEntity ae;
//        ae.id = i;
//        ae.unit = enemy;
//        ae.fsm = (StateMachine){ .currState = IdleState };
//        ae.maxHealth = 100;
//        ae.health = 100;
//        ae.alive = 1;
//        ae.hasScored = 0;
//        ae.lastLeftmostX = 0.0f;
//
//        Arr_Insert(&enemyArr, ae);
//        //enemyArr.ActiveEntityArr[i].unit.id = i;
//
//        Start_Wave(&enemyArr.ActiveEntityArr[i].unit, (int)2);
//
//
//        enemyArr.ActiveEntityArr[i].unit.centerPos.x += 200.0f;
//    }
//
//    ContArr_Init(playerArr.used, &containersArr);
//    Read_File("Assets/containers");
//}
//
///* -------------------------------------------------------------------------- */
///* Lifecycle                                                                   */
///* -------------------------------------------------------------------------- */
//void Test_Init(void)
//{
//    srand((unsigned)time(NULL));
//
//    //Map_Init();
//    initPlayerDemo();
//
//    winHeight = (float)CP_System_GetWindowHeight();
//    winWidth = (float)CP_System_GetWindowWidth();
//
//    circles[0] = (Circle){ 0, {winWidth / 3.0f, winHeight / 2.0f}, 300.0f, Red, NULL };
//
//    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
//    mySound = CP_Sound_Load("Assets/sound.mp3");
//
//
//    Hearts_Init(3);
//    HealthAudio_Load("Assets/Metal Ping by timgormly Id-170957.wav",
//        "Assets/Glass Break by unfa Id-221528.wav");
//
//    extern void GameOver_SetData(float, int);
//    extern void GameOver_Init(void);
//    extern void GameOver_Update(void);
//    extern void GameOver_Exit(void);
//    Health_BindGameOver(GameOver_SetData, GameOver_Init, GameOver_Update, GameOver_Exit);
//    HealthTimer_Reset();
//
//
//    float colW, rowH;
//
//    /* column width */
//    if (TILE_COLUMNS > 1)
//        colW = g_TileMap[0][1].centerPos.x - g_TileMap[0][0].centerPos.x;
//    else if (g_TileMap[0][0].dim.x > 0.0f)
//        colW = g_TileMap[0][0].dim.x;
//    else
//        colW = 96.0f;
//
//    /* row height */
//    if (TILE_ROWS > 1)
//        rowH = g_TileMap[1][0].centerPos.y - g_TileMap[0][0].centerPos.y;
//    else if (g_TileMap[0][0].dim.y > 0.0f)
//        rowH = g_TileMap[0][0].dim.y;
//    else
//        rowH = colW;
//
//
//    float cell = (colW < rowH) ? colW : rowH;
//
//    g_goalRadius = 0.45f * cell;
//
//
//    float leftEdgeX = g_TileMap[0][0].centerPos.x - 0.5f * colW;
//
//
//    float goalMargin = 0.25f * cell;
//
//
//    for (int r = 0; r < TILE_ROWS; ++r) {
//        g_goalCenters[r].x = leftEdgeX - (g_goalRadius + goalMargin);
//        g_goalCenters[r].y = g_TileMap[r][0].centerPos.y;
//    }
//
//
//    g_drawGoals = 1;
//
//
//    for (int k = 0; k < (int)(sizeof(g_enemyHitCD) / sizeof(g_enemyHitCD[0])); ++k)
//        g_enemyHitCD[k] = 0.0f;
//}
//
//void Test_Update(void)
//{
//    float dt = CP_System_GetDt();
//
//    CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
//    Map_Update();
//
//    HealthTimer_Update(dt);
//    Hearts_Update(dt);
//
//
//    if (Is_Mouse_Released(circles[0].centerPos.x, circles[0].centerPos.y, circles[0].diameter,
//        CP_Input_GetMouseX(), CP_Input_GetMouseY()))
//    {
//        GameEntity t = (GameEntity){
//            .centerPos = (CP_Vector){100, 100}, .rotation = 0, .isPlayer = 1,
//            .forwardVector = (CP_Vector){0, 0}, .color = (Color){255, 0, 0, 255},
//            .diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "template"
//        };
//        ActiveEntity ae;
//        ae.id = (int)playerArr.used;
//        ae.unit = t;
//        ae.fsm = (StateMachine){ .currState = IdleState };
//        ae.maxHealth = 100;
//        ae.health = 100;
//        ae.alive = 1;
//        ae.hasScored = 0;
//        ae.lastLeftmostX = t.centerPos.x - 0.5f * t.diameter;
//        Arr_Insert(&playerArr, ae);
//    }
//
//    /* players draw */
//    for (size_t i = 0; i < playerArr.used; ++i) {
//        ActiveEntity* ent = &playerArr.ActiveEntityArr[i];
//        FSM_Update(&ent->fsm, &ent->unit, dt);
//
//        GameEntity* p = &ent->unit;
//        if (p->isSel) { p->color.red = 0; p->color.green = 0; p->color.blue = 255; p->color.opacity = 255; }
//        else { p->color.red = 255; p->color.green = 0; p->color.blue = 0;   p->color.opacity = 255; }
//
//        CP_Settings_Fill(CP_Color_Create(p->color.red, p->color.green, p->color.blue, p->color.opacity));
//        CP_Graphics_DrawCircle(p->centerPos.x, p->centerPos.y, p->diameter);
//    }
//
//
//    for (size_t i = 0; i < enemyArr.used; ++i) {
//        ActiveEntity* ent = &enemyArr.ActiveEntityArr[i];
//        FSM_Update(&ent->fsm, &ent->unit, dt);
//        Move_Wave(&ent->unit, dt);
//
//        GameEntity* e = &ent->unit;
//        if (e->isSel) { e->color.red = 255; e->color.green = 255; e->color.blue = 255; e->color.opacity = 255; }
//        else { e->color.red = 255; e->color.green = 255; e->color.blue = 0;   e->color.opacity = 255; }
//
//        CP_Settings_Fill(CP_Color_Create(e->color.red, e->color.green, e->color.blue, e->color.opacity));
//        CP_Graphics_DrawCircle(e->centerPos.x, e->centerPos.y, e->diameter);
//
//
//        Health_DrawEnemyBar(ent, 80.0f, 10.0f, 20.0f);
//    }
//
//
//    DamageEnemiesOnPlayerCollisions(34, 0.30f, dt);
//    ProcessGoalHits();
//
//
//    if (g_drawGoals) {
//        CP_Settings_Fill(CP_Color_Create(0, 0, 0, 0));
//        CP_Settings_Stroke(CP_Color_Create(255, 0, 0, 160));
//        CP_Settings_StrokeWeight(3.0f);
//        for (int r = 0; r < TILE_ROWS; ++r)
//            CP_Graphics_DrawCircle(g_goalCenters[r].x, g_goalCenters[r].y, g_goalRadius * 2.0f);
//    }
//
//
//    CP_Settings_RectMode(CP_POSITION_CENTER);
//    CP_Settings_Fill(CP_Color_Create(circles[0].color.red, circles[0].color.green, circles[0].color.blue, circles[0].color.opacity));
//    CP_Graphics_DrawCircle(circles[0].centerPos.x, circles[0].centerPos.y, circles[0].diameter);
//
//
//    Hearts_Draw();
//
//    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
//    CP_Settings_TextSize(28.0f);
//    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_RIGHT, CP_TEXT_ALIGN_V_TOP);
//
//    char tbuf[48];
//    snprintf(tbuf, sizeof(tbuf), "Time: %.1fs", HealthTimer_Seconds());
//
//    float pad = 12.0f;
//    float tx = (float)CP_System_GetWindowWidth() - pad;
//    CP_Font_DrawText(tbuf, tx, pad);
//}
//
//void Test_Exit(void)
//{
//    if (myFont)  CP_Font_Free(myFont);
//    if (mySound) CP_Sound_Free(mySound);
//}