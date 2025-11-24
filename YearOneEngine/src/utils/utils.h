#ifndef UTIL_H
#define UTIL_H
#include "utils/arr.h"
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
int Is_Circle_Clicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int Is_Mouse_Released(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);
int Is_Right_Clicked();
int IsImgHovered(CP_Vector leftTopBound, float area_width, float area_height, CP_Vector mouse);
int AreCirclesIntersecting(GameEntity* bullet, GameEntity* enemy);
int EnemyCrossedLine(GameEntity* enemy);
#endif