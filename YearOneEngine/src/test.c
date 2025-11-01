#include "state/pickup.h"
#include "utils/utils.h"
#include "utils/container.h"
#include "utils/arr.h"
#include "utils/SM.h"
#include "utils/readTxt.h"
#include "utils/wave/wave.h"
#include <stdlib.h>
#include <time.h>
#include "utils/health/health.h"

/* Health bar sizing */
#define minWidth  0.0f
#define maxWidth  1400.0f
#define extraBars 10

/* Sound */
CP_Sound mySound = 0;

/* Window size cache */
float winWidth;
float winHeight;

/* Example globals already used in your project */
GameEntity  players[1];
GameEntity* Player;
GameEntity  _player;
StateMachine* _SM;

/* Simple colors (your Color struct) */
Color Blue = { 0,   0, 255, 255 };
Color Green = { 0, 255,   0, 255 };
Color Red = { 255, 0,   0, 255 };
Color White = { 0,   0,   0, 255 };

void inArea(CP_Vector, CP_Vector);
typedef void (*funcArea)(CP_Vector, CP_Vector);

typedef struct {
    int       id;
    CP_Vector centerPos;
    float     diameter;
    Color     color;
    funcArea  inArea;
} Circle;

Circle circles[2];
float  width = maxWidth;
float  startPoint = 100.0f;
int    maxed;
int    minimum;
int    indent = 146;
int    size = 80;
int    i;
CP_Font myFont;

/* Utility: click in circle */
int isInArea(Circle circle, GameEntity* player)
{
    CP_Vector v = CP_Vector_Subtract(circle.centerPos, player->centerPos);
    float dist = CP_Vector_Length(v);
    return (dist - (player->diameter * 0.5f) <= circle.diameter * 0.5f);
}

/* -------------------------------------------------------------------------- */
/*                               Init players                                  */
/* -------------------------------------------------------------------------- */
void initPlayerDemo(void)
{
    /* ---- Templates (match your GameEntity member order) ---- */
    GameEntity playerTemplate;
    playerTemplate.id = 0;
    playerTemplate.centerPos.x = 100.0f;
    playerTemplate.centerPos.y = 100.0f;
    playerTemplate.rotation = 0.0f;
    playerTemplate.isPlayer = 1;
    playerTemplate.forwardVector.x = 0.0f;
    playerTemplate.forwardVector.y = 0.0f;
    playerTemplate.color = (Color){ 255, 0, 0, 255 };
    playerTemplate.diameter = 100.0f;
    playerTemplate.stateTimer = 0.0f;
    playerTemplate.isItOnMap = 0;
    playerTemplate.isSel = 0;
    playerTemplate.label = "Fire";

    GameEntity enemyTemplate = playerTemplate;
    enemyTemplate.centerPos.y = 400.0f;
    enemyTemplate.isPlayer = 0;

    Arr_Init(2, &playerArr);
    Arr_Init(10, &enemyArr);

    /* ---- Spawn 4 player units ---- */
    for (int k = 0; k < 4; ++k) {
        ActiveEntity ae;
        ae.id = k;
        ae.unit = playerTemplate;
        ae.unit.centerPos.x = playerTemplate.centerPos.x + k * 100.0f;
        ae.unit.id = k;
        ae.fsm.currState = IdleState;
        ae.health = 100;
        ae.maxHealth = 100;
        ae.alive = 1;

        Arr_Insert(&playerArr, ae);
    }

    /* ---- Spawn 11 enemies (start on right, move by wave) ---- */
    for (int k = 0; k < 11; ++k) {
        ActiveEntity ae = { 0 };
        ae.id = k;
        ae.unit = enemyTemplate;        // enemyTemplate.isPlayer == 0
        ae.fsm.currState = IdleState;
        ae.maxHealth = 100;
        ae.health = 100;
        ae.alive = 1;

        Arr_Insert(&enemyArr, ae);

        ActiveEntity* e = &enemyArr.ActiveEntityArr[enemyArr.used - 1];

        startWave(&e->unit, 2);                 

        e->unit.centerPos.x = 1600.0f;          
        e->hasScored = 0;
        e->lastLeftmostX = e->unit.centerPos.x - 0.5f * e->unit.diameter;
    }



    /* Containers UI + data */
    ContArr_Init(playerArr.used, &containersArr);
    readFile("Assets/containers");
}

