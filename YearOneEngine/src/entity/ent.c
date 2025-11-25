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
#include "utils/mouse/mouse.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

ButtonInfo NewWaveButton;
ButtonInfo NewWave2Button;
ButtonSound defaultSound;
static float s_tipTimer = 0.0f;
static int   s_lastWaveSeen = -1;
static char  s_tipMsg[96] = "";

//CP_Image baseTex;
//CP_Image normalTex;
//CP_Color* basePixels;
//CP_Color* normalPixels;
//CP_Color* outPixels;
//CP_Image imgOut;
/* Template Value */
GameEntity Make_Template(const char* name) {
	GameEntity e; char* spritePath = "Assets/Cats/n.png"; char* shadowPath = "Assets/Cats/n_s.png";
	if (name == "player")
	{
		spritePath = "Assets/Cats/n.png";
		shadowPath = "Assets/Cats/n_s.png";
		e = (GameEntity){
		.centerPos = {400, 100}, .rotation = 0, .isPlayer = 1, .forwardVector = {0, 0}, .color = {255,0,0,255},
		.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "fire", .bullets = {0 }, .pickUpRemoval = 0};
	}


	if (name == "poison")
	{
		Bullet temp = Bullet_Template("poison");
		spritePath = "Assets/Cats/p.png";
		shadowPath = "Assets/Cats/n_s.png";
		e = (GameEntity){
		.centerPos = {400, 150}, .rotation = 0, .isPlayer = 1, .forwardVector = {0, 0}, .color = {255,0,255,255},
		.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "poison" , .bullets = {0}, .sprite = "Assets/Cats/p.png"};
		//B_Arr_Insert(&e.bullets, temp);

	}

	if (name == "stun")
	{
		Bullet temp = Bullet_Template("stun");
		spritePath = "Assets/Cats/e.png";
		shadowPath = "Assets/Cats/n_s.png";
		e = (GameEntity){
		.centerPos = {500, 100}, .rotation = 0, .isPlayer = 1, .forwardVector = {0, 0}, .color = {0,0,255,255},
		.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "stun" , .bullets = {0} };

	}


	if (name == "enemy")
	{
		e = (GameEntity){
		.centerPos = {100, 400}, .rotation = 0, .isPlayer = 0, .forwardVector = {0, 0}, .color = {255,255,0,255},
		.diameter = 100, .stateTimer = 0, .isItOnMap = 0, .isSel = 0, .label = "enemy" , .bullets = {0} };

	}
	e.sprite = CP_Image_Load(spritePath);
	e.shadow = CP_Image_Load(shadowPath);
	return e;
}

/*LOADS IN PLAYER & ENEMY ARRAY */
void Init_PlayerDemo() {

	GameEntity player = Make_Template("player");
	GameEntity enemy = Make_Template("enemy");

	/* Template Value * /
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
		//printf("turrent ID: %d", ae.id);

		Arr_Insert(&playerArr, ae);
		playerArr.ActiveEntityArr[i].unit.centerPos.x = player.centerPos.x + i * 100.0f;

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
		if (enemyArr.ActiveEntityArr[i].unit.accel.x > -0.5) {
			enemyArr.ActiveEntityArr[i].maxHealth += 35 * -enemyArr.ActiveEntityArr[i].unit.accel.x;
			printf("THis enemy has more health %f\n", enemyArr.ActiveEntityArr[i].health);
		}

	}
	//ContArr_Init(playerArr.used, &containersArr);
	//Read_File("Assets/containers");
}

void Init_NewWave(int currWave) {
	GameEntity enemy = Make_Template("enemy");
	/* FOR ENEMY UNITS */
	waveFlag = 1;
	// every new wave add 5 units, we start with 5 units
	int spawn = currWave + 5;
	if (spawn > MAX_ENTITIES) { spawn = MAX_ENTITIES; }
	for (int i = 0; i < spawn; i++) {
		ActiveEntity ae;
		ae.id = i;
		ae.unit = enemy;
		ae.fsm = (StateMachine){ .currState = EnemyIdleState };
		/* Difficulty Curving */
		ae.maxHealth = 100 + pow(currWave, 3);
		ae.health = 100 + pow(currWave, 3);
		printf("health %f\n", enemyArr.ActiveEntityArr[i].health);
		ae.alive = 1;
		ae.hasScored = 0;
		ae.lastLeftmostX = 0.0f;
		ae.isHitting = 0;
		ae.contactTime = 0.0f;
		Arr_Insert(&enemyArr, ae);
		Start_Wave(&enemyArr.ActiveEntityArr[i].unit, (int)2);

		/* TANK CODE */
		/* this sets ur enemy health, if enemy is slower than -0.4 than it will be tankier */
		if (enemyArr.ActiveEntityArr[i].unit.accel.x > -0.1) {
			enemyArr.ActiveEntityArr[i].maxHealth += 1005 * -enemyArr.ActiveEntityArr[i].unit.accel.x;
			enemyArr.ActiveEntityArr[i].health += 1005 * -enemyArr.ActiveEntityArr[i].unit.accel.x;
			printf("Tank HP %f\n", enemyArr.ActiveEntityArr[i].health);
		}
	}
}

