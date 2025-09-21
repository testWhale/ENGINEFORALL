#ifndef __STRUCT_H
#define __STRUCT_H

#include "cprocessing.h"
#include <stdio.h>
#include <stdbool.h>
struct MouseSaveTem {
	float x;
	float y;
	CP_Image sprite;
 }; typedef struct MouseSaveTem MouseSave;

struct Line {
	 float x1;
	 float y1;
	 float x2;
	 float y2;
	 bool isActive;
 }; typedef struct Line LineSave;
typedef enum MouseState {
	FirstClick,
	SecondClick,
	Reset
} MouseClickState;

int saveMousePos(MouseSave* nMouse, LineSave* nLine);
int createLine(MouseSave* nMouse, LineSave* nLine);
int MouseManager(MouseSave *nMouse, LineSave* nLine);

#endif