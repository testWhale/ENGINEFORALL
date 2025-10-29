#include "state/pickup.h"
#include "utils/utils.h"
#include "utils/container.h"
#include "utils/arr.h"
#include "utils/SM.h"
#include "utils/readTxt.h"
#include "utils/wave/wave.h"
#include <stdlib.h>
#include <time.h>
//define minWidth of HealthBar
#define minWidth 0.0f
#define maxWidth 1400.0f
#define extraBars 10



//defined Sound
CP_Sound mySound = NULL;



float winWidth;
float winHeight;

//Array of Players
GameEntity players[1];
GameEntity* Player;
GameEntity _player;
StateMachine* _SM;

Color Blue = { 0, 0, 255, 255 };
Color Green = { 0, 255, 0, 255 };
Color Red = { 255, 0, 0, 255 };
Color White = { 0, 0, 0, 255};
void inArea(CP_Vector, CP_Vector);
typedef void (*funcArea)(CP_Vector, CP_Vector);

typedef struct {
	int id;
	CP_Vector centerPos;
	float diameter;
	Color color;
	funcArea inArea;
}Circle;

Circle circles[2];
float width = maxWidth;
float startPoint = 100.0f;
int maxed;
int minimum;
int indent = 146;
int size = 80;
int i;
CP_Font myFont;


int isInArea(Circle circle, GameEntity* player) {
	CP_Vector PlayerToCircleDist = CP_Vector_Subtract(circle.centerPos, player->centerPos);
	float distLength = CP_Vector_Length(PlayerToCircleDist);

	if (distLength - (player->diameter / 2) <= circle.diameter / 2) {
		//printf("%f\n", distLength);
		//printf("In contact\n");
		return 1;
	}
	return 0;
}


//StateMachine fsmList[MAX_ENTITIES];
//, { 1, {300, 200}, 0, 0, {0, 0}, {0,255,0,255}, 120 },
//{ 2, {500, 300}, 0, 0, {0, 0}, {0,255,0,255}, 120 }

/*LOADS IN PLAYER ARRAY */
void initPlayerDemo() {
	/*-------------Template Value--------------*/
	GameEntity template = (GameEntity){
	.id = 0, .centerPos = {100, 100}, .rotation = 0, .isPlayer = 1, .forwardVector = {0, 0}, .color = {255,0,0,255},
	.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "Fire" };
	GameEntity enemy = (GameEntity){
.id = 0, .centerPos = {100, 400}, .rotation = 0, .isPlayer = 0, .forwardVector = {0, 0}, .color = {255,0,0,255},
.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "Fire" };

	Arr_Init(2, &playerArr);
	Arr_Init(10, &enemyArr);
	/*FOR PLAYER_UNITS ONLY*/
	for (int i = 0; i < 4; i++) {
		Arr_Insert(&playerArr, (ActiveEntity){ 
			.id = i, 
			.unit = template, 
			.fsm = (StateMachine) { .currState = IdleState }});
		printf("CHECK AFTER INSERT: %d, \n", playerArr.ActiveEntityArr[i].id);
		playerArr.ActiveEntityArr[i].unit.centerPos.x = template.centerPos.x + i * 100;
		playerArr.ActiveEntityArr[i].unit.id = i;

		printf("ID: %d\n", playerArr.ActiveEntityArr[i].id);
	} 
	/* FOR ENEMY UNITS */


	for (int i = 0; i < 11; i++) {
		Arr_Insert(&enemyArr, (ActiveEntity) {
			.id = i,
			.unit = enemy,
			.fsm = (StateMachine){ .currState = IdleState }
		});
		printf("CHECK AFTER INSERT: %d, \n", enemyArr.ActiveEntityArr[i].id);
		enemyArr.ActiveEntityArr[i].unit.centerPos.x = 1600;
		enemyArr.ActiveEntityArr[i].unit.id = i;

		startWave(&enemyArr.ActiveEntityArr[i].unit, (int)(2));
		printf("ID: %d\n", enemyArr.ActiveEntityArr[i].id);
	}
	ContArr_Init(playerArr.used, &containersArr);
	readFile("Assets/containers");
}



