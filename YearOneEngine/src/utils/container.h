//---------------------------------------------------------
// file:	container.h
// author:	[Zachary Ng]
// email:	[zacnghuaen.n@digipen.edu]
//
// brief:	Types and functions for container panels and their array.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#ifndef CONTAINER_H
#define CONTAINER_H
#include "cprocessing.h"

/*Container H just scales the container to the screen size, draws the container, and frees it.
The code that activates its specific states is inside of /backend*/
typedef struct Container{
	int id; char label[100]; CP_Vector leftTopPos; int width; int height;
	CP_Image bg; char bg_filepath[100]; /*Basic Identifiers*/

	float scale_factor;  float opacity; int animate;float stateTimer;
} Container;

/*Dynamic Array Code*/
typedef struct ContArr {
	Container* container; //I want ContArr to own dynamic arr Container structs, Allows me to free it here.
	size_t entitySize; //why not pointer? cause i want my array to actually own these structs and be able to use and delete them as and when.
	size_t used;
	size_t maxLength;
}ContArr;

/*Declarations Array Code*/
/* ContArr_Init()
Input:
    size_t maxLength - slots to reserve
    ContArr* Array - array struct to fill
Output:
    ContArr current array
Brief:
    Prepares the container array and allocates space for each slot.
*/
ContArr ContArr_Init(size_t maxLength, ContArr* Array);

/* ContArr_Insert()
Input:
    ContArr* Array - array to insert into
    Container container - value to add
Output:
    void
Brief:
    Adds a container, growing the buffer when needed.
*/
void ContArr_Insert(ContArr* Array, Container container);

/* ContArr_Free()
Input:
    ContArr* Array - array to free
Output:
    void
Brief:
    Releases the storage and resets counts.
*/
void ContArr_Free(ContArr* Array);

/*Declarations Container Code*/
/* Container_Init()
Input:
    Container* container - container to set up
Output:
    void
Brief:
    Loads the background image and scales it to the screen.
*/
void Container_Init(Container* container);

/* Container_Draw()
Input:
    Container* container - container to draw
Output:
    void
Brief:
    Draws the background image at the stored position.
*/
void Container_Draw(Container* container);

/* Container_Destroy()
Input:
    Container* container - container holding the image
Output:
    void
Brief:
    Frees the image resource.
*/
void Container_Destroy(Container* container);

/*Declarations Get Specific Container*/
/* getContainer()
Input:
    char* label - name of the container to find
    ContArr* Array - array to search
Output:
    Container* pointer when found, otherwise NULL
Brief:
    Searches the array by label.
*/
Container* getContainer(char* label, ContArr* Array);

ContArr containersArr;

#endif