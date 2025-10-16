#ifndef UTIL_H
#define UTIL_H
#include "cprocessing.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y, int button);
int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);


#endif UTIL_H