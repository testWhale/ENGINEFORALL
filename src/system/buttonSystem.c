#include "cprocessing.h"
#include "buttonSystem.h"

ButtonComponent nButton;
// Static counter for automatic ID assignment
static int next_button_id = 0;

void ButtonInit(ButtonComponent Buttons[], int num_buttons, float win_width, float win_height)
{
	for (int i = 0; i < num_buttons; i++) {
		buttons[i].id = i;
		buttons[i].sprite = CP_Image_Load("Assets/DigiPen_Singapore_WEB_BLACK.png");
		buttons[i].width = 100;
		buttons[i].height = 100;
		buttons[i].cx = 200.0f + i * 150.0f; // Example positioning
	}
	nButton.id = next_button_id++;
	nButton.sprite = CP_Image_Load("Assets/DigiPen_Singapore_WEB_BLACK.png");
	if (nButton.sprite == NULL)
	{
		printf("Failed to load image\n");
	}

}

void isMouseInsideButton(ButtonComponent* button,float mouseX, float mouseY)
{
	if (mouseX >= nButton.cx && mouseX <= nButton.cx + nButton.width &&
		mouseY >= nButton.cy && mouseY <= nButton.cy + nButton.height)
	{
		nButton.isMouseInside = true;
		nButton.width = 120;
		nButton.height = 120;
	}
	else
	{
		nButton.isMouseInside = false;
		nButton.width = 100;
		nButton.height = 100;
	}
}

void ButtonUpdate(ButtonComponent Buttons[], int num_buttons, float mouseX, float mouseY)
{
	//O(n)
	for (int i = 0; i < num_buttons; i++) {
		CP_Image_Draw(Buttons[i].sprite, Buttons[i].cx, Buttons[i].cy, Buttons[i].width, Buttons[i].height, 255);
		isMouseInsideButton(&Buttons[i],mouseX, mouseY);

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