//---------------------------------------------------------
// file:	clickCode.h
// author:	[Quak June Hao (Quinn)]
// email:	[quak.j@digipen.edu]
//
// brief:	This code contains the scene for the tutorial section of the game
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------

#ifndef clickCode_H
#define clickCode_H



extern int clickPower;
extern float OneCountdown,passiveIncome;


/// <summary>
/// earn money from one click
/// </summary>
/// <param name="currentMoney"></param>
void One_Click(float* currentMoney);

void Reward_Click(float* currentMoney); /* Zac added */

/// <summary>
/// earn money on a passive basis
/// </summary>
/// <param name="currentMoney"></param>
void Passive_System(float* currentMoney);

/// <summary>
/// Upgrades the One Click function
/// </summary>
void Click_Upgrade();

/// <summary>
///this Upgrades your passive system

/// </summary>
void Passive_Upgrade();

#endif