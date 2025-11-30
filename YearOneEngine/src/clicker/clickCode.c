//---------------------------------------------------------
// file:	clickCode.c
// author:	[Quak June Hao (Quinn)][Zachary Ng]
// email:	[quak.j@digipen.edu][zacharyhuaen.n@digipen.edu]
//
// brief:	This code contains behavior for the clicker system
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------



#include "cprocessing.h"
#include "clickCode.h"
#include <math.h>
#include <time.h>
#include <stdlib.h> 

clickPower = 1;
clickPurchaseAmount = 0;
float OneCountdown = 1.0f;
float passiveIncome = 0;


//this function generates money from one click
void One_Click(float* currentMoney) 
{
	*currentMoney += clickPower;
}


void Reward_Click(float* currentMoney) {
	int rndm = rand() % 10;
	*currentMoney += rndm;
}

void Click_Upgrade() {
	clickPower += 1;
}

void Passive_Upgrade() {
	passiveIncome += 10;
}

void Passive_System(float* currentMoney)
{
	OneCountdown -= CP_System_GetDt();
	if (OneCountdown <= 0.0f) 
	{
		*currentMoney += passiveIncome;
		OneCountdown = 1.0f;
	}
}

////int ClickCost() 
//{
//	clickUpgradeCost = 50 * (1.15 *clickPurchaseAmount);
//}
