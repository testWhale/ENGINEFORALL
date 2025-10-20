#include "cprocessing.h"
#include "container.h"
float space_remaining(Container* contain) {
	//CP_Vector startPos= contain->centerPos.x - contain->width
}
void Container_Init(Container* contain) {
	char* filepath = contain->bg_filepath;
	contain->bg = CP_Image_Load(filepath);
	if (contain->bg == NULL) {
		printf("CANNOT LOAD %s", filepath);
	}

		float screen_width = CP_System_GetWindowWidth();
		float screen_height = CP_System_GetWindowHeight();


	// CALCULATE SCALE TO FILL SCREEN (PRESERVE ASPECT RATIO)
	float scaleX = screen_width / contain->width;
	float scaleY = screen_height / contain->height;

	// USE SMALLER SCALE TO FIT BOTH DIMENSIONS
	float scale = (scaleX < scaleY) ? scaleX : scaleY;
	printf("scale: %f", scale);
	// SET CONTAINER SIZE
	contain->width = contain->width * scale;
	contain->height = contain->height * scale;
}

void Container_Update(Container* contain) {
	int width = contain->width;
	int height = contain->height;
	if (contain->bg == NULL) {
		printf("CANNOT LOAD %s", contain->bg_filepath);
	}
	//if (contain->width == 0) {
	//	printf("CANNOT LOAD");
	//}
	//if (contain->height == 0) {
	//	printf("CANNOT LOAD");
	//}
	CP_Image_Draw(contain->bg, width / 2, height / 2, width, height, 255);
}
void Container_Destroy(Container* contain) {
	CP_Image_Free(contain->bg);
}