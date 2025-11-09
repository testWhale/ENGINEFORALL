#include "cprocessing.h"
#include "clickCode.h"
#include <math.h>
#include <time.h>

clickPower = 1;
clickPurchaseAmount = 0;
FiveCountdown = 5.0f;
passiveIncome = 0;

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
	passiveIncome += 1;
}

void Passive_System(float* currentMoney)
{
	FiveCountdown -= CP_System_GetDt();
	if (FiveCountdown <= 0.0f) 
	{
		*currentMoney += passiveIncome;
		FiveCountdown = 5.0;
	}
}

////int ClickCost() 
//{
//	clickUpgradeCost = 50 * (1.15 *clickPurchaseAmount);
//}
