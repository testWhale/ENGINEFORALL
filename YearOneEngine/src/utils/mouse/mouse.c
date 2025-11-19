#include "mouse.h"

static int pickupCount = 1;
static bool isMouseDown = false;
static bool mouseReleased = false;

void Mouse_Init(void)
{
    pickupCount = 0;
    isMouseDown = false;
    mouseReleased = false;
}

void Mouse_Update(void)
{
    bool mouseDown = CP_Input_MouseDown(MOUSE_BUTTON_LEFT);

    // Detect release event (pressed last frame, not pressed now)
    if (CP_Input_MouseReleased(MOUSE_BUTTON_LEFT))
        mouseReleased = true;
    else
        mouseReleased = false;

    isMouseDown = mouseDown;
}

bool Mouse_CanPickup(void)
{
    return pickupCount < MAX_PICKUP_ITEMS;
}

void Mouse_AddPickup(void)
{
    if (pickupCount < MAX_PICKUP_ITEMS)
        pickupCount++;
}
void Mouse_DelPickup(void)
{
        pickupCount--;
}

int Mouse_GetPickupCount(void)
{
    return pickupCount;
}
void Free_Pickup() {
    pickupCount = 0;
}

//bool Is_Mouse_Released(float cx, float cy, float radius, float mx, float my)
//{
//    if (!mouseReleased)
//        return false;
//
//    // Check distance mouse  circle center
//    float dx = mx - cx;
//    float dy = my - cy;
//    float distSq = dx * dx + dy * dy;
//
//    return distSq <= radius * radius;
//}
