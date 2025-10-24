#include "state/pickup.h"
#include "utils/utils.h"
#include "utils/container.h"
#include "utils/arr.h"
#include "utils/SM.h"
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

//TestArr


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

GameEntity template[MAX_ENTITIES] = { {0, {100, 100}, 0, 0, {0, 0}, {255,0,0,255}, 100}, { 1, {300, 200}, 0, 0, {0, 0}, {0,255,0,255}, 120 } };
ActiveEntity tempAct = { 0, &template[0], &IdleState };
StateMachine fsmPool[MAX_ENTITIES];
static StateMachine fsmList[MAX_ENTITIES];
void initEnemies() {
	for (int i = 0; i < MAX_ENTITIES; i++) {
		//activeEntityList[i].unit = &template[i];
		//activeEntityList[i].fsm = &fsmList[i];
		//activeEntityList[i].fsm->currState = IdleState;
		newArr.ActiveEntityArr[i].unit = NULL;
		newArr.ActiveEntityArr[i].fsm = NULL;

		newArr.ActiveEntityArr[i].unit = &template[i];
		newArr.ActiveEntityArr[i].fsm = &fsmList[i];
		newArr.ActiveEntityArr[i].fsm->currState = IdleState;
	}

}


void Test_Init(void)
{
	//initEnemies();
	winHeight = CP_System_GetWindowHeight();
	winWidth = CP_System_GetWindowWidth();
	players[0] = (GameEntity){ 0, {100.0f, 100.0f}, 0, 1, {0, 0}, Blue, 150 };
	circles[0] = (Circle){ 0, {winWidth / 3 * 1, winHeight / 2}, 300, Red };
	circles[1] = (Circle){ 1, {winWidth / 3 * 2, winHeight / 2}, 300, Green };

	//_SM.currState = IdleState; //SetState(..., deltaTime)

	// ExitDamageState
	//_SM_Instance.transitionMap[Damage] = Exit_Damage_State;
	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
	mySound = CP_Sound_Load("Assets/sound.mp3");
	
	/*EXTERNAL FUNCTIONS*/
	Map_Init();
	CONTAINERS[0] = (Container){ 0, "TEST", {100.0f,100.0f},264,595,NULL,"Assets/templ0.jpg" };
	CONTAINERS[1] = (Container){ 1, "Icons", {300.0f,300.0f},797,144,NULL,"Assets/templ1.jpg" };

	Container_Init(&CONTAINERS[0]);
	newArr = Arr_Init(3);
	initEnemies();

	//myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
}

int count = 0;


void Test_Update(void)
{
	Player = &players[0];
	float dt = CP_System_GetDt();
	
	CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
	Map_Update();
	 
	Container_Update(&CONTAINERS[0]);
	for (int i = 0; i < MAX_ENTITIES; i++) {
		ActiveEntity entity = newArr.ActiveEntityArr[i];
		FSM_Update(entity.fsm, entity.unit, dt);
		GameEntity* ptr = entity.unit;
		//if (ptr->isSel==1) {
		//	count+=1;
		//	printf("%d\n", ptr->isSel);
		//	if (count > 1) {
		//		printf("HUH2");
		//		//more than one isSel meaning DESELECT ALL
		//		deselectEnt();
		//		count = 0;
		//	}
		//}
		CP_Settings_Fill(CP_Color_Create(ptr->color.red, ptr->color.green, ptr->color.blue, ptr->color.opacity));
		CP_Graphics_DrawCircle(ptr->centerPos.x, ptr->centerPos.y, ptr->diameter);
		
		//printf("%s", activeEntityList[i].fsm.currState);
	}


	////Set Circles
	//CP_Settings_RectMode(CP_POSITION_CENTER);
	//CP_Settings_Fill(CP_Color_Create(circles[0].color.red, circles[0].color.green, circles[0].color.blue, circles[0].color.opacity));
	//CP_Graphics_DrawCircle(circles[0].centerPos.x, circles[0].centerPos.y, circles[0].diameter);

	//// draw
	//CP_Settings_RectMode(CP_POSITION_CENTER);
	//CP_Settings_Fill(CP_Color_Create(circles[1].color.red, circles[1].color.green, circles[1].color.blue, circles[1].color.opacity));
	//CP_Graphics_DrawCircle(circles[1].centerPos.x, circles[1].centerPos.y, circles[1].diameter);
	
}

void Test_Exit(void)
{
	Container_Destroy(&CONTAINERS[0]);
	Container_Destroy(&CONTAINERS[1]);

	CP_Font_Free(myFont);
	CP_Sound_Free(mySound);
}