/* Completely Kills all active Enemies */
void Kill_NewWave() {
	{
		printf("test;");
		while(enemyArr.used > 0) {
			Arr_Del(&(enemyArr), enemyArr.ActiveEntityArr->id);
		}
	}
}

void Load_TempText() {
	Button_Load(&NewWave2Button, &defaultSound,
		96 * unit, 60 * unit,
		143 * unit, 60 * unit,
		0 * unit,
		"Assets/Buttons/Ribbon/RibbonW.png",
		"Assets/Buttons/Ribbon/RWHighlighted.png",
		"Assets/Buttons/Ribbon/RibbonW.png", 0);

	Button_Load(&NewWaveButton, &defaultSound,
		96 * unit, 92 * unit,
		20 * unit, 20 * unit,
		0 * unit,
		"Assets/Buttons/Suprise/JackNormal.png",
		"Assets/Buttons/Suprise/JackHighlight.png",
		"Assets/Buttons/Suprise/JackClicked.png", 0);

	s_tipTimer = 0.0f;
	s_lastWaveSeen = -1;
	s_tipMsg[0] = '\0';
}

void Draw_TempText(float dt) {
	if (waveFlag) {
		waveState += (dt * 2);
		//printf("DT: %f\n", waveState);
		CP_Graphics_DrawRect(CP_Input_GetMouseX(), CP_Input_GetMouseY(), 50, 50);
		NewWaveButton.alive = 1; NewWave2Button.alive = 1;
		Button_Behavior(&NewWaveButton);
		if (NewWaveButton.isClicked)
		{
			Reward_Click(&currentMoney);
		}

		Button_Behavior(&NewWave2Button);
		{
			Reward_Click(&currentMoney);
		}

		if (waveState > 4 && (NewWaveButton.alive == 1)) {
			waveFlag = 0; waveState = 0;
			NewWaveButton.alive = 0;
			NewWave2Button.alive = 0;
		}
	}
	if (wave != s_lastWaveSeen) {
		s_tipMsg[0] = '\0';
		s_tipTimer = 0.0f;

		switch (wave) {
		case 5:
			snprintf(s_tipMsg, sizeof s_tipMsg, "Maybe consider buying a nuke.");
			s_tipTimer = 3.0f;
			break;
		case 10:
			snprintf(s_tipMsg, sizeof s_tipMsg, "You should really consider buying one.");
			s_tipTimer = 3.0f;
			break;
		case 15:
			snprintf(s_tipMsg, sizeof s_tipMsg, "Now you really should buy one!");
			s_tipTimer = 3.0f;
			break;
		default:
			break;
		}
		s_lastWaveSeen = wave;
	}

	if (s_tipTimer > 0.0f) {
		s_tipTimer -= dt;
		float t = (s_tipTimer > 0.4f) ? 1.0f : (s_tipTimer / 0.4f);
		if (t < 0.0f) t = 0.0f;

		const float cx = 0.5f * (float)CP_System_GetWindowWidth();
		const float cy = 18.0f * unit;
		const float bw = 86.0f * unit;
		const float bh = 12.0f * unit;

		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)(160 * t)));
		CP_Graphics_DrawRect(cx, cy, bw, bh);

		CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
		CP_Settings_TextSize(5.0f * unit);
		CP_Settings_Fill(CP_Color_Create(255, 255, 255, (int)(255 * t)));
		CP_Font_DrawText(s_tipMsg, cx, cy);
	}
}
void Del_TempText() {
	Button_Free(&NewWaveButton);
	Button_Free(&NewWave2Button);
}

