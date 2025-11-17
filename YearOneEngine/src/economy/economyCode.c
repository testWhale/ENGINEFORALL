#include <cprocessing.h>
#include <math.h>

currentMoney = 10000;
float timer = 2;

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

void Poor_Feedback(float fontsize,float PosX, float PosY)
{ 
	timer -= CP_System_GetDt();
	if (timer >0.0f)
	{
		CP_Settings_TextSize(fontsize);
		CP_Font_DrawText("YOURE POOR", PosX, PosY);
	}
	if (timer <= 0)
	{
		timer = 2;
	}
}

float Scaling_Cost(int purchaseCount, float basePrice)
{
	return basePrice * pow(1.75, (double)purchaseCount);
}