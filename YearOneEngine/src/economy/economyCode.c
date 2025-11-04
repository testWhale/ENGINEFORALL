#include <cprocessing.h>

int Purchase_System(float *currentMoney,float itemCost)
	{
	if (*currentMoney >= itemCost)
		{
		*currentMoney -= itemCost;
		printf("Purchased");
		return 1;
		}
	else 
		{
		printf("Brokie");
		return 0;
		}
	}