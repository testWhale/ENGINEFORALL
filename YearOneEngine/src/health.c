//#include "health.h"
//
//
////define minWidth of HealthBar
//#define minWidth 0.0f
//#define maxWidth 1400.0f
//#define extraBars 10
//
////defined Sound
//CP_Sound mySound = NULL;
//
////Defined Colours
//Color Green = { 0, 255, 0, 255 };
//Color Red = { 255, 0, 0, 255 };
//Color Blue = { 0, 0, 255, 255 };
//
//float winWidth;
//float winHeight;
//
////Array of Players
//GameEntity players[1];
//GameEntity* Player;
//EntityData _player;
//StateMachine _SM_Instance;
//States Damage;
//
//void inArea(CP_Vector, CP_Vector);
//typedef void (*funcArea)(CP_Vector,CP_Vector);
//
//typedef struct {
//	int id;
//	CP_Vector centerPos;
//	float diameter;
//	Color color;
//	funcArea inArea;
//}Circle;
//
//Circle circles[2];
//float width = maxWidth;
//float startPoint = 100.0f;
//int maxed;
//int minimum;
//int indent = 146;
//int size = 80;
//int i;
//CP_Font myFont;
//
//// Transition state code
//StateFunction SM_SetState(StateMachine _SM_Instance, States newState, EntityData _entityData, float currentElapsedTime) {
//	_SM_Instance.currState.exit;
//	_SM_Instance.currState = newState;
//	_SM_Instance.currState.init = newState.init;
//	if (!_SM_Instance.currState.init) {
//		printf("Invalid state or unassigned state function.\n");
//	}
//
//}
//States IdleState = {
//	.init = PlayerIdle_Init,
//	.update = PlayerIdle_Update,
//	.exit = PlayerIdle_Exit
//};
//States AttackState = {
//	.init = PlayerAttack_Init,
//	.update = PlayerAttack_Update,
//	.exit = PlayerAttack_Exit
//};
//
//void PlayerIdle_Init(EntityData* entity, float dt) {
//	printf("Player entered IDLE state\n");
//	entity->entityData.color.red = 100;
//	entity->entityData.color.green = 100;
//	entity->entityData.color.blue = 255;
//	entity->stateTimer = 0.0f;
//}
//
//void PlayerIdle_Update(EntityData* entity, float dt) {
//	entity->stateTimer += dt;
//
//	// Example: Transition to Attack if "attack" input detected
//	// In real game, check input here
//	if (CP_Input_KeyDown(KEY_P)) {
//		SetPlayerState(entity, &AttackState, dt);
//		return;
//	}
//
//	//// Example: Take damage randomly to trigger Damaged state
//	//if (/* random damage event */) {
//	//	entity->entityData.health -= 20.0f;
//	//	if (entity->entityData.health > 0) {
//	//		SetPlayerState(entity, &DamagedState, dt);
//	//	}
//	//	return;
//	//}
//
//	// Idle logic (e.g., slight animations, etc.)
//}
//
//void PlayerIdle_Exit(EntityData* entity, float dt) {
//	printf("Player left IDLE state\n");
//}
//
//void PlayerIdle_Init(EntityData* entity, float dt) {
//	printf("Player entered IDLE state\n");
//	entity->entityData.color.red = 100;
//	entity->entityData.color.green = 100;
//	entity->entityData.color.blue = 255;
//	entity->stateTimer = 0.0f;
//}
//
//void PlayerIdle_Update(EntityData* entity, float dt) {
//	entity->stateTimer += dt;
//
//	// Example: Transition to Attack if "attack" input detected
//	// In real game, check input here
//	if (CP_Input_KeyDown(KEY_P)) {
//		SetPlayerState(entity, &AttackState, dt);
//		return;
//	}
//
//	//// Example: Take damage randomly to trigger Damaged state
//	//if (/* random damage event */) {
//	//	entity->entityData.health -= 20.0f;
//	//	if (entity->entityData.health > 0) {
//	//		SetPlayerState(entity, &DamagedState, dt);
//	//	}
//	//	return;
//	//}
//
//	// Idle logic (e.g., slight animations, etc.)
//}
//
//void PlayerIdle_Exit(EntityData* entity, float dt) {
//	printf("Player left IDLE state\n");
//}
//
//void Movement(float currentElapsedTime) {
//	Player->centerPos.x += Player->forwardVector.x * currentElapsedTime * 30;
//	Player->centerPos.y += Player->forwardVector.y * currentElapsedTime * 30;
//}
//int isInArea(Circle circle, GameEntity* player){
//	CP_Vector PlayerToCircleDist = CP_Vector_Subtract(circle.centerPos, player->centerPos);
//	float distLength = CP_Vector_Length(PlayerToCircleDist);
//	
//	if (distLength - (player->diameter / 2) <= circle.diameter / 2) {
//		//printf("%f\n", distLength);
//		//printf("In contact\n");
//		return 1;
//	}
//	return 0;
//}
//
//float DOT = 0;
////update State]
//
//
//States Damage{
//	.init = Damage_Init,
//	.update = Damage_Update,
//	.exit = Damage_Exit
//};
//void Damage_State() {
//	
//}
//void Recover_State(void* entityPtr, float deltaTime) {
//	
//	float futureWidth = width + 3;
//	if (width > maxWidth)
//	{
//		width = 1400;
//		maxed = 1;
//	}
//	if (1!= maxed) {
//		//printf("Recover\n");
//		width += 5;
//		minimum = 0;
//		Player->color = (Color){ 0,255,0,255 };
//		DOT += deltaTime;
//		CP_Font_Set(myFont);
//		CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
//		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
//		CP_Settings_TextSize(60.0f);
//		CP_Font_DrawText("Play", Player->centerPos.x + 100, Player->centerPos.y+100);
//		CP_Sound_Play(mySound);
//	}
//	if (DOT > 0.5) {
//		Player->color = (Color){ 0,0,255,255 };
//		DOT = 0;
//	}
//}
//
//int extraHealth() {
//	if (maxWidth /10 -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint, 200.0f, size, 50.0f);
//	}
//	if (((maxWidth / 10) * 2) -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent, 200.0f, size, 50.0f);
//	}
//	if (((maxWidth / 10) * 3) -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent*2, 200.0f, size, 50.0f);
//	}
//	if (((maxWidth / 10) * 4) -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent*3, 200.0f, size, 50.0f);
//	}
//	if (((maxWidth / 10) * 5) -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent*4, 200.0f, size, 50.0f);
//	}
//	if (((maxWidth / 10) * 6) -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent * 5, 200.0f, size, 50.0f);
//	}
//	if (((maxWidth / 10) * 7) -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent * 6, 200.0f, size, 50.0f);
//	}
//	if (((maxWidth / 10) * 8) -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent * 7, 200.0f, size, 50.0f);
//	}
//	if (((maxWidth / 10) * 9) -120 < width) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent * 8, 200.0f, size, 50.0f);
//	}
//	if (width > maxWidth - 100) {
//		CP_Settings_RectMode(CP_POSITION_CORNER);
//		CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//
//		CP_Graphics_DrawRect(startPoint + indent * 9, 200.0f, size, 50.0f);
//	}
//	
//	
//}
//
//
//
//void Health_Init(void)
//{
//	winHeight = CP_System_GetWindowHeight();
//	winWidth = CP_System_GetWindowWidth();
//    players[0] = (GameEntity){ 0, {100.0f, 100.0f}, 0, 1, {0, 0}, Blue, 150};
//	circles[0] = (Circle){ 0, {winWidth / 3 * 1, winHeight / 2}, 300, Red };
//	circles[1] = (Circle){ 1, {winWidth / 3 * 2, winHeight / 2}, 300, Green};
//	
//	_SM_Instance.currState = Damage_State; //SetState(..., deltaTime)
//	_SM_Instance.currState = Recover_State;
//	
//	// ExitDamageState
//	//_SM_Instance.transitionMap[Damage] = Exit_Damage_State;
//	myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
//	mySound = CP_Sound_Load("Assets/sound.mp3");
//
//    //myFont = CP_Font_Load("Assets/Exo2-Regular.ttf");
//}
//
//
//
//void Health_Update(void)
//{
//	Player = &players[0];
//	float dt = CP_System_GetDt();
//	SM_UpdateState(
//	//if smt happens
//		//setState
//	);
//    CP_Graphics_ClearBackground(CP_Color_Create(128, 128, 128, 255));
//
//	//Set Circles
//	CP_Settings_RectMode(CP_POSITION_CENTER);
//	CP_Settings_Fill(CP_Color_Create(circles[0].color.red, circles[0].color.green, circles[0].color.blue, circles[0].color.opacity));
//	CP_Graphics_DrawCircle(circles[0].centerPos.x, circles[0].centerPos.y, circles[0].diameter);
//
//	// draw
//	CP_Settings_RectMode(CP_POSITION_CENTER);
//	CP_Settings_Fill(CP_Color_Create(circles[1].color.red, circles[1].color.green, circles[1].color.blue, circles[1].color.opacity));
//	CP_Graphics_DrawCircle(circles[1].centerPos.x, circles[1].centerPos.y, circles[1].diameter);
//
//	if (isInArea(circles[0], Player)) {
//		SM_SetState(_SM_Instance, Damage, _player, dt);
//	}
//	if (isInArea(circles[1], Player)) {
//		SM_SetState(_SM_Instance, Recover, _player, dt);
//	}
//	//game loop
//	//init Statemachine -> c
//	//Update stateMachine -> if checks update state 
//
//
//	
//	if (Player->isPlayer == 1) {
//		// Clear the background
//		if (CP_Input_KeyDown(KEY_W))
//		{
//			Player->forwardVector.y = -10.0f;
//			Player->forwardVector.x = 0.0f;
//
//			Player->rotation = 90.0;
//			Movement(dt);
//
//		}
//		if (CP_Input_KeyDown(KEY_A))
//		{
//			Player->forwardVector.x = -10.0f;
//			Player->forwardVector.y = 0.0f;
//
//			Player->rotation = 0;
//			Movement(dt);
//		}
//		if (CP_Input_KeyDown(KEY_S))
//		{
//			Player->forwardVector.y = 10.0f;
//			Player->forwardVector.x = 0.0f;
//
//			Player->rotation = 270.0;
//			Movement(dt);
//		}
//		if (CP_Input_KeyDown(KEY_D))
//		{
//			Player->forwardVector.x = 10.0f;
//			Player->forwardVector.y = 0.0f;
//
//			Player->rotation = 180.0;
//			Movement(dt);
//		}
//	}
//
//	CP_Settings_RectMode(CP_POSITION_CENTER);
//	CP_Settings_Fill(CP_Color_Create(Player->color.red, Player->color.green, Player->color.blue, Player->color.opacity));
//	CP_Graphics_DrawCircle(Player->centerPos.x, Player->centerPos.y, Player->diameter);
//	Player->color = (Color){ 0,0,255,255 };
//
//	//Shadow Health Bar
//	CP_Settings_RectMode(CP_POSITION_CORNER);
//	CP_Settings_Fill(CP_Color_CreateHex(0x8B0000FF));
//	CP_Graphics_DrawRect(100.0f, 100.0f, maxWidth, 50.0f);
//	//Health Bar
//	CP_Settings_RectMode(CP_POSITION_CORNER);
//	CP_Settings_Fill(CP_Color_Create(255, 0, 0, 255));
//	CP_Graphics_DrawRect(100.0f, 100.0f, width, 50.0f);
//	
//	extraHealth();
//	
//}
//
//void Health_Exit(void)
//{
//    CP_Font_Free(myFont);
//	CP_Sound_Free(mySound);
//}