/* Mouse Refresh after Loop */
// Compare function for qsort descending
int compare_desc(const void* a, const void* b) {
	return (*(int*)b - *(int*)a);
}

void LateUpdate_Pickups()
{
	int removedIndices[64]; // adjust max pickups if needed
	int removedCount = 0;

	// PASS 1 — find all removed items
	for (int i = 0; i < playerArr.used; i++)
	{
		GameEntity* e = &playerArr.ActiveEntityArr[i].unit;

		if (e->pickUpRemoval == 1)
		{
			printf("\nREMOVING %d\n", e->pickUpIndex);
			removedIndices[removedCount++] = e->pickUpIndex;

			e->pickUpIndex = 0;
			e->pickUpRemoval = 0;
			
		}
	}

	if (removedCount == 0)
		return;

	// Sort removed indices descending
	qsort(removedIndices, removedCount, sizeof(int), compare_desc);

	// PASS 2 — shift remaining items down
	for (int r = 0; r < removedCount; r++)
	{
		int removedIndex = removedIndices[r];

		for (int i = 0; i < playerArr.used; i++)
		{
			GameEntity* e = &playerArr.ActiveEntityArr[i].unit;

			if (e->pickUpIndex > removedIndex)
			{
				e->pickUpIndex--;
			}
		}
	}
	Mouse_DelPickup();
}


float rotation = 0.f;
void Draw_Bullets() {
	for (size_t i = 0; i < playerArr.used; ++i) {
		ActiveEntity* ent = &playerArr.ActiveEntityArr[i];
		if (!ent->alive)
		{
			ent->unit.bullets.used = 0;  
			continue;
		}
		GameEntity* p = &playerArr.ActiveEntityArr[i].unit;
		for (int j = 0; j < p->bullets.used; j++)
		{
			Bullet* pew = &p->bullets.bulletArr[j];
			
			if (pew->opacity == 255)
			{
				if (pew->type == "poison") { 
					pew->color.red = 255; pew->color.green = 0; pew->color.blue = 255; pew->color.opacity = 255; }
				
				CP_Settings_Fill(CP_Color_Create(pew->color.red, pew->color.green, pew->color.blue, pew->opacity));
				CP_Graphics_DrawCircle(pew->centerPos.x, pew->centerPos.y, pew->diameter);
				if (rotation >= 360) {
					rotation = 0;
				}

				CP_Image_DrawAdvanced(pew->yarn, pew->centerPos.x, pew->centerPos.y, pew->diameter, pew->diameter, 255, rotation);
				rotation += 10;
			}
		}
	}
}

