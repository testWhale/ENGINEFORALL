#include <stdio.h>
#include "container.h"
#include "readTxt.h"
#define _countof(arr) (sizeof(arr) / sizeof((arr)[0]))

void readFile(char* filePath) {
    FILE* f = fopen("C:/Users/uyait/source/GAM100/GAM100_ENGINE/YearOneEngine/src/containers.txt", "r");
    Container c; 
    while (fscanf_s(f, "%d %100s { %f,%f } %d %d %100s %f %f %d",
        &c.id, c.label, (unsigned)_countof(c.label),
        &c.leftTopPos.x, &c.leftTopPos.y,
        &c.width, &c.height,
        c.bg_filepath, (unsigned)_countof(c.bg_filepath),
        &c.scale_factor, &c.opacity, &c.animate, &c.stateTimer)==10)
    {
  /*      printf("\n%d %63s { %f,%f } %d %d %127s %f %f %d\n",
            c.id, c.label,
            c.leftTopPos.x, c.leftTopPos.y,
            c.width, &c.height,
            c.bg_filepath,
            c.scale_factor, c.opacity, c.animate);*/
        Container_Init(&c);
        ContArr_Insert(&containersArr,c);
    }
    printf("RUNINFK");
    fclose(f);
}