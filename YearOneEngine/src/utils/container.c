//---------------------------------------------------------
// file:	container.c
// author:	[Zachary Ng]
// email:	[zacnghuaen.n@digipen.edu]
//
// brief:	Manages container arrays and draws background panels.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include "cprocessing.h"
#include "container.h"
#include <stdio.h>
#include <stdlib.h>

/* ContArr_Init()
Input:
    size_t maxLength - how many containers to reserve
    ContArr* Array - array structure to fill
Output:
    ContArr current global array
Brief:
    Sets up the container array and allocates space for each entry.
*/
ContArr ContArr_Init(size_t maxLength, ContArr* Array) {

	containersArr.maxLength = maxLength;
	containersArr.entitySize = 0;
	containersArr.used = 0;
	containersArr.container = (Container*)malloc(maxLength * sizeof(Container));
	//for (int i = 0; i < maxLength; i++) { 
	//	*(containersArr.container + i) = (Container){
	//	.id = 0, . = NULL, .unit = NULL };
	//}
	return containersArr;
}

/* ContArr_Insert()
Input:
    ContArr* Array - array to insert into
    Container Entity - container data to store
Output:
    void
Brief:
    Grows the buffer if needed and appends the new container.
*/
void ContArr_Insert(ContArr* Array, Container Entity) {
	if (Array->used >= Array->maxLength) {
		Array->maxLength *= 2;
	}
	//realloc tries preserves old data when it enlarges, if unable it allocates new memory but frees old block 
	Array->container = realloc(Array->container, Array->maxLength * sizeof(Container)); //so how am I able to pass it itself?
	//i  want to add another element to the containersArr. but doesnt this wipe the first containersArr and realloc(, numofArrElems)
	if (!Array->container) {
		fprintf(stderr, "Memory reallocation failed!\n");
	}
	Array->container[Array->used] = Entity;
	Array->used++;
}

/* ContArr_Free()
Input:
    ContArr* Array - array to clear
Output:
    void
Brief:
    Frees the array buffer and resets counts.
*/
void ContArr_Free(ContArr* Array) {
	free(Array->container);
	Array->container = NULL;
	Array->entitySize = 0;
	Array->maxLength = 0;
	Array->used = 0;
}

/*------------------Definitions: Container ---------------------*/
/* Container_Init()
Input:
    Container* contain - container to prepare
Output:
    void
Brief:
    Loads the background image and scales the container to the screen.
*/
void Container_Init(Container* contain) {
	
	contain->bg = CP_Image_Load(contain->bg_filepath);
	if (contain->bg == NULL) {
		printf("CANNOT LOAD %s", contain->bg_filepath);
	} CP_Settings_ImageMode(CP_POSITION_CORNER); /*Setting the Image at the top left corner. Easier to mark out the limits of the img*/
	
	float screen_width = CP_System_GetWindowWidth();
	float screen_height = CP_System_GetWindowHeight();
	
	// CALCULATE SCALE TO FILL SCREEN (PRESERVE ASPECT RATIO)
	float scaleX = screen_width / contain->width;
	float scaleY = screen_height / contain->height;
	if (0.0f == contain->scale_factor) { contain->scale_factor = 1.0f;} 
	if (0.0f == contain->opacity) { contain->opacity = 255; }

	// USE SMALLER SCALE TO FIT BOTH DIMENSIONS
	float scale = ((scaleX < scaleY) ? scaleX : scaleY) * contain->scale_factor;
	printf("scale: %f", scale);
	// SET CONTAINER SIZE
	contain->width *= scale;
	contain->height *= scale;
}

/* Container_Draw()
Input:
    Container* contain - container to draw
Output:
    void
Brief:
    Draws the container background image at its stored position.
*/
void Container_Draw(Container* contain) {
	int width = contain->width;
	int height = contain->height;
	CP_Image_Draw(contain->bg, contain->leftTopPos.x, contain->leftTopPos.y, width, height, 255);
}

/* Container_Destroy()
Input:
    Container* contain - container holding the image
Output:
    void
Brief:
    Frees the background image.
*/
void Container_Destroy(Container* contain) {
	CP_Image_Free(contain->bg);
}

/* getContainer()
Input:
    char* Slabel - label to look for
    ContArr* Array - array to search
Output:
    Container* pointer when the label matches
Brief:
    Finds a container by label in the array.
*/
Container* getContainer(char* Slabel, ContArr* Array) {
	for (int i = 0; i < Array->maxLength; i++) {
		if (strcmp(Slabel, Array->container[i].label) == 0) {
			Container* ptr = &(Array->container[i]);
			return ptr;
		}
	}
}