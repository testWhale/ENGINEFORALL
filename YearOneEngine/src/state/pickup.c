#include "pickup.h"
#include "utils/utils.h"
#include "tile/tile.h"

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
		//printf("STARTED ATTACK STATE FROM UPDATE\n");
		FSM_SetState(SM, PickUpState, entity, dt);
		return;
	}
}

void PlayerIdle_Exit(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("LEAVING IDLE state\n");
}


void PickedUp_Init(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("Player entered Attck state\n");
	if (1 == entity->isItActive) {
		FSM_SetState(SM, SelectedState, entity, dt);
	}
	entity->color.red = 255;
	entity->color.green = 255;
	entity->color.blue = 255;
	entity->stateTimer = 0.0f;
}

void PickedUp_Update(GameEntity* entity, StateMachine* SM, float dt) {
	/*//printf("UPDATING\n");*/
	entity->stateTimer += dt;
	entity->centerPos = (CP_Vector){ CP_Input_GetMouseX(), CP_Input_GetMouseY() };
	hoverTileAt(entity, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() });

	if (IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		getTileAt(entity, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() });
		FSM_SetState(SM, IdleState, entity, dt);
		return;
	}
}

void PickedUp_Exit(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("Player left IDLE state\n");
	hoverTileExit();
}

void Sel_Init(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("Player entered Attck state\n");
	printf("NOW selecting..\n");
	hoverTileExit();
	entity->stateTimer = 0.0f;
}

void Sel_Update(GameEntity* entity, StateMachine* SM, float dt) {
	/*//printf("UPDATING\n");*/
	entity->stateTimer += dt;
	//printf("WE ARE SELECTION\n");
	hoverTileAt(entity, (CP_Vector) { entity->centerPos.x, entity->centerPos.y });

	if (IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		hoverTileExit();
		FSM_SetState(SM, IdleState, entity, dt);
		return;
	}
}

void Sel_Exit(GameEntity* entity, StateMachine* SM, float dt) {
	printf("BYE SELECTION\n");
	hoverTileExit();
}

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
