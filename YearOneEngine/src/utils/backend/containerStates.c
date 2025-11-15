#include "containerStates.h"
#include "utils/utils.h"
#include <math.h>

float targetX = 400;
/*---------------------------------IDLE CODE-----------------------------*/
void ConIdle_Init(Container* container, StateMachine* SM, float dt) {
	container->stateTimer = 0;
	//printf("Player entered IDLE::INIT state\n");

}
void ConIdle_Update(Container* container, StateMachine* SM, float dt) {
	
	//Code that loops through list of active buttons on container,
	if (1==IsImgHovered(container->leftTopPos, container->width, container->height, (CP_Vector){CP_Input_GetMouseX(), CP_Input_GetMouseY()}) ){
		container->stateTimer = 0;
		return;
	}
	//replay animation
	if (2==IsImgHovered(container->leftTopPos, container->width, container->height, (CP_Vector) { CP_Input_GetMouseX(), CP_Input_GetMouseY() })) {
		FSM_SetState(SM, ConScrollState, container, dt);
		return;
	}
}

void ConIdle_Exit(Container* container, StateMachine* SM, float dt){
	
}

/*---------------------------------PickUp Functions-----------------------------*/

void ConScrollIn_Init(Container* container, StateMachine* SM, float dt){
	// Code that zooms in till a certain size of entity,
	// Code that brings in ui from the left.
	container->stateTimer = 0;
	container->animate = 1;
	container->leftTopPos = (CP_Vector){ 0,0 };
}
void ConScrollIn_Update(Container* container, StateMachine* SM, float dt){
	if (container->animate) {
		container->stateTimer += dt * 3.0f;
		float bounce_decay = sin(container->stateTimer * 5) * exp(-(container->stateTimer) * 2);
		float progress = 1.0f - exp(-(container->stateTimer) * 2);
		container->leftTopPos.x = -300 + (targetX + (bounce_decay * 100) + 300) * progress;
		if ( fabs( container->leftTopPos.x - targetX ) < 0.5f && container->stateTimer > 2.0f)
		{
			container->leftTopPos.x = 400;
			container->animate = 0;
		}
	} else 
	{ FSM_SetState(SM, ConIdleState, container, dt); }
}
void ConScrollIn_Exit(Container* container, StateMachine* SM, float dt){
}

/*---------------------------------HIDE FUNCTION-----------------------------*/
void ConHidden_Init(Container* container, StateMachine* SM, float dt) {
	container->opacity = 255;
}
void ConHidden_Update(Container* container, StateMachine* SM, float dt){
	if (container->opacity>0)
	{ container->opacity -= dt; } 
}

void ConHidden_Exit(Container* container, StateMachine* SM, float dt){
}

/*---------------------------------States Assigning-----------------------------*/
States ConIdleState = {
	ConIdle_Init,
	ConIdle_Update,
	ConIdle_Exit
};

States ConScrollState = {
	ConScrollIn_Init,
	ConScrollIn_Update,
	ConScrollIn_Exit
};

States ConHiddenState = {
	ConHidden_Init,
	ConHidden_Update,
	ConHidden_Exit
};