#include "cprocessing.h"
#include "buttonSystem.h"
#include "../state/grid.h"

ButtonComponent nButton;
// Static counter for automatic ID assignment
static int next_button_id = 0;
float winCenterX, winCenterY;

void ButtonInit(ButtonComponent Buttons[], int num_buttons, float win_width, float win_height)
{
	for (int i = 0; i < num_buttons; i++) {
		/*printf("Button %d: pathToSprite = %s\n", Buttons[i].id,
			Buttons[i].pathToSprite ? Buttons[i].pathToSprite : "NULL");*/
		Buttons[i].id = i;
		printf(" %s\n", Buttons[i].pathToSprite);

		Buttons[i].sprite = CP_Image_Load(Buttons[i].pathToSprite);
		if (Buttons[i].sprite == NULL)
		{
			printf("Failed to load image %s\n", Buttons[i].pathToSprite);
		}


		Buttons[i].width = (CP_Image_GetWidth(Buttons[i].sprite) * 2) + 400;
		Buttons[i].height = CP_Image_GetHeight(Buttons[i].sprite) *2;
		CP_Vector coords = grid_coords(IMG_ALIGN_H_CENTER, IMG_ALIGN_V_MIDDLE, Buttons[i].offsetX, Buttons[i].offsetY);
		Buttons[i].cx = coords.x ;
		Buttons[i].cy = coords.y ;
		

	
	}


}

void isMouseInsideButton(ButtonComponent* mbutton, float mouseX, float mouseY)
{
	if (mouseX >= mbutton->cx && mouseX <= mbutton->cx + mbutton->width &&
		mouseY >= mbutton->cy && mouseY <= mbutton->cy + mbutton->height)
	{
		mbutton->isMouseInside = true;
		mbutton->width = 120;
		mbutton->height = 120;
	}
	else
	{
		mbutton->isMouseInside = false;
		mbutton->width = 100;
		mbutton->height = 100;
	}
}

void ButtonUpdate(ButtonComponent Buttons[], int num_buttons, float mouseX, float mouseY)
{
	//O(n)
	for (int i = 0; i < num_buttons; i++) {
		CP_Settings_ImageMode(CP_POSITION_CENTER);
		//check why the (Buttons[i].width / 2) onlhy works in update
		CP_Image_Draw(Buttons[i].sprite, Buttons[i].cx ,  Buttons[i].cy, Buttons[i].width, Buttons[i].height, 255);
		isMouseInsideButton(&Buttons[i], mouseX, mouseY);
		CP_Graphics_DrawCircle(Buttons[i].cx, Buttons[i].cy + (Buttons[i].height / 2), 10); //true drawing point since imageload loads from 

		if (Buttons[i].isMouseInside == true) {
			if (CP_Input_MouseClicked()) {
				printf("Button Clicked!\n");
			}
		}
	}


}

void ButtonShutdown()
{
	CP_Image_Free(nButton.sprite);
}

//void reset_button_ids() {
//	next_button_id = 0;
//}