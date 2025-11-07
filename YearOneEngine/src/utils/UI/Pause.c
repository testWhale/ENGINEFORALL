
#include "pause.h"
#include "Button/button.h"

static int s_paused = 0;   // Tracks pause state: 0 = running, 1 = paused
static int s_menuRequest = 0;  // Tracks if Menu was clicked

static buttonInfo s_btnPause;   // Pause button
static buttonInfo s_btnResume;  // Resume button
static buttonInfo s_btnMenu;    // Menu button

// Button image assets
#define PAUSE_N   "Assets/buttons/Pause normal.png"
#define PAUSE_H   "Assets/buttons/Pause hover.png"
#define PAUSE_C   "Assets/buttons/Pause clicked.png"

#define BTN_N     "Assets/buttons/button normal.png"
#define BTN_H     "Assets/buttons/button hover.png"
#define BTN_C     "Assets/buttons/button clicked.png"

// Returns current pause state
int Pause_IsPaused(void) { return s_paused; }

// Sets pause state (on = 1 pauses, on = 0 resumes)
void Pause_SetPaused(int on) { s_paused = (on != 0); }

// Returns dt or 0 if paused (freezes game updates when paused)
float Pause_Dt(float dt) { return s_paused ? 0.0f : dt; }

// Returns menu request flag and resets it
int Pause_TakeMenuRequest(void) { int r = s_menuRequest; s_menuRequest = 0; return r; }

// Initializes pause system and loads button assets
void Pause_Init(void)
{
    s_paused = 0;          // Start unpaused
    s_menuRequest = 0;     // No menu request initially

    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();
    (void)H;

    const float icon = 42.0f;
    const float cx = W - (icon * 0.5f) - 10.0f;
    const float cy = 10.0f + (icon * 0.5f);

    // Configure buttons with positions and assets
    buttonLoad(&s_btnPause, cx, cy, icon, icon, 0.0f, PAUSE_N, PAUSE_C, PAUSE_H);
    buttonLoad(&s_btnResume, 0.0f, 0.0f, 200.0f, 48.0f, 0.0f, BTN_N, BTN_C, BTN_H);
    buttonLoad(&s_btnMenu, 0.0f, 0.0f, 200.0f, 48.0f, 0.0f, BTN_N, BTN_C, BTN_H);
}

// Handles pause button behavior and draws pause menu when paused
void Pause_UpdateAndDraw(void)
{
    const float W = (float)CP_System_GetWindowWidth();
    const float H = (float)CP_System_GetWindowHeight();

    // If game is running, check pause button click
    if (!s_paused)
    {
        buttonBehavior(&s_btnPause);
        if (s_btnPause.isClicked) {
            s_paused = 1;                // Pause game
            s_btnPause.isClicked = 0;    // Reset click state
        }
        return; // Skip drawing pause menu
    }

    //overlay panel for pause menu
    const float panelW = 720.0f;
    const float panelH = 360.0f;
    const float cx = 0.5f * W;
    const float cy = 0.5f * H;

    CP_Settings_RectMode(CP_POSITION_CENTER);
    CP_Settings_Fill(CP_Color_Create(25, 25, 25, 230)); // Dark overlay
    CP_Settings_Stroke(CP_Color_Create(255, 255, 255, 35));
    CP_Settings_StrokeWeight(2.0f);
    CP_Graphics_DrawRect(cx, cy, panelW, panelH);

    // Draw "PAUSED" text
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(240, 240, 240, 255));
    CP_Settings_TextSize(36.0f);
    CP_Font_DrawText("PAUSED", cx, cy - panelH * 0.5f + 70.0f);

    // Position Resume and Menu buttons
    const float gap = 72.0f;
    s_btnResume.buttonWidth = 280.0f;
    s_btnResume.buttonHeight = 60.0f;
    s_btnMenu.buttonWidth = 280.0f;
    s_btnMenu.buttonHeight = 60.0f;

    s_btnResume.buttonPos.x = cx;
    s_btnResume.buttonPos.y = cy - 10.0f;
    s_btnMenu.buttonPos.x = cx;
    s_btnMenu.buttonPos.y = s_btnResume.buttonPos.y + s_btnResume.buttonHeight + gap;

    // Handle button clicks
    buttonBehavior(&s_btnResume);
    buttonBehavior(&s_btnMenu);

    // Draw button labels
    CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
    CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_TextSize(28.0f);
    CP_Font_DrawText("Resume", s_btnResume.buttonPos.x, s_btnResume.buttonPos.y);
    CP_Font_DrawText("Menu", s_btnMenu.buttonPos.x, s_btnMenu.buttonPos.y);

    // Resume or menu request actions
    if (s_btnResume.isClicked) { s_paused = 0; s_btnResume.isClicked = 0; }
    if (s_btnMenu.isClicked) { s_menuRequest = 1; s_btnMenu.isClicked = 0; }

    CP_Settings_RectMode(CP_POSITION_CENTER);
}
