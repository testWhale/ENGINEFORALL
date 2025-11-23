#include "logo.h"
#include "cprocessing.h"
#include "mainmenu.h"

CP_Image justinFace = NULL;
float elapsed = 0.0f;          // time since screen started
const float FADE_DURATION = 3.0f;  // 3 seconds fade

void Logo_Init(void)
{
    elapsed = 0; // reset timer
    CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
    justinFace = CP_Image_Load("Assets/Misc/DigiPen_BLACK.png");

    if (justinFace == NULL)
    {
        CP_System_SetWindowTitle("Error: Failed to load DigiPen_BLACK.png");
    }
}

void Logo_Update(void)
{
    elapsed += CP_System_GetDt();

    float t = elapsed / FADE_DURATION;
    if (t > 1.0f) t = 1.0f;
    int alpha = (int)(t * 255.0f);

    int width = CP_System_GetWindowWidth();
    int height = CP_System_GetWindowHeight();

    // scale logo to 60% of screen width
    float drawW = width * 0.6f;
    float aspect = 445.0f / 1525.0f;
    float drawH = drawW * aspect;

    CP_Graphics_ClearBackground(CP_Color_Create(255, 255, 255, 255));
    CP_Settings_ImageMode(CP_POSITION_CENTER);

    /* draw centered */
    CP_Image_Draw(justinFace,
        width * 0.5f,
        height * 0.5f,
        drawW,
        drawH,
        alpha);

    if (elapsed > FADE_DURATION + 0.5f)
    {
        CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
    }
}

void Logo_Exit(void)
{
    CP_Image_Free(justinFace);
}
