#include "pickup.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "utils/container.h"
#include "tile/tile.h"
#include "shoot.h"
int coun = 0;

int checkForSel() {
	int count2 = 0;
	for (int i = 0; i < playerArr.used; i++) {
		ActiveEntity entity = playerArr.ActiveEntityArr[i];
		printf("ID: %d		ISSEL: %d\n", entity.id, entity.unit.isSel);
		if (entity.unit.isSel) {
			printf("YES\n");
			return 1;
		}
	}
	return 0;
}
void deselectEnt() {
		for (int j = 0; j < MAX_ENTITIES; j++) {
			ActiveEntity* entity2 = &playerArr.ActiveEntityArr[j];
			entity2->unit.color.red = 100;
			entity2->unit.color.green = 0;
			entity2->unit.color.blue = 0;
			entity2->unit.isSel = 0;
		}
} 

/*---------------------------------IDLE CODE-----------------------------*/
void Idle_Init(GameEntity* entity, StateMachine* sm, float dt) {
	//printf("Player entered IDLE::INIT state\n");
	entity->color.red = 100;
	entity->color.green = 100;
	entity->color.blue = 255;
	entity->stateTimer = 0.0f;

}
void Idle_Update(GameEntity* entity, StateMachine* sm, float dt) {
	entity->stateTimer += dt;
	// Example: Transition to Attack if "attack" input detected
	// In real game, check input here
	if (entity->isItOnMap==1) {
		FSM_SetState(sm, ShootState, entity, dt);
		return;
	}
	if (IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		//printf("STARTED ATTACK STATE FROM IDLE\n");
		/*deselectEnt();*/
		FSM_SetState(sm, PickUpState, entity, dt);
		return;
	}
}
void Idle_Exit(GameEntity* entity, StateMachine* sm, float dt) {
	//printf("LEAVING IDLE state\n");
}

/*---------------------------------PickUp Functions-----------------------------*/
void PickedUp_Init(GameEntity* entity, StateMachine* sm, float dt) {

	if (1 == entity->isItOnMap) { //When it is onMap -> SelectedState
		FSM_SetState(sm, SelectedState, entity, dt);

	} else {
		entity->color.red = 0;
		entity->color.green = 0;
		entity->color.blue = 255;
		entity->stateTimer = 0.0f;
		entity->isSel = 1;
	}
}
void PickedUp_Update(GameEntity* entity, StateMachine* sm, float dt) {
	/*//printf("UPDATING\n");*/
	entity->stateTimer += dt;
	entity->centerPos = (CP_Vector){ CP_Input_GetMouseX(), CP_Input_GetMouseY() };
	hoverTileAt(entity, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() });

	if (IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		setOnTile(entity, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() });
		FSM_SetState(sm, IdleState, entity, dt);
		return;
	}
}
void PickedUp_Exit(GameEntity* entity, StateMachine* sm, float dt) {
	//printf("Player left IDLE state\n");
	B_Arr_Refresh(&(entity->bullets.bulletArr), entity);
	entity->isSel = 0;
	entity->sound.soundPlace = CP_Sound_Load("./Assets/soundeffect/meow.wav");
	if (entity->sound.soundPlace == NULL) {
		printf("HELP");
	} 
	hoverTileExit(); 
}

/*---------------------------------SELECT FUNCTION-----------------------------*/
void Sel_Init(GameEntity* entity, StateMachine* sm, float dt) {
	hoverTileExit();
	//SelAfterPlaced(entity, entity->centerPos); //Select Function

	entity->stateTimer = 0.0f;
	CP_Sound_Play(entity->sound.soundPlace);

	if (checkForSel()) { //check if other unit has been selected. Before Setting New isSel
		deselectEnt();
	};
	entity->isSel = 1;
	
}
void Sel_Update(GameEntity* entity, StateMachine* sm, float dt) {
	hoverTileAt(entity, (CP_Vector) { entity->centerPos.x, entity->centerPos.y });
	//Container_Draw( getContainer(entity->label, &containersArr) );
	if (0==entity->isSel || IsCircleClicked(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		FSM_SetState(sm, IdleState, entity, dt);
		return;
	}
	Shoot_Update(entity, sm, dt);
}

void Sel_Exit(GameEntity* entity, StateMachine* sm, float dt) {
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
