#pragma once
#ifndef GRID_H
#define GRID_H

typedef struct Grid {
	int rows;
	int cols;
	float cellWidth;
	float cellHeight;
	float offsetX;
	float offsetY;
};
typedef enum {
	LeftTop, CenterTop, RightTop,
	LeftMiddle, CenterMiddle, RightMiddle,
	LeftBottom, CenterBottom, RightBottom
} Placement;

typedef enum IMG_ALIGN_HORIZONTAL
{
	IMG_ALIGN_H_LEFT = 1 << 0,      // Align image to the left column of the 3x3 grid
	IMG_ALIGN_H_CENTER = 1 << 1,    // Align image to the center column of the 3x3 grid
	IMG_ALIGN_H_RIGHT = 1 << 2,     // Align image to the right column of the 3x3 grid
	IMG_ALIGN_H_OFFSET = 1 << 3     // Flag to indicate custom horizontal offset
} IMG_ALIGN_HORIZONTAL;

typedef enum IMG_ALIGN_VERTICAL
{
	IMG_ALIGN_V_TOP = 1 << 4,       // Align image to the top row of the 3x3 grid
	IMG_ALIGN_V_MIDDLE = 1 << 5,    // Align image to the middle row of the 3x3 grid
	IMG_ALIGN_V_BOTTOM = 1 << 6,    // Align image to the bottom row of the 3x3 grid
	IMG_ALIGN_V_OFFSET = 1 << 7     // Flag to indicate custom vertical offset
} IMG_ALIGN_VERTICAL;

void grid_init(void);

void grid_update(void);
CP_Vector grid_coords(IMG_ALIGN_HORIZONTAL h_align, IMG_ALIGN_VERTICAL v_align, float h_offset, float v_offset);
void grid_exit(void);
#endif