float newDT=0;
void Draw_Entities(void)
{
	float dt = CP_System_GetDt();

	
	CP_Settings_NoStroke();

	if (!Pause_IsPaused())
	{
		for (size_t i = 0; i < playerArr.used; ++i)
		{
			ActiveEntity* ent = &playerArr.ActiveEntityArr[i];
			if (!ent->alive)
			{
				continue; }
				

			FSM_Update(&ent->fsm, &ent->unit, dt);
			Mouse_Update();
		}
		newDT += dt;
		if (enemyArr.used <= 0 && newDT > 6)
		{	
			newDT = 0;
			Init_NewWave(wave++);
		}

		/* -------ENEMIES -------*/
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
				if (ent->unit.isStunned) {
					ent->unit.stunTimer -= dt;

					if (ent->unit.stunTimer <= 0) {
						ent->unit.isStunned = 0;
						ent->unit.stunTimer = 0;
					}
				}
				else {
					Move_Wave(&ent->unit, dt);
				}
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
		CP_Image_Draw(p->shadow, shadowPos.x, shadowPos.y,
			p->diameter,
			p->diameter * shadowScaleY, 100);

		if (p->label == "poison") { p->color.red = 255; p->color.green = 0;   p->color.blue = 255; p->color.opacity = 100; }
		if (p->label == "fire") { p->color.red = 255; p->color.green = 0;   p->color.blue = 0;   p->color.opacity = 100; }
		if (p->isSel) { p->color.red = 0;   p->color.green = 0;   p->color.blue = 255; p->color.opacity = 100; }

		//CP_Settings_Fill(CP_Color_Create(p->color.red, p->color.green, p->color.blue, p->color.opacity));
		//CP_Graphics_DrawCircle(p->centerPos.x, p->centerPos.y, p->diameter);
		CP_Image_Draw(p->sprite, p->centerPos.x, p->centerPos.y, p->diameter, p->diameter, 255);
		
		if (p->pickUpIndex > 0) 
		{
			char str[2];
			CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
			CP_Settings_TextSize(5 * unit);
			
			sprintf_s(str, sizeof(str), "%d", p->pickUpIndex);

			CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
			CP_Font_DrawText(str, p->centerPos.x, p->centerPos.y);
			
		}

	}

	for (size_t i = 0; i < enemyArr.used; ++i)
	{
		ActiveEntity* ent = &enemyArr.ActiveEntityArr[i];
		if (!ent->alive)
			continue;

		GameEntity* e = &ent->unit;

		//CP_Settings_Fill(CP_Color_Create(e->color.red, e->color.green, e->color.blue, e->color.opacity));
		//CP_Graphics_DrawCircle(e->centerPos.x, e->centerPos.y, e->diameter);
		CP_Settings_ImageMode(CP_POSITION_CENTER);
		CP_Image_Draw(e->sprite, e->centerPos.x, e->centerPos.y - (2.5 * unit), e->sWidth* e->scale * 0.1, e->sHeight* e->scale * 0.1, 255);
	}

	Draw_Bullets();
	
	for (size_t i = 0; i < enemyArr.used; ++i)
	{
		ActiveEntity* ent = &enemyArr.ActiveEntityArr[i];
		if (!ent->alive) continue;

		GameEntity* e = &ent->unit;

		HealthSystem hs = { 0 };
		hs.maxhealth = (float)ent->maxHealth;
		hs.health = (float)ent->health;

		float barW = e->diameter * 0.90f;
		float barH = e->diameter * 0.11f;
		float barX = e->centerPos.x - barW * 0.5f;
		float barY = e->centerPos.y - e->diameter * 0.65f;

		HealthSystem_DrawBar(&hs, barX, barY, barW, barH);
	}

	for (size_t i = 0; i < playerArr.used; ++i)
	{
		ActiveEntity* ent = &playerArr.ActiveEntityArr[i];
		if (!ent->alive) continue;

		GameEntity* p = &ent->unit;

		HealthSystem hs = { 0 };
		hs.maxhealth = (float)ent->maxHealth;
		hs.health = (float)ent->health;

		float barW = p->diameter * 0.90f;
		float barH = p->diameter * 0.11f;
		float barX = p->centerPos.x - barW * 0.5f;
		float barY = p->centerPos.y - p->diameter * 0.65f;

		HealthSystem_DrawBar(&hs, barX, barY, barW, barH);
	}
}


