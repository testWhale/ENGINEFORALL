#include "SM.h"
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


