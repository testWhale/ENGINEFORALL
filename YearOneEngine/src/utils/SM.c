#include "SM.h"
//Defined Colours
#include <string.h>
#include <stdio.h>

// Transition state code
StateFunction FSM_SetState(StateMachine* fsm, States newState, GameEntity* data, float dt) {
	if (fsm->currState.exit) {
		fsm->currState.exit(data, fsm, dt);
	}
	fsm->currState = newState;
	fsm->currState.init(data, fsm, dt);
}
StateFunction FSM_Update(StateMachine* fsm, GameEntity* data, float dt) {
	fsm->currState.update(data, fsm,dt);
}
GameEntity MakePlayerTemplate() {
    GameEntity e = {
        .centerPos = {100, 100},
        .rotation = 0,
        .isPlayer = 1,
        .forwardVector = {0, 0},
        .color = {255, 0, 0, 255},
        .diameter = 50,
        .stateTimer = 0,
        .isItOnMap = 0,
        .isSel = 0,
        .label = "Player",
        .bullets = {0}  // zero init the struct
    };

    B_Arr_Init(10, &e.bullets);
    return e;
}

void PrintBulletInfo(GameEntity* entity) {

    for (size_t i = 0; i < entity->bullets.used; i++) {
        Bullet* b = &entity->bullets.bulletArr[i];
        printf("  Bullet %d at (%.1f, %.1f)\n", b->id, b->centerPos.x, b->centerPos.y);
    }
}




