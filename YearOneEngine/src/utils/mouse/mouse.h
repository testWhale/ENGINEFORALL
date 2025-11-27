#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>
#include "cprocessing.h"

int cursor;

// Maximum items the player is allowed to pick up
#define MAX_PICKUP_ITEMS 5

/* Mouse_Init()
Input:
    None
Output:
    void
Brief:
    Resets mouse button tracking and pickup counters.
*/
void Mouse_Init(void);

/* Mouse_Update()
Input:
    None
Output:
    void
Brief:
    Samples the current mouse button state and marks whenever the left button is released.
*/
void Mouse_Update(void);

/* Mouse_CanPickup()
Input:
    None
Output:
    bool indicating whether a new pickup can be added
Brief:
    Checks the pickup counter against the predefined limit.
*/
bool Mouse_CanPickup(void);

/* Mouse_AddPickup()
Input:
    None
Output:
    void
Brief:
    Increments the active pickup counter if the limit isn't reached.
*/
void Mouse_AddPickup(void);

/* Mouse_DelPickup()
Input:
    None
Output:
    void
Brief:
    Decrements the pickup counter when an item is dropped or consumed.
*/
void Mouse_DelPickup(void);

/* Mouse_GetPickupCount()
Input:
    None
Output:
    int current number of pickups held
Brief:
    Returns how many pickups the player currently possesses.
*/
int Mouse_GetPickupCount(void);

/* Free_Pickup()
Input:
    None
Output:
    void
Brief:
    Resets the pickup counter back to the default starting amount.
*/
void Free_Pickup();
#endif
