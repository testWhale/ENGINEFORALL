#include "cprocessing.h"
#include "container.h"
#include <stdio.h>
#include <stdlib.h>

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

void ContArr_Insert(ContArr* Array, Container Entity) {
	if (Array->used >= Array->maxLength) {
		Array->maxLength += 1;
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

void ContArr_Free(ContArr* Array) {
	free(Array->container);
	Array->container = NULL;
	Array->entitySize = 0;
	Array->maxLength = 0;
	Array->used = 0;
}

/*------------------Definitions: Container ---------------------*/
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

void Container_Draw(Container* contain) {
	int width = contain->width;
	int height = contain->height;
	CP_Image_Draw(contain->bg, contain->leftTopPos.x, contain->leftTopPos.y, width, height, 255);
}

void Container_Destroy(Container* contain) {
	CP_Image_Free(contain->bg);
}

Container* getContainer(char* Slabel, ContArr* Array) {
	for (int i = 0; i < Array->maxLength; i++) {
		if (strcmp(Slabel, Array->container[i].label) == 0) {
			Container* ptr = &(Array->container[i]);
			return ptr;
		}
	}
}