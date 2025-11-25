#ifndef SOUND_H
#define SOUND_H

#include "cprocessing.h"

typedef struct {
	CP_Sound soundIdle;
	CP_Sound soundShoot;
	CP_Sound soundHurt;
	CP_Sound soundPlace;
	CP_Sound soundSel;
}entSound;

typedef struct {
	CP_Sound idleMusic;
}bgSound;



#endif