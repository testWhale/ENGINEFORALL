#include "cprocessing.h"
#include "ent.h"
#include "../SM.h"
#include "../arr.h"
#include "../state/enemy.h"
#include "../utils/arr/State.h"
#include "../wave/wave.h"
#include "health.h"
#include "../container.h"
#include "../buttons/buttonCode.h"
#include "../scenes/mainmenu.h"
#include "../economy/economyCode.h"
#include "state/shoot.h"
extern int wave = 0;
extern int waveFlag = 0;
extern float waveState = 0;
ButtonInfo NewWaveButton;
ButtonSound defaultSound;

/*-------------Template Value--------------*/
GameEntity Make_Template(const char* name) {
	GameEntity e;
	if (name == "player")
	{
		e = (GameEntity){
		.centerPos = {400, 100}, .rotation = 0, .isPlayer = 1, .forwardVector = {0, 0}, .color = {255,0,0,255},
		.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "fire", .bullets = {0 } };
	}


	if (name == "poison")
	{
		Bullet temp = Bullet_Template("poison");
		e = (GameEntity){
		.centerPos = {400, 150}, .rotation = 0, .isPlayer = 0, .forwardVector = {0, 0}, .color = {255,0,255,255},
		.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "poison" , .bullets = {0} };
		B_Arr_Insert(&e.bullets, temp);
		/*B_Arr_Init(2, &e.bullets);
		B_Arr_Insert(&e.bullets, temp);*/
	}

	if (name == "stun")
	{
		Bullet temp = Bullet_Template("stun");
		e = (GameEntity){
		.centerPos = {500, 100}, .rotation = 0, .isPlayer = 0, .forwardVector = {0, 0}, .color = {255,0,0,255},
		.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "fire" , .bullets = {0} };
		/*B_Arr_Init(2, &e.bullets);
		B_Arr_Insert(&e.bullets, temp);*/
	}

	if (name == "enemy")
	{

		e = (GameEntity){
		.centerPos = {100, 400}, .rotation = 0, .isPlayer = 0, .forwardVector = {0, 0}, .color = {255,255,0,255},
		.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "enemy" , .bullets = {0} };

	}
	//do not assign any pointers here as it will point to the same address
	/* aka:
	B_Arr_Init(10, &e.bullets);
	...
	GameEntity player = e
	GameEntity enemy = e
	both point to the same bullet array STOP */
	return e;
}

/*LOADS IN PLAYER & ENEMY ARRAY */
void Init_PlayerDemo() {

	GameEntity player = Make_Template("player");
	GameEntity enemy = Make_Template("enemy");

	/*-------------Template Value--------------*/
	Arr_Init(2, &playerArr);
	Arr_Init(11, &enemyArr);

	/*FOR PLAYER_UNITS ONLY*/
	for (int i = 0; i < 4; i++) {
		ActiveEntity ae;
		ae.id = i;
		ae.unit = player;
		ae.fsm = (StateMachine){ .currState = IdleState };
		ae.maxHealth = 100;
		ae.health = 100;
		ae.alive = 1;
		ae.hasScored = 0;
		ae.lastLeftmostX = 0.0f;
		printf("turrent ID: %d", ae.id);
		Arr_Insert(&playerArr, ae);
		playerArr.ActiveEntityArr[i].unit.centerPos.x = player.centerPos.x + i * 100.0f;

		//B_Arr_Init(10, &ae.unit.bullets);
	}


	/* FOR ENEMY UNITS */
	for (int i = 0; i < 5; i++) {
		ActiveEntity ae;
		ae.id = i;
		ae.unit = enemy;
		ae.fsm = (StateMachine){ .currState = EnemyIdleState };
		ae.maxHealth = 100;
		ae.health = 100;
		ae.alive = 1;
		ae.hasScored = 0;
		ae.lastLeftmostX = 0.0f;

		Arr_Insert(&enemyArr, ae);
		Start_Wave(&enemyArr.ActiveEntityArr[i].unit, 0);
		/*enemyArr.ActiveEntityArr[i].unit.centerPos.x += 200.0f;*/
	}
	//ContArr_Init(playerArr.used, &containersArr);
	//Read_File("Assets/containers");
}

void Init_NewWave(int currWave) {
	GameEntity enemy = Make_Template("enemy");
	/* FOR ENEMY UNITS */
	waveFlag = 1;
	int spawn = currWave + 5;
	for (int i = 0; i < spawn; i++) {
		ActiveEntity ae;
		ae.id = i;
		ae.unit = enemy;
		ae.fsm = (StateMachine){ .currState = IdleState };
		ae.maxHealth = 100;
		ae.health = 100;
		ae.alive = 1;
		ae.hasScored = 0;
		ae.lastLeftmostX = 0.0f;

		Arr_Insert(&enemyArr, ae);
		Start_Wave(&enemyArr.ActiveEntityArr[i].unit, (int)2);

		/*enemyArr.ActiveEntityArr[i].unit.centerPos.x += 200.0f;*/
	}
}