/* Config / tuning */
const float CELL_THRESH_1 = 0.20f;   /* deep shadow threshold */
const float CELL_THRESH_2 = 0.45f;   /* shadow threshold */
const float CELL_THRESH_3 = 0.75f;   /* light threshold */

const float SHADE_1 = 0.20f; /* deep shadow */
const float SHADE_2 = 0.45f; /* shadow */
const float SHADE_3 = 0.75f; /* light */
const float SHADE_4 = 1.00f; /* highlight */

const float AMBIENT_TINT = 0.08f;    /* tiny ambient added after quantize */
const float FIXED_LZ = 0.50f;        /* fixed Z component of light */

#define NUM_DIRS 16  /* precompute 16 directional textures */

/* Globals */
static CP_Image baseTex = NULL;      /* base sprite texture */
static CP_Image normalTex = NULL;    /* normal map texture */

static int texW = 0;                 /* texture width */
static int texH = 0;                 /* texture height */

static float* baseR = NULL;          /* base red channel (0..1) */
static float* baseG = NULL;          /* base green channel (0..1) */
static float* baseB = NULL;          /* base blue channel (0..1) */
static unsigned char* baseA = NULL;  /* base alpha channel (0..255) */

static float* nxArr = NULL;          /* normal X */
static float* nyArr = NULL;          /* normal Y */
static float* nzArr = NULL;          /* normal Z */

static CP_Image* texDirs = NULL;     /* array of precomputed directional textures */

/* Helpers */
static inline float clampf01(float v) {
	/* clamp value to 0..1 */
	if (v < 0.0f) return 0.0f;
	if (v > 1.0f) return 1.0f;
	return v;
}

/* Setup */
void setup(const char* basePath, const char* normalPath) {
	/* load textures */
	baseTex = CP_Image_Load(basePath);
	normalTex = CP_Image_Load(normalPath);

	texW = CP_Image_GetWidth(baseTex);
	texH = CP_Image_GetHeight(baseTex);
	int totalPixels = texW * texH;

	/* temporary buffers for reading pixel data */
	CP_Color* tmpBase = malloc(sizeof(CP_Color) * totalPixels);
	CP_Color* tmpNormal = malloc(sizeof(CP_Color) * totalPixels);
	CP_Image_GetPixelData(baseTex, tmpBase);
	CP_Image_GetPixelData(normalTex, tmpNormal);

	/* allocate arrays */
	baseR = malloc(sizeof(float) * totalPixels);
	baseG = malloc(sizeof(float) * totalPixels);
	baseB = malloc(sizeof(float) * totalPixels);
	baseA = malloc(sizeof(unsigned char) * totalPixels);
	nxArr = malloc(sizeof(float) * totalPixels);
	nyArr = malloc(sizeof(float) * totalPixels);
	nzArr = malloc(sizeof(float) * totalPixels);

	/* fill arrays */
	for (int i = 0; i < totalPixels; ++i) {
		CP_Color bc = tmpBase[i];
		baseR[i] = bc.r / 255.0f;
		baseG[i] = bc.g / 255.0f;
		baseB[i] = bc.b / 255.0f;
		baseA[i] = bc.a;

		CP_Color nc = tmpNormal[i];
		nxArr[i] = (nc.r / 255.0f) * 2.0f - 1.0f;
		nyArr[i] = (nc.g / 255.0f) * 2.0f - 1.0f;
		nzArr[i] = (nc.b / 255.0f); /* 0..1 */
	}

	free(tmpBase);
	free(tmpNormal);

	/* allocate directional texture array */
	texDirs = malloc(sizeof(CP_Image) * NUM_DIRS);

	/* precompute directional textures */
	for (int d = 0; d < NUM_DIRS; ++d) {
		float angle = (float)d / NUM_DIRS * 2.0f * 3.14159265f;
		float Lx = cosf(angle);
		float Ly = sinf(angle);
		float Lz = FIXED_LZ;
		float invLen = 1.0f / sqrtf(Lx * Lx + Ly * Ly + Lz * Lz);
		Lx *= invLen; Ly *= invLen; Lz *= invLen;

		CP_Color* buf = malloc(sizeof(CP_Color) * totalPixels);

		for (int i = 0; i < totalPixels; ++i) {
			float dot = nxArr[i] * Lx + nyArr[i] * Ly + nzArr[i] * Lz;
			float shade;

			if (dot < CELL_THRESH_1) shade = SHADE_1;
			else if (dot < CELL_THRESH_2) shade = SHADE_2;
			else if (dot < CELL_THRESH_3) shade = SHADE_3;
			else shade = SHADE_4;

			shade = clampf01(shade + AMBIENT_TINT);

			buf[i] = CP_Color_Create(
				(int)(baseR[i] * shade * 255.0f),
				(int)(baseG[i] * shade * 255.0f),
				(int)(baseB[i] * shade * 255.0f),
				baseA[i]
			);
		}

		texDirs[d] = CP_Image_CreateFromData(texW, texH, (unsigned char*)buf);
		free(buf);
	}

	printf("CS_Setup: Precomputed %d directional textures (%dx%d)\n", NUM_DIRS, texW, texH);
}

