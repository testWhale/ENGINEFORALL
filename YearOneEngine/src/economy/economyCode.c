//---------------------------------------------------------
// file:	credits.h
// author:	[Quak June Hao (Quinn)]
// email:	[quak.j@digipen.edu]
//
// brief:	This code contains the scene for the tutorial section of the game
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#include <cprocessing.h>
#include <math.h>

currentMoney = 0;

int Purchase_System(float *currentMoney,float itemCost)
	{
	if (*currentMoney >= itemCost)
		{
		*currentMoney -= itemCost;
		return 1;
		}
	else 
		{
		return 0;
		}
	}



float Scaling_Cost(int purchaseCount, float basePrice, float scale)
{
	return basePrice * pow(scale, (double)purchaseCount);
}
