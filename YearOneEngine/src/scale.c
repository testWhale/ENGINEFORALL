//#include "scale.h"
// struct LOGO {
//	CP_Image logo;
//	float img_startX;
//	float img_startY;
//};
// struct LOGO DigiPenLOGO = {NULL,0,0};
//
//void scale_init(void)
//{
//	//declare and initialize variables: logo
//	DigiPenLOGO.logo = CP_Image_Load("Assets/DigiPen_BLACK.png");
//	if (DigiPenLOGO.logo == NULL)
//	{
//		printf("Failed to load image\n");
//	}
//	DigiPenLOGO.img_startX = 0.0f;
//	DigiPenLOGO.img_startY = 0.0f;
//	CP_Settings_ImageMode(CP_POSITION_CORNER);
//	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
//}
//
//void scale_update(void)
//{
//	//clear background to black
//	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
//	//update player variables
//	int width = CP_Input_GetMouseX();
//	int height = CP_Input_GetMouseY();
//	//draw image every frame
//	CP_Image_Draw(DigiPenLOGO.logo, DigiPenLOGO.img_startX, DigiPenLOGO.img_startY, width, height, 255);
//}
//
//void scale_exit(void)
//{
//	//free resources loaded (unload)
//	CP_Image_Free(DigiPenLOGO.logo);
//
//	CP_Engine_Terminate();
//}