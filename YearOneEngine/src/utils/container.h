#ifndef CONTAINER_H
#define CONTAINER_H
typedef struct {
	int id;
	char* name;
	CP_Vector centerPos;
	int width;
	int height;
	CP_Image bg;
	char* bg_filepath;
} Container;

Container CONTAINERS[2];

void Container_Init(Container* contain);
void Container_Update(Container* contain);
void Container_Destroy(Container* contain);

#endif