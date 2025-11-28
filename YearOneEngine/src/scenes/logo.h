//---------------------------------------------------------
// file:	logo.h
// author:	[Zachary Ng]
// email:	zacharyhuaen.n@digipen.edu
//
// brief:	Declares the logo splash screen helpers.
//
// Copyright 2025 DigiPen, All rights reserved.
//---------------------------------------------------------
#ifndef LOGO_H
#define LOGO_H

/* Logo_Init()
Input:
    None
Output:
    void
Brief:
    Resets the timer and loads the logo image.
*/
void Logo_Init(void);

/* Logo_Update()
Input:
    None
Output:
    void
Brief:
    Advances the fade, draws the logo, and transitions to the main menu.
*/
void Logo_Update(void);

/* Logo_Exit()
Input:
    None
Output:
    void
Brief:
    Frees the logo texture.
*/
void Logo_Exit(void);

#endif