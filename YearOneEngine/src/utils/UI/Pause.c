
#include "pause.h"
#include "cprocessing.h"


static int   g_paused = 0;
static float g_btnW = 140.0f;
static float g_btnH = 46.0f;
static float g_btnPad = 12.0f;  
static float g_btnYBelow = 44.0f;   


static int PointInRect(float px, float py, float x, float y, float w, float h) {
    return (px >= x && px <= x + w && py >= y && py <= y + h);
}


void Pause_Init(void) {
    g_paused = 0;
}

void Pause_Toggle(void) {
    g_paused = !g_paused;
}

int Pause_IsOpen(void) {
    return g_paused;
}


void Pause_UpdateAndDrawTopRightButton(void) {
    float WW = (float)CP_System_GetWindowWidth();
    float btnX = WW - g_btnPad - g_btnW;
    float btnY = g_btnPad + g_btnYBelow;

  
    if (CP_Input_KeyTriggered(KEY_P)) g_paused = !g_paused;
    if (CP_Input_MouseTriggered(MOUSE_BUTTON_1)) {
        float mx = CP_Input_GetMouseX(), my = CP_Input_GetMouseY();
        if (PointInRect(mx, my, btnX, btnY, g_btnW, g_btnH)) g_paused = !g_paused;
    }

    
    int hovered = PointInRect(CP_Input_GetMouseX(), CP_Input_GetMouseY(), btnX, btnY, g_btnW, g_btnH);

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 180));
    CP_Settings_StrokeWeight(2.0f);
    CP_Settings_Fill(hovered ? CP_Color_Create(60, 60, 60, 255)
        : CP_Color_Create(40, 40, 40, 255));
    CP_Graphics_DrawRect(btnX, btnY, g_btnW, g_btnH);

    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_TextSize(22.0f);
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Font_DrawText(g_paused ? "Resume" : "Pause",
        btnX + g_btnW * 0.5f, btnY + g_btnH * 0.5f);
}


void Pause_DrawOverlay(void) {
    if (!g_paused) return;

    float WW = (float)CP_System_GetWindowWidth();
    float HH = (float)CP_System_GetWindowHeight();

    CP_Settings_RectMode(CP_POSITION_CORNER);
    CP_Settings_Fill(CP_Color_Create(0, 0, 0, 140));
    CP_Graphics_DrawRect(0, 0, WW, HH);

    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_TextSize(72.0f);
    CP_Font_DrawText("PAUSED", WW * 0.5f, HH * 0.45f);

    CP_Settings_TextSize(20.0f);
    CP_Font_DrawText("Press P or click Resume", WW * 0.5f, HH * 0.55f);
}