/* Draw */
void draw(float worldX, float worldY, float drawW, float drawH, int alpha) {
	if (!texDirs) return;

	float mx = CP_Input_GetMouseX();
	float my = CP_Input_GetMouseY();

	float screenX = worldX * unit - drawW * unit * 0.5f;
	float screenY = worldY * unit - drawH * unit * 0.5f;
	float screenW = drawW * unit;
	float screenH = drawH * unit;

	float cx = screenX + screenW * 0.5f;
	float cy = screenY + screenH * 0.5f;

	/* compute angle from sprite center to mouse */
	float dx = mx - cx;
	float dy = my - cy;
	float angle = atan2f(dy, dx);
	if (angle < 0) angle += 2.0f * 3.14159265f;

	/* map angle to 0..NUM_DIRS */
	float fdir = angle / (2.0f * 3.14159265f) * NUM_DIRS;
	int index0 = (int)fdir % NUM_DIRS;
	int index1 = (index0 + 1) % NUM_DIRS;
	float blend = fdir - index0;

	/* draw first texture fully opaque */
	CP_Settings_Tint(CP_Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
	CP_Image_Draw(texDirs[index0], worldX * unit, worldY * unit, screenW, screenH, alpha);

	/* draw second texture fully opaque, weighted by blend using color only */
	CP_Settings_Tint(CP_Color_Create(blend, blend, blend, 1.0f));
	CP_Image_Draw(texDirs[index1], worldX * unit, worldY * unit, screenW, screenH, alpha);

	/* reset tint */
	CP_Settings_Tint(CP_Color_Create(1.0f, 1.0f, 1.0f, 1.0f));
}

/* Cleanup */
void cleanup(void) {
	/* free directional textures */
	for (int d = 0; d < NUM_DIRS; ++d) {
		if (texDirs[d]) { CP_Image_Free(texDirs[d]); texDirs[d] = NULL; }
	}
	free(texDirs); texDirs = NULL;

	/* free base textures */
	if (baseTex) { CP_Image_Free(baseTex); baseTex = NULL; }
	if (normalTex) { CP_Image_Free(normalTex); normalTex = NULL; }

	/* free arrays */
	if (baseR) { free(baseR); baseR = NULL; }
	if (baseG) { free(baseG); baseG = NULL; }
	if (baseB) { free(baseB); baseB = NULL; }
	if (baseA) { free(baseA); baseA = NULL; }

	if (nxArr) { free(nxArr); nxArr = NULL; }
	if (nyArr) { free(nyArr); nyArr = NULL; }
	if (nzArr) { free(nzArr); nzArr = NULL; }
}
