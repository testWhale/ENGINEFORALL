
#include "enemy.h"
#include "tile/tile.h"
#include "utils/utils.h"
#include "utils/arr.h"
#include "./utils/SM.h"
/*---------------------------------IDLE CODE-----------------------------*/
void Enemy_IdleInit(GameEntity* entity, StateMachine* sm, float dt) {
	//printf("Player entered IDLE::INIT state\n");
	entity->color.red = 255;
	entity->color.green = 255;
	entity->color.blue = 0;
	entity->stateTimer = 0.0f;

}
void Enemy_IdleUpdate(GameEntity* entity, StateMachine* sm, float dt) {
	entity->stateTimer += dt;

	// Example: Transition to Attack if "attack" input detected
	//if (Is_Mouse_Released(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
	//	//printf("STARTED ATTACK STATE FROM IDLE\n");
	//	/*deselectEnt();*/
	//	FSM_SetState(sm, Enemy_PickUpState, entity, dt);
	//	return;
	//}
}
void Enemy_IdleExit(GameEntity* entity, StateMachine* sm, float dt) {
	//printf("LEAVING IDLE state\n");
}

/*---------------------------------PickUp Functions-----------------------------*/
void Enemy_PickedUpInit(GameEntity* entity, StateMachine* sm, float dt) {

	//if (1 == entity->isItOnMap) { //When it is onMap -> SelectedState
	//	//FSM_SetState(sm, EnemySelectedState, entity, dt);

	//}
	//else {
	//	entity->color.red = 0;
	//	entity->color.green = 0;
	//	entity->color.blue = 255;
	//	entity->stateTimer = 0.0f;
	//	entity->isSel = 1;
	//}
}
void Enemy_PickedUpUpdate(GameEntity* entity, StateMachine* sm, float dt) {
	
	/*entity->stateTimer += dt;
	entity->centerPos = (CP_Vector){ CP_Input_GetMouseX(), CP_Input_GetMouseY() };
	Hover_TileAt(entity, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() });
	if (Is_Mouse_Released(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		Set_OnTile(entity, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() });
		FSM_SetState(sm, EnemyIdleState, entity, dt);
		return;
	}*/
}
void Enemy_PickedUpExit(GameEntity* entity, StateMachine* sm, float dt) {
	////printf("Player left IDLE state\n"); 
	//entity->isSel = 0;
	//entity->sound.soundPlace = CP_Sound_Load("./Assets/soundeffect/meow.wav");
	//if (entity->sound.soundPlace == NULL) {
	//	printf("HELP");
	//}
	//Hover_Tile_Exit();
}

/*---------------------------------SELECT FUNCTION-----------------------------*/
void Enemy_SelInit(GameEntity* entity, StateMachine* sm, float dt) {
	Hover_Tile_Exit();
	//Sel_AfterPlaced(entity, entity->centerPos); //Select Function

	entity->stateTimer = 0.0f;
	CP_Sound_Play(entity->sound.soundPlace);

	if (Check_ForSel()) { //check if other unit has been selected. Before Setting New isSel
		deselectEnt();
	};
	entity->isSel = 1;

}
void Enemy_SelUpdate(GameEntity* entity, StateMachine* sm, float dt) {
	entity->stateTimer += dt;
	Hover_TileAt(entity, (CP_Vector) { entity->centerPos.x, entity->centerPos.y });
	//Container_Draw( getContainer(entity->label, &containersArr) );
	if (0 == entity->isSel || Is_Mouse_Released(entity->centerPos.x, entity->centerPos.y, entity->diameter, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		FSM_SetState(sm, EnemyIdleState, entity, dt);
		return;
	}
}

void Enemy_SelExit(GameEntity* entity, StateMachine* sm, float dt) {
	printf("BYE SELECTION\n");
	entity->isSel = 0;
	Check_ForSel();
	Hover_Tile_Exit();
}

/*---------------------------------States Assigning-----------------------------*/
States EnemyIdleState = {
	Enemy_IdleInit,
	Enemy_IdleUpdate,
	Enemy_IdleExit
};


States EnemyPickUpState = {
	Enemy_PickedUpInit,
	Enemy_PickedUpUpdate,
	Enemy_PickedUpExit
};

States EnemySelectedState = {
	Enemy_SelInit,
	Enemy_SelUpdate,
	Enemy_SelExit
};
