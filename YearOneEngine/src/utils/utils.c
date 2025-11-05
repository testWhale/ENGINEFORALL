#include <math.h>
#include <stdio.h>
#include "utils/arr.h"
#include "test.h"
#include "utils.h"

int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	if (click_x >= area_center_x - (area_width / 2) && click_x <= area_center_x + (area_width / 2) &&
		click_y >= area_center_y - (area_height / 2) && click_y <= area_center_y + (area_height / 2))
	{
		if (CP_Input_MouseClicked())
		{
			return 1;
		}
	}
	return 0;
}
int IsImgHovered(CP_Vector leftTopBound, float area_width, float area_height, CP_Vector mouse)
{
	if (CP_Input_MouseClicked()) {
		if ((mouse.x >= leftTopBound.x) && (mouse.x <= (leftTopBound.x + area_width)) &&
			(mouse.y >= leftTopBound.y) && (mouse.y <= (leftTopBound.y + area_height))) {
			return 2;
		}
	} else{
		if ((mouse.x >= leftTopBound.x) && (mouse.x <= (leftTopBound.x + area_width)) &&
			(mouse.y >= leftTopBound.y) && (mouse.y <= (leftTopBound.y + area_height))) {
			return 1; }
		return 0; }
}

int IsCircleClicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y){
	//find the dist btwn the point clicked and the center of the circle.
	float radius = diameter / 2.0f;
	float dist_x = click_x - circle_center_x;
	float dist_y = click_y - circle_center_y;
	dist_x = dist_x * dist_x;
	dist_y = dist_y * dist_y;
	double dist = sqrt(dist_x + dist_y);
	if (dist <= radius && CP_Input_MouseDoubleClicked() ) {
		printf("Circle Clicked\n");
		return 1;
	}
	return 0;
}

int AreCirclesIntersecting(Bullet* bullet, GameEntity* enemy) {
	CP_Vector vec_c1 = CP_Vector_Set(bullet->centerPos.x, bullet->centerPos.y);
	CP_Vector vec_c2 = CP_Vector_Set(enemy->centerPos.x, enemy->centerPos.y);
	
	return (bullet->diameter / 2.0f + enemy->diameter / 2.0f) >= CP_Vector_Distance(vec_c1, vec_c2);
}

//int IntitializeEntity(GameEntity* entity, int id, float pos_x, float pos_y, float rotation, CP_BOOL isPlayer) {
//	if (entity == NULL) {
//		return 0;
//	}
//	entity->id = id;
//	entity->centerPos.x = pos_x;
//	entity->centerPos.y = pos_y;
//	entity->rotation = rotation;
//	entity->isPlayer = isPlayer;
//	return 1;
//}
