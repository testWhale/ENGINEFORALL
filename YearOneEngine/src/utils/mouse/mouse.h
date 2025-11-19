#ifndef MOUSE_H
#define MOUSE_H

#include <stdbool.h>
#include "cprocessing.h"

// Maximum items the player is allowed to pick up
#define MAX_PICKUP_ITEMS 5

// Initialize mouse system (reset counter)
void Mouse_Init(void);

// Update mouse (check for release event)
void Mouse_Update(void);

// Returns true if player is allowed to pick up more items
bool Mouse_CanPickup(void);

// Increase pickup count
void Mouse_AddPickup(void);

void Mouse_DelPickup(void);

// Get current pickup count
int Mouse_GetPickupCount(void);

#endif
