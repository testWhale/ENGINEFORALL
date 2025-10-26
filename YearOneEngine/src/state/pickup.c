#include "pickup.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "utils/container.h"
#include "tile/tile.h"

int coun = 0;

int checkForSel() {
	int count2 = 0;
	for (int i = 0; i < MAX_ENTITIES; i++) {
		ActiveEntity entity = playerArr.ActiveEntityArr[i];
		printf("ID: %d		ISSEL: %d\n", entity.unit->id, entity.unit->isSel);
		if (entity.unit->isSel) {
			return 1;
		}
	}
	return 0;
}
void deselectEnt() {
		for (int j = 0; j < MAX_ENTITIES; j++) {
			ActiveEntity entity2 = playerArr.ActiveEntityArr[j];
			entity2.unit->color.red = 100;
			entity2.unit->color.green = 0;
			entity2.unit->color.blue = 0;
			entity2.unit->isSel = 0;
		}
} 

/*---------------------------------IDLE CODE-----------------------------*/
void Idle_Init(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("Player entered IDLE::INIT state\n");
	entity->color.red = 100;
	entity->color.green = 100;
	entity->color.blue = 255;
	entity->stateTimer = 0.0f;

}
void Idle_Update(GameEntity* entity, StateMachine* SM, float dt) {
	entity->stateTimer += dt;
	// Example: Transition to Attack if "attack" input detected
	// In real game, check input here
	if (CP_Input_KeyDown(KEY_P)) {
		FSM_SetState(SM, PickUpState, entity, dt);
		return;
	}
	if (IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		//printf("STARTED ATTACK STATE FROM IDLE\n");
		/*deselectEnt();*/
		FSM_SetState(SM, PickUpState, entity, dt);
		return;
	}
}
void Idle_Exit(GameEntity* entity, StateMachine* SM, float dt) {
	//printf("LEAVING IDLE state\n");
}

/*---------------------------------PickUp Functions-----------------------------*/
void PickedUp_Init(GameEntity* entity, StateMachine* SM, float dt) {

	if (1 == entity->isItOnMap) { //When it is onMap -> SelectedState
		FSM_SetState(SM, SelectedState, entity, dt);

	} else {
		entity->color.red = 0;
		entity->color.green = 0;
		entity->color.blue = 255;
		entity->stateTimer = 0.0f;
		entity->isSel = 1;
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
	entity->isSel = 0;
	hoverTileExit();
}

/*---------------------------------SELECT FUNCTION-----------------------------*/
void Sel_Init(GameEntity* entity, StateMachine* SM, float dt) {
	hoverTileExit();
	//SelAfterPlaced(entity, entity->centerPos); //Select Function

	entity->stateTimer = 0.0f;

	if (checkForSel()) { //check if other unit has been selected. Before Setting New isSel
		deselectEnt();
	};
	entity->isSel = 1;
	checkForSel();
	
}
void Sel_Update(GameEntity* entity, StateMachine* SM, float dt) {
	entity->stateTimer += dt;
	hoverTileAt(entity, (CP_Vector) { entity->centerPos.x, entity->centerPos.y });
	Container_Draw( getContainer(entity->label, &containersArr) );
	if (0==entity->isSel || IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		FSM_SetState(SM, IdleState, entity, dt);
		return;
	}
}

void Sel_Exit(GameEntity* entity, StateMachine* SM, float dt) {
	printf("BYE SELECTION\n");
	entity->isSel = 0;
	checkForSel();
	hoverTileExit();
}

/*---------------------------------States Assigning-----------------------------*/
States IdleState = {
	Idle_Init,
	Idle_Update,
	Idle_Exit
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
