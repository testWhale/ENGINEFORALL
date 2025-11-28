//---------------------------------------------------------
// file:	utils.h
// author:	[Ding Yi Chaw Maung]
// email:	[dingyichaw.maung@digipen.edu]
//
// brief:	Declarations for mouse and click helpers.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------
#ifndef UTIL_H
#define UTIL_H
#include "utils/arr.h"
#include "cprocessing.h"

/* IsAreaClicked()
Input:
    float area_center_x - center X of the rectangle
    float area_center_y - center Y of the rectangle
    float area_width - width of the rectangle
    float area_height - height of the rectangle
    float click_x - click X
    float click_y - click Y
Output:
    int (1 if clicked inside)
Brief:
    Checks whether the last click was inside the rectangle.
*/
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);

/* Is_Circle_Clicked()
Input:
    float circle_center_x - circle center X
    float circle_center_y - circle center Y
    float diameter - circle size
    float click_x - click X
    float click_y - click Y
Output:
    int (1 if the circle was clicked)
Brief:
    Returns 1 if the double-click happened inside the circle.
*/
int Is_Circle_Clicked(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

/* Is_Mouse_Released()
Input:
    float circle_center_x - circle center X
    float circle_center_y - circle center Y
    float diameter - circle size
    float click_x - click X
    float click_y - click Y
Output:
    int (1 while mouse button is down inside the circle)
Brief:
    Tracks whether the mouse is pressed inside the circle limiter.
*/
int Is_Mouse_Released(float circle_center_x, float circle_center_y, float diameter, float click_x, float click_y);

/* Is_Right_Clicked()
Input:
    None
Output:
    int (1 when right button was released)
Brief:
    Returns 1 when the right mouse button is released.
*/
int Is_Right_Clicked();

/* IsImgHovered()
Input:
    CP_Vector leftTopBound - top-left corner of the hit box
    float area_width - box width
    float area_height - box height
    CP_Vector mouse - current mouse position
Output:
    int (0 none, 1 hover, 2 click)
Brief:
    Returns whether the mouse is over or clicked in the area.
*/
int IsImgHovered(CP_Vector leftTopBound, float area_width, float area_height, CP_Vector mouse);

/* AreCirclesIntersecting()
Input:
    GameEntity* bullet - bullet to test
    GameEntity* enemy - enemy to test
Output:
    int (non-zero if they overlap)
Brief:
    Checks whether two circles (bullet/enemy) overlap.
*/
int AreCirclesIntersecting(GameEntity* bullet, GameEntity* enemy);

/* EnemyCrossedLine()
Input:
    GameEntity* enemy - enemy to test
Output:
    int (1 when the enemy crossed the line)
Brief:
    Returns 1 when the enemy reaches the far edge of the tiles.
*/
int EnemyCrossedLine(GameEntity* enemy);
#endif