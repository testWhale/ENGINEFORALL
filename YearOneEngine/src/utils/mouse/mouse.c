//---------------------------------------------------------
// file:	mouse.c
// author:	[Zachary Ng]
// email:	[zacnghuaen.n@digipen.edu]
//
// brief:	Implements mouse/ pickup count utilities for UI interactions.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "mouse.h"

static int pickupCount = 1;
static bool isMouseDown = false;
static bool mouseReleased = false;

/* Mouse_Init()
Input:
    None
Output:
    void
Brief:
    Resets pickup counters and mouse button flags before a new session.
*/
void Mouse_Init(void)
{
    pickupCount = 0;
    isMouseDown = false;
    mouseReleased = false;
}

/* Mouse_Update()
Input:
    None
Output:
    void
Brief:
    Samples the left mouse button state, tracking presses and release events for pickup logic.
*/
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

/* Mouse_CanPickup()
Input:
    None
Output:
    bool indicating whether the player can pick up another item
Brief:
    Checks if the pickup list has room left.
*/
bool Mouse_CanPickup(void)
{
    return pickupCount < MAX_PICKUP_ITEMS;
}

/* Mouse_AddPickup()
Input:
    None
Output:
    void
Brief:
    Increments the pickup counter if we are still below the limit.
*/
void Mouse_AddPickup(void)
{
    if (pickupCount < MAX_PICKUP_ITEMS)
        pickupCount++;
}

/* Mouse_DelPickup()
Input:
    None
Output:
    void
Brief:
    Decrements the pickup counter when an item is released or consumed.
*/
void Mouse_DelPickup(void)
{
    pickupCount--;
}

/* Mouse_GetPickupCount()
Input:
    None
Output:
    int current pickup counter
Brief:
    Returns how many pickups the player currently holds.
*/
int Mouse_GetPickupCount(void)
{
    return pickupCount;
}

/* Free_Pickup()
Input:
    None
Output:
    void
Brief:
    Resets the pickup counter to the default starting value.
*/
void Free_Pickup() {
    pickupCount = 1;
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
