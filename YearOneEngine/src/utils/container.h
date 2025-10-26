#ifndef CONTAINER_H
#define CONTAINER_H
#include "cprocessing.h"

/*Container H just scales the container to the screen size, draws the container, and frees it.
The code that activates its specific states is inside of /backend*/
typedef struct {
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
ContArr ContArr_Init(size_t maxLength, ContArr* Array);
void ContArr_Insert(ContArr* Array, Container container);
void ContArr_Free(ContArr* Array);

/*Declarations Container Code*/
void Container_Init(Container* container); /*scales the container to the screen and user inputed scale factor */
void Container_Draw(Container* container); /*takes the width and height and draws */
void Container_Destroy(Container* container); /*frees Image from Container */

/*Declarations Get Specific Container*/
Container* getContainer(char* label, ContArr* Array);

ContArr containersArr;
#endif