/* -------------------------------------------------------------------------- */
/*                                 Test_Init                                   */
/* -------------------------------------------------------------------------- */
void Test_Init(void)
{
    srand((unsigned)time(NULL));   //

    Map_Init();
    initPlayerDemo();

    winHeight = (float)CP_System_GetWindowHeight();
    winWidth = (float)CP_System_GetWindowWidth();

    /* Setup one red circle button */
    circles[0].id = 0;
    circles[0].centerPos.x = winWidth / 3.0f;
    circles[0].centerPos.y = winHeight / 2.0f;
    circles[0].diameter = 300.0f;
    circles[0].color = Red;
    circles[0].inArea = NULL;

    myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
    mySound = CP_Sound_Load("Assets/sound.mp3");

    /* Health / audio / GO binding */
    Hearts_Init(3);
    HealthAudio_Load("Assets/Metal Ping by timgormly Id-170957.wav",
        "Assets/Glass Break by unfa Id-221528.wav");

    extern void GameOver_SetData(float, int);
    extern void GameOver_Init(void);
    extern void GameOver_Update(void);
    extern void GameOver_Exit(void);
    Health_BindGameOver(GameOver_SetData, GameOver_Init, GameOver_Update, GameOver_Exit);

    HealthTimer_Reset();
}

/* -------------------------------------------------------------------------- */
/*                                Test_Update                                  */
/* -------------------------------------------------------------------------- */
void Test_Update(void)
{
    float dt = CP_System_GetDt();

    CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
    Map_Update();

    HealthTimer_Update(dt);
    Hearts_Update(dt);

    /* Click to add a player unit using a simple template */
    if (IsCircleClicked(circles[0].centerPos.x, circles[0].centerPos.y, circles[0].diameter,
        CP_Input_GetMouseX(), CP_Input_GetMouseY()))
    {
        GameEntity unitTemplate;
        unitTemplate.id = 0;
        unitTemplate.centerPos.x = 100.0f;
        unitTemplate.centerPos.y = 100.0f;
        unitTemplate.rotation = 0.0f;
        unitTemplate.isPlayer = 0;
        unitTemplate.forwardVector.x = 0.0f;
        unitTemplate.forwardVector.y = 0.0f;
        unitTemplate.color = (Color){ 255, 0, 0, 255 };
        unitTemplate.diameter = 100.0f;
        unitTemplate.stateTimer = 0.0f;
        unitTemplate.isItOnMap = 0;
        unitTemplate.isSel = 0;
        unitTemplate.label = "template";

        ActiveEntity ae;
        ae.id = (int)playerArr.used;
        ae.unit = unitTemplate;
        ae.fsm.currState = IdleState;
        ae.health = 100;
        ae.maxHealth = 100;
        ae.alive = 1;

        Arr_Insert(&playerArr, ae);
    }

    /* ---- Players ---- */
    for (int k = 0; k < (int)playerArr.used; ++k) {
        ActiveEntity* ent = &playerArr.ActiveEntityArr[k];
        FSM_Update(&ent->fsm, &ent->unit, dt);

        GameEntity* p = &ent->unit;
        if (p->isSel) { p->color.red = 0;   p->color.green = 0;   p->color.blue = 255; p->color.opacity = 255; }
        else { p->color.red = 255; p->color.green = 0;   p->color.blue = 0;   p->color.opacity = 255; }

        CP_Settings_Fill(CP_Color_Create(p->color.red, p->color.green, p->color.blue, p->color.opacity));
        CP_Graphics_DrawCircle(p->centerPos.x, p->centerPos.y, p->diameter);
    }

    /* ---- Enemies ---- */
    for (int k = 0; k < (int)enemyArr.used; ++k) {
        ActiveEntity* ent = &enemyArr.ActiveEntityArr[k];
        FSM_Update(&ent->fsm, &ent->unit, dt);
        moveWave(&ent->unit, dt);

        GameEntity* e = &ent->unit;
        if (e->isSel) { e->color.red = 255; e->color.green = 255; e->color.blue = 255; e->color.opacity = 255; }
        else { e->color.red = 255; e->color.green = 255; e->color.blue = 0; e->color.opacity = 255; }

        CP_Settings_Fill(CP_Color_Create(e->color.red, e->color.green, e->color.blue, e->color.opacity));
        CP_Graphics_DrawCircle(e->centerPos.x, e->centerPos.y, e->diameter);

        /* Enemy HP bar */
        Health_DrawEnemyBar(ent, 80.0f, 10.0f, 20.0f);
    }

    /* If any enemy reaches the leftmost column, lose a heart and remove it */
    Health_ProcessLeftGoal(&enemyArr, startPoint);

    /* UI circle button */
    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_Fill(CP_Color_Create(circles[0].color.red, circles[0].color.green, circles[0].color.blue, circles[0].color.opacity));
    CP_Graphics_DrawCircle(circles[0].centerPos.x, circles[0].centerPos.y, circles[0].diameter);

    /* Hearts HUD on top */
    Hearts_Draw();
}

/* -------------------------------------------------------------------------- */
/*                                 Test_Exit                                   */
/* -------------------------------------------------------------------------- */
void Test_Exit(void)
{
    CP_Font_Free(myFont);
    CP_Sound_Free(mySound);
}
