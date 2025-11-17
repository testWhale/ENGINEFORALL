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
#include <math.h>

ButtonInfo NewWaveButton;
ButtonSound defaultSound;

CP_Image baseTex;
CP_Image normalTex;
CP_Color* basePixels;
CP_Color* normalPixels;
CP_Color* outPixels;
CP_Image imgOut;
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
		ae.isHitting = 0;      
		ae.contactTime = 0.0f;
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
		ae.isHitting = 0;
		ae.contactTime = 0.0f;
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

void Draw_Entities(void)
{
	float dt = CP_System_GetDt();

	if (!Pause_IsPaused())
	{
		for (size_t i = 0; i < playerArr.used; ++i)
		{
			ActiveEntity* ent = &playerArr.ActiveEntityArr[i];
			if (!ent->alive)
				continue;

			FSM_Update(&ent->fsm, &ent->unit, dt);
		}

		if (enemyArr.used <= 0)
		{
			Init_NewWave(wave++);
		}

		/* ----------------- ENEMIES ----------------- */
		for (size_t i = 0; i < enemyArr.used; )
		{
			ActiveEntity* ent = &enemyArr.ActiveEntityArr[i];
			if (!ent->alive)
			{
				++i;
				continue;
			}
			if (!ent->isHitting)
			{
				Move_Wave(&ent->unit, dt);
			}

			FSM_Update(&ent->fsm, &ent->unit, dt);

			if (ent->health <= 0.0f)
			{
				Arr_Del(&enemyArr, ent->id);
				continue;      
			}

			++i;
		}
	}



	CP_Vector lightDir = CP_Vector_Set(1.0f, -1.0f);   
	float     shadowScaleY = 0.5f;

	for (size_t i = 0; i < playerArr.used; ++i)
	{
		ActiveEntity* ent = &playerArr.ActiveEntityArr[i];
		if (!ent->alive)
			continue;

		GameEntity* p = &ent->unit;
		CP_Vector shadowOffset = CP_Vector_Scale(lightDir, -50.0f);
		CP_Vector shadowPos = CP_Vector_Add(p->centerPos, shadowOffset);

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, 100));
		CP_Graphics_DrawEllipse(
			shadowPos.x, shadowPos.y,
			p->diameter,
			p->diameter * shadowScaleY);

		if (p->label == "poison") { p->color.red = 255; p->color.green = 0;   p->color.blue = 255; p->color.opacity = 255; }
		if (p->label == "fire") { p->color.red = 255; p->color.green = 0;   p->color.blue = 0;   p->color.opacity = 255; }
		if (p->isSel) { p->color.red = 0;   p->color.green = 0;   p->color.blue = 255; p->color.opacity = 255; }

		CP_Settings_Fill(CP_Color_Create(p->color.red, p->color.green, p->color.blue, p->color.opacity));
		CP_Graphics_DrawCircle(p->centerPos.x, p->centerPos.y, p->diameter);

		{
			HealthSystem hs = { 0 };
			hs.maxhealth = (float)ent->maxHealth;
			hs.health = (float)ent->health;

			const float barW = 80.0f;
			const float barH = 10.0f;
			const float barX = p->centerPos.x - barW * 0.5f;
			const float barY = p->centerPos.y - p->diameter * 0.65f;

			HealthSystem_DrawBar(&hs, barX, barY, barW, barH);
		}
	}

	for (size_t i = 0; i < enemyArr.used; ++i)
	{
		ActiveEntity* ent = &enemyArr.ActiveEntityArr[i];
		if (!ent->alive)
			continue;

		GameEntity* e = &ent->unit;

		CP_Settings_Fill(CP_Color_Create(e->color.red, e->color.green, e->color.blue, e->color.opacity));
		CP_Graphics_DrawCircle(e->centerPos.x, e->centerPos.y, e->diameter);

		{
			HealthSystem hs = { 0 };
			hs.maxhealth = (float)ent->maxHealth;
			hs.health = (float)ent->health;

			const float barW = 80.0f;
			const float barH = 10.0f;
			const float barX = e->centerPos.x - barW * 0.5f;
			const float barY = e->centerPos.y - e->diameter * 0.65f;

			HealthSystem_DrawBar(&hs, barX, barY, barW, barH);
		}
	}

	Draw_Bullets();
	
}

void setup(char* imgPath, char* normPath) {
	baseTex = CP_Image_Load(imgPath);
	if (baseTex == NULL) { printf("BRoke at test.\n"); }
	normalTex = CP_Image_Load(normPath);
	if (normalTex == NULL) { printf("BRoke at normal.\n"); }
	int w = CP_Image_GetWidth(baseTex);
	int h = CP_Image_GetHeight(baseTex);
	float lx = 500;
	float ly = 10;
	// Allocate pixel buffers (arrays with length: image width * height)
	basePixels = (CP_Color*)malloc(sizeof(CP_Color) * w * h); //basePixels = pointer to first byte of memory block of baseImg
	normalPixels = (CP_Color*)malloc(sizeof(CP_Color) * w * h);
	outPixels = (CP_Color*)malloc(sizeof(CP_Color) * w * h);

	/* Get an array of CP_Color variables from images */
	CP_Image_GetPixelData(baseTex, basePixels); // Stores every pixel inside of this block 
	CP_Image_GetPixelData(normalTex, normalPixels);
	

	//  Create output image from pixel buffer
	imgOut = CP_Image_CreateFromData(w, h, (unsigned char*)outPixels);

}

void draw(float x, float y, float wdth, float height, int alpha) {
	
	int w = CP_Image_GetWidth(baseTex);
	int h = CP_Image_GetHeight(baseTex);
	float lx = CP_Input_GetMouseX();
	float ly = CP_Input_GetMouseY();
	// Lighting per pixel 
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int i = y * w + x;

			CP_Color col = basePixels[i];
			CP_Color n = normalPixels[i];

			// Convert normal RGB -> [-1,1] for X/Y, 0..1 for Z
			float nx = (n.r / 255.0f) * 2.0f - 1.0f;
			float ny = (n.g / 255.0f) * 2.0f - 1.0f;
			float nz = (n.b / 255.0f);

			// Light direction (2D)
			float dx = lx - (400 - w / 2 + x);
			float dy = ly - (300 - h / 2 + y);
			float len = sqrtf(dx * dx + dy * dy);
			if (len < 0.0001f) len = 0.0001f;
			dx /= len;
			dy /= len;

			// Diffuse lighting
			float diffuse = nx * dx + ny * dy + nz * 0.5f;
			if (diffuse < 0) diffuse = 0;

			// Apply diffuse to color
			int r = (int)(col.r * diffuse + 0.5f);
			int g = (int)(col.g * diffuse + 0.5f);
			int b = (int)(col.b * diffuse + 0.5f);

			outPixels[i] = CP_Color_Create(r, g, b, col.a);
		}
	}

	// Update the output image pixels
	CP_Image_UpdatePixelData(imgOut, outPixels);

	CP_Image_Draw(imgOut, x * unit, y * unit, wdth * unit, height * unit, alpha);


}


void clean() {
	//  Free memory
	free(basePixels);
	free(normalPixels);
	free(outPixels);

	// Optional: free output image if not reused
	CP_Image_Free(baseTex);
	CP_Image_Free(normalTex);
	CP_Image_Free(imgOut);
}

