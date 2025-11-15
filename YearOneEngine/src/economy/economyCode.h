char moneyString[10];
char statisticString[100];
char statisticString2[100];
char clicker1Cost[100], clicker2Cost[100];
char troop1Cost[100], troop2Cost[100], troop3Cost[100];
extern float currentMoney, passiveIncome;
int clickerUpgrade1Count, clickerUpgrade2Count;
int troop1Count, troop2Count, troop3Count;


int Purchase_System(float* currentMoney, float itemCost);
void Poor_Feedback(float fontsize, float PosX, float PosY);
float Scaling_Cost(int purchaseCount, float basePrice);