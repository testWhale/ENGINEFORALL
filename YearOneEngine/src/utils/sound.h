//---------------------------------------------------------
// file:	sound.h
// author:	Zachary Ng
// email:	zacharyhuaen.n@digipen.edu
//
// brief:	Defines sound buckets for GameEntity entities sounds.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#ifndef SOUND_H
#define SOUND_H

#include "cprocessing.h"

/* entSound
Brief:
	Holds sound handles used by entities.
*/
typedef struct {
	CP_Sound soundIdle; //didnt get used
	CP_Sound soundShoot;  //didnt get used
	CP_Sound soundHurt; //didnt get used
	CP_Sound soundPlace;
	CP_Sound soundSel; //didnt get used
}entSound;

/* bgSound
Brief:
	Holds the music sound handle.
*/
typedef struct {
	CP_Sound idleMusic;
}bgSound;



#endif