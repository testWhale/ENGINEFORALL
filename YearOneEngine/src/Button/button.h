#include "cprocessing.h"

typedef struct buttonInfo {
    CP_Vector buttonPos;
    float buttonWidth, buttonHeight, buttonDiameter;
    CP_Image buttonNormal, buttonFeedback, buttonHighlight;
    int isSel, isClicked;
}buttonInfo;


void buttonLoad(buttonInfo* newbtn, float posX, float posY, float width, float height, float diameter, const char* buttonNormalPath, const char* buttonFeedbackPath, const char* buttonHighlightPath); 	//this loads the button data from the computer
//this loads the button data from the computer

void drawButtonNormal(buttonInfo* btnname);
void drawButtonFeedback(buttonInfo* btnname);
void drawButtonHighlight(buttonInfo* btnname);

//int isSquareButtonHovered(buttonInfo* btnname, float mousex, float mousey);
//int isCircleButtonHovered(buttonInfo* btnname, float mousex, float mousey);
int isAnyButtonHovered(buttonInfo* btnname, float mousex, float mousey);
int isButtonPressed(buttonInfo* btnname, int isHovered);
int isButtonReleased(buttonInfo* btnname, int isHovered);

void buttonBehavior(buttonInfo* btnname);