void Load_TempText() {
	Button_Load(&NewWaveButton, &defaultSound,
		96 * unit, 92 * unit,
		20 * unit, 20 * unit,
		0 * unit,
		"Assets/Buttons/Suprise/JackNormal.png",
		"Assets/Buttons/Suprise/JackHighlight.png",
		"Assets/Buttons/Suprise/JackClicked.png", 0);
}

void Draw_TempText(float dt) {
	if (waveFlag) {
		waveState += (dt * 2);
		printf("DT: %f\n", waveState);
		CP_Graphics_DrawRect(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50, 50);
		NewWaveButton.alive = 1;
		Button_Behavior(&NewWaveButton);
		if (NewWaveButton.isClicked)
		{
			Reward_Click(&currentMoney);
		}

		if (waveState > 4 && (NewWaveButton.alive==1)) {
			waveFlag = 0; waveState = 0;
			NewWaveButton.alive = 0;
			
		}
	}
}
void Del_TempText() {
	Button_Free(&NewWaveButton);
}

void Print_BulletInfo(GameEntity* entity) {
	for (size_t i = 0; i < playerArr.used; ++i) {

		for (size_t i = 0; i < entity->bullets.used; i++) {
			Bullet* b = &entity->bullets.bulletArr[i];
			printf("  Bullet %d at (%.1f, %.1f)\n", b->id, b->centerPos.x, b->centerPos.y);
		}
	}
}

void Draw_Bullets() {
	for (size_t i = 0; i < playerArr.used; ++i) {
		GameEntity* p = &playerArr.ActiveEntityArr[i].unit;
		for (int j = 0; j < p->bullets.used; j++)
		{
			Bullet* pew = &p->bullets.bulletArr[j];

			if (pew->opacity == 255)
			{
				if (pew->type == "poison") { 
					pew->color.red = 255; pew->color.green = 0; pew->color.blue = 255; pew->color.opacity = 255; }
				//printf("%s\n", pew->type);
				CP_Settings_Fill(CP_Color_Create(pew->color.red, pew->color.green, pew->color.blue, pew->opacity));
				CP_Graphics_DrawCircle(pew->centerPos.x, pew->centerPos.y, pew->diameter);
			}
		}
	}
}

void Draw_Entities() {
	float dt = CP_System_GetDt();
	

	CP_Vector lightDir = CP_Vector_Set(1.0f, -1.0f); // direction light comes *from*
	float lightHeight = 1.5f;
	

	/* players draw */
	for (size_t i = 0; i < playerArr.used; ++i) {
		ActiveEntity* ent = &playerArr.ActiveEntityArr[i];
		FSM_Update(&ent->fsm, &ent->unit, dt);

		GameEntity* p = &ent->unit;
		// --- SHADOW COMPUTATION ---
		CP_Vector shadowOffset = CP_Vector_Scale(lightDir, -50);
		CP_Vector shadowPos = CP_Vector_Add(p->centerPos, shadowOffset);
		float shadowScaleY = 0.5f;  // flatten vertically

		// --- DRAW SHADOW ---
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100)); // semi-transparent black
		// simulate flattening by using ellipse
		CP_Graphics_DrawEllipse(shadowPos.x, shadowPos.y, p->diameter, p->diameter * shadowScaleY);

		if (p->label == "poison") { p->color.red = 255; p->color.green = 0; p->color.blue = 255; p->color.opacity = 255; }
		if (p->label == "fire") { p->color.red = 255; p->color.green = 0; p->color.blue = 0;   p->color.opacity = 255; }

		if (p->isSel) { p->color.red = 0; p->color.green = 0; p->color.blue = 255; p->color.opacity = 255; }

		CP_Settings_Fill(CP_Color_Create(p->color.red, p->color.green, p->color.blue, p->color.opacity));
		CP_Graphics_DrawCircle(p->centerPos.x, p->centerPos.y, p->diameter);

	}

	if (enemyArr.used <= 0) {

		Init_NewWave(wave++);

	}
	for (size_t i = 0; i < enemyArr.used; ++i) {
		ActiveEntity* ent = &enemyArr.ActiveEntityArr[i];

		Move_Wave(&ent->unit, dt);
		FSM_Update(&ent->fsm, &ent->unit, dt);
		if (enemyArr.ActiveEntityArr[i].health <= 0.f) {
			Arr_Del(&enemyArr, enemyArr.ActiveEntityArr[i].id);
			continue;
		}
		GameEntity* e = &ent->unit;
		//if (e->isSel) { e->color.red = 255; e->color.green = 255; e->color.blue = 255; e->color.opacity = 255; }

		CP_Settings_Fill(CP_Color_Create(e->color.red, e->color.green, e->color.blue, e->color.opacity));
		CP_Graphics_DrawCircle(e->centerPos.x, e->centerPos.y, e->diameter);



		Health_DrawEnemyBar(ent, 80.0f, 10.0f, 20.0f);
	}

	Draw_Bullets();

	
}