void Test_Init(void)
{
	float dt = CP_System_GetDt();
	srand(time((int)dt));
	Map_Init();
	initPlayerDemo();
	//initEnemies();
	winHeight = CP_System_GetWindowHeight();
	winWidth = CP_System_GetWindowWidth();
	//players[0] = (GameEntity){ 0, {100.0f, 100.0f}, 0, 1, {0, 0}, Blue, 150 };
	circles[0] = (Circle){ 0, {winWidth / 3 * 1, winHeight / 2}, 300, Red };
	//circles[1] = (Circle){ 1, {winWidth / 3 * 2, winHeight / 2}, 300, Green };

	//_SM.currState = IdleState; //SetState(..., deltaTime)

	// ExitDamageState
	//_SM_Instance.transitionMap[Damage] = Exit_Damage_State;
	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	mySound = CP_Sound_Load("Assets/sound.mp3");

	/*EXTERNAL FUNCTIONS*/



	//myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
}

int count = 0;

void Test_Update(void)
{
	Container contTemplate = (Container){ 1, "Fire", (CP_Vector) { 100,100 }, 300, 200, "Assets/buttons/Troop_3.png", 1.0, 255, 0 };

	GameEntity template = (GameEntity){
	.id = 0, .centerPos = {100, 100}, .rotation = 0, .isPlayer = 0, .forwardVector = {0, 0}, .color = {255,0,0,255},
	.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "template" };

	float dt = CP_System_GetDt();
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	Map_Update();
	
	if (IsCircleClicked(circles->centerPos.x, circles->centerPos.y, circles->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {

		Arr_Insert(&playerArr, (ActiveEntity) { playerArr.used, template, (StateMachine) { .currState = IdleState } });
		//ContArr_Insert(&containersArr,contTemplate);
	}
	for (int i = 0; i < playerArr.used; i++) {
		ActiveEntity* UnitEntity = &playerArr.ActiveEntityArr[i];
		FSM_Update(&(UnitEntity->fsm), &(UnitEntity->unit), dt);

		GameEntity* ptr = &(UnitEntity->unit);

		if (ptr->isSel) { ptr->color.red = 0, ptr->color.green = 0, ptr->color.blue = 255, ptr->color.opacity = 255; }
		else { ptr->color.red = 255, ptr->color.green = 0, ptr->color.blue = 0, ptr->color.opacity = 255; }
		CP_Settings_Fill(CP_Color_Create(ptr->color.red, ptr->color.green, ptr->color.blue, ptr->color.opacity));
		CP_Graphics_DrawCircle(ptr->centerPos.x, ptr->centerPos.y, ptr->diameter);
		//printf("%s", activeEntityList[i].fsm.currState);
	}
	for (int i = 0; i < enemyArr.used; i++) {
		ActiveEntity* EnemyEntity = &enemyArr.ActiveEntityArr[i];
		FSM_Update(&(EnemyEntity->fsm), &(EnemyEntity->unit), dt);
		GameEntity* enemyPtr = &(EnemyEntity->unit);
		moveWave(enemyPtr, dt);
		if (enemyPtr->isSel) { enemyPtr->color.red = 255, enemyPtr->color.green = 255, enemyPtr->color.blue = 255, enemyPtr->color.opacity = 255; }
		else { enemyPtr->color.red = 255, enemyPtr->color.green = 255, enemyPtr->color.blue = 0, enemyPtr->color.opacity = 255; }
		CP_Settings_Fill(CP_Color_Create(enemyPtr->color.red, enemyPtr->color.green, enemyPtr->color.blue, enemyPtr->color.opacity));
		CP_Graphics_DrawCircle(enemyPtr->centerPos.x, enemyPtr->centerPos.y, enemyPtr->diameter);

	}
	



	//Set Circles
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_Fill(CP_Color_Create(circles[0].color.red, circles[0].color.green, circles[0].color.blue, circles[0].color.opacity));
	CP_Graphics_DrawCircle(circles[0].centerPos.x, circles[0].centerPos.y, circles[0].diameter);

	//// draw
	//CP_Settings_RectMode(CP_POSITION_CENTER);
	//CP_Settings_Fill(CP_Color_Create(circles[1].color.red, circles[1].color.green, circles[1].color.blue, circles[1].color.opacity));
	//CP_Graphics_DrawCircle(circles[1].centerPos.x, circles[1].centerPos.y, circles[1].diameter);
	
}

void Test_Exit(void)
{
	//Container_Destroy(&CONTAINERS[0]);
	//Container_Destroy(&CONTAINERS[1]);
	//Container_Destroy(&CONTAINERS[2]);
	//Container_Destroy(&CONTAINERS[3]);
	CP_Font_Free(myFont);
	CP_Sound_Free(mySound);
}