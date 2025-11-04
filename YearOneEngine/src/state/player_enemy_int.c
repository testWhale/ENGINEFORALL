#include "player_enemy_int.h"
#include "utils/utils.h"
#include "tile/tile.h"
#include "utils/SM.h"
#include "utils/arr.h"
int coun = 0;

int checkForSel() {
	int count2 = 0;
	for (int i = 0; i < MAX_ENTITIES; i++) {
		ActiveEntity entity = newArr.ActiveEntityArr[i];
		printf("ID: %d		ISSEL: %d\n", entity.id, entity.unit->isSel);
		if (entity.unit->isSel) {
			count2 += 1; if (count2 > 1) {return 1;}
		}
	}
	return 0;
}
void deselectEnt() {
	printf("HUH");
	if (checkForSel()) {
		printf("CHECK");
		for (int j = 0; j < MAX_ENTITIES; j++) {
			ActiveEntity entity2 = newArr.ActiveEntityArr[j];
			entity2.unit->color = GREEN;
			entity2.unit->isSel = 0;
		}
	}
} 

/*---------------------------------IDLE CODE-----------------------------*/
void PlayerIdle_Init(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("Player entered IDLE::INIT state\n");
	entity->color.red = 100;
	entity->color.green = 100;
	entity->color.blue = 255;
	entity->stateTimer = 0.0f;

}
void PlayerIdle_Update(GameEntity* entity, StateMachine* SM, float dt) {
	entity->stateTimer += dt;
	////printf("UPDATE");
	// Example: Transition to Attack if "attack" input detected
	// In real game, check input here
	if (CP_Input_KeyDown(KEY_P)) {
		//printf("STARTED ATTACK STATE FROM UPDATE\n");
		FSM_SetState(SM, PickUpState, entity, dt);
		return;
	}
	if (IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		printf("STARTED ATTACK STATE FROM IDLE\n");
		deselectEnt();
		FSM_SetState(SM, PickUpState, entity, dt);
		return;
	}
}
void PlayerIdle_Exit(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("LEAVING IDLE state\n");
}

/*---------------------------------PickUp Functions-----------------------------*/
void PickedUp_Init(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("Player entered Attck state\n");
	if (1 == entity->isItOnMap) { //isItOnMap is set in tile.c
		FSM_SetState(SM, SelectedState, entity, dt);

	} else {
		entity->color.red = 0;
		entity->color.green = 255;
		entity->color.blue = 0;
		entity->stateTimer = 0.0f;
	}
}
void PickedUp_Update(GameEntity* entity, StateMachine* SM, float dt) {
	/*//printf("UPDATING\n");*/
	entity->stateTimer += dt;
	entity->centerPos = (CP_Vector){ CP_Input_GetMouseX(), CP_Input_GetMouseY() };
	hoverTileAt(entity, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() });

	if (IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		setOnTile(entity, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() });
		FSM_SetState(SM, IdleState, entity, dt);
		return;
	}
}
void PickedUp_Exit(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("Player left IDLE state\n");
	hoverTileExit();
}

/*---------------------------------SELECT FUNCTION-----------------------------*/
void Sel_Init(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("Player entered Attck state\n");
	printf("NOW selecting..\n");
	hoverTileExit();
	SelAfterPlaced(entity, entity->centerPos);
	entity->stateTimer = 0.0f;
	entity->color.red = 0;
	entity->color.green = 0;
	entity->color.blue = 255;
	entity->isSel = 1;
}
void Sel_Update(GameEntity* entity, StateMachine* SM, float dt) {
	/*//printf("UPDATING\n");*/
	entity->stateTimer += dt;
	//printf("WE ARE SELECTION\n");
	if (IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		printf("PROBLEM\n");
		hoverTileExit();
		deselectEnt();
		entity->isSel = 0;
		FSM_SetState(SM, IdleState, entity, dt);
		return;
	}
}

void Sel_Exit(GameEntity* entity, StateMachine* SM, float dt) {
	printf("BYE SELECTION\n");
	entity->isSel = 0;
	
	hoverTileExit();
}

/*---------------------------------States Assigning-----------------------------*/
States IdleState = {
	PlayerIdle_Init,
	PlayerIdle_Update,
	PlayerIdle_Exit
};

States PickUpState = {
	PickedUp_Init,
	PickedUp_Update,
	PickedUp_Exit
};

States SelectedState = {
	Sel_Init,
	Sel_Update,
	Sel_Exit
};
