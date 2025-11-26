
//---------------------------------------------------------
// file:	credits.h
// author:	[Quak June Hao (Quinn)]
// email:	[quak.j@digipen.edu]
//
// brief:	This code contains the scene for the tutorial section of the game
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

char moneyString[10];
char statisticString[100];
char statisticString2[100];
char clicker1Cost[100], clicker2Cost[100];
char troop1Cost[100], troop2Cost[100], troop3Cost[100];
extern float currentMoney, passiveIncome;
int clickerUpgrade1Count, clickerUpgrade2Count;
int troop1Count, troop2Count, troop3Count;

extern int purchaseCount;

/// <summary>
/// This function checks against your current money and an object cost 
/// Deducts it if you have enough
/// Rejects if not
/// </summary>
/// <param name="currentMoney"></param>
/// <param name="itemCost">insert cost of item here</param>
/// <returns>1 if possible to purchase, 0 if not</returns>
int Purchase_System(float* currentMoney, float itemCost);

/// <summary>
/// This function scales the cost of an object exponential according to a formula
/// </summary>
/// <param name="purchaseCount">How many times it has been bought before</param>
/// <param name="basePrice">the first original cost og the object</param>
/// <param name="scale">how much it scales by each time</param>
/// <returns></returns>
float Scaling_Cost(int purchaseCount, float basePrice, float scale);