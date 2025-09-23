#include "cprocessing.h"
#include <stdio.h>
#include "grid.h"
char buffer[256];
CP_Font myfont;



void grid_init(void)
{
    myfont = CP_Font_Load("Assets/Fonts/Exo2/Exo2-Regular.ttf");
    if (myfont == NULL)
    {
        printf("Failed to load image\n");
    }
}



void grid_update(void)
{
    float win_width = CP_System_GetWindowWidth();
    float win_height = CP_System_GetWindowHeight();
    float col_width = win_width / 3.0f;
    float row_height = win_height / 3.0f;
    
    // Draw vertical white grid lines (left, center, right) 
    CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 255)); 
    CP_Settings_StrokeWeight(2.0f);
    CP_Graphics_DrawLine(col_width, 0, col_width, win_height); // Left column line
    CP_Graphics_DrawLine(2 * col_width, 0, 2 * col_width, win_height); // Right column line

    // Draw horizontal grid lines (top, middle, bottom)
    CP_Graphics_DrawLine(0, row_height, win_width, row_height); // Top row line
    CP_Graphics_DrawLine(0, 2 * row_height, win_width, 2 * row_height); // Bottom row line
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

    // Label grid cells
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Font_Set(myfont);
    CP_Settings_TextSize(72.f);
    
    CP_Font_DrawText("Left-Top", col_width * 0.5f, row_height * 0.5f);
    CP_Font_DrawText("Center-Top", col_width * 1.5f, row_height * 0.5f);
    CP_Font_DrawText("Right-Top", col_width * 2.5f, row_height * 0.5f);
    CP_Font_DrawText("Left-Middle", col_width * 0.5f, row_height * 1.5f);
    CP_Font_DrawText("Center-Middle", col_width * 1.5f, row_height * 1.5f);
    CP_Font_DrawText("Right-Middle", col_width * 2.5f, row_height * 1.5f);
    CP_Font_DrawText("Left-Bottom", col_width * 0.5f, row_height * 2.5f);
    CP_Font_DrawText("Center-Bottom", col_width * 1.5f, row_height * 2.5f);
    CP_Font_DrawText("Right-Bottom", col_width * 2.5f, row_height * 2.5f);
}

CP_Vector grid_coords(IMG_ALIGN_HORIZONTAL h_align, IMG_ALIGN_VERTICAL v_align, float h_offset, float v_offset)
{
    float win_width = CP_System_GetWindowWidth();
    float win_height = CP_System_GetWindowHeight();
    float col_width = win_width / 3.0f;
    float row_height = win_height / 3.0f;
    float x = 0.0f, y = 0.0f;

    // Horizontal alignment
    if (h_align & IMG_ALIGN_H_LEFT) {
        x = col_width * 0.5f + h_offset;
    }
    else if (h_align & IMG_ALIGN_H_CENTER) {
        x = col_width * 1.5f + h_offset;
    }
    else if (h_align & IMG_ALIGN_H_RIGHT) {
        x = col_width * 2.5f + h_offset;
    }
    else {
        x = col_width * 1.5f; // Default to center
        printf("Warning: Invalid horizontal alignment, defaulting to center\n");
    }

    // Vertical alignment
    if (v_align & IMG_ALIGN_V_TOP) {
        y = row_height * 0.5f + v_offset;
    }
    else if (v_align & IMG_ALIGN_V_MIDDLE) {
        y = row_height * 1.5f + v_offset;
    }
    else if (v_align & IMG_ALIGN_V_BOTTOM) {
        y = row_height * 2.5f + v_offset;
    }
    else {
        y = row_height * 1.5f; // Default to middle
        printf("Warning: Invalid vertical alignment, defaulting to middle\n");
    }

    //// Apply offsets if specified
    //if (h_align & IMG_ALIGN_H_OFFSET) {
    //    x += h_offset;
    //}
    //if (v_align & IMG_ALIGN_V_OFFSET) {
    //    y += v_offset;
    //}

    return CP_Vector_Set(x, y);
}

void grid_exit(void)
{
    // No cleanup needed
}

