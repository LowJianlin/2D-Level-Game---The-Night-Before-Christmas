/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file mainmenu.c
@author Gwen Leo Yuhan(leo.y)
*//*______________________________________________________________________*/

#include "mainmenu.h"
#include "cprocessing.h"
#include "instructions.h"
#include "../credits/credits.h"
#include "../utils/utils.h"
#include "../mainmenu/cutscene.h"

CP_Font myfont;
CP_Image BGimage = NULL;
int transitioning = 0; // Flag to check if fading is in progress
float alpha = 0.0f; // Transparency value for fade effect
extern int life[];

void Main_Menu_Init(void)
{
	myfont = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	BGimage = CP_Image_Load("Assets/background.jpg");
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	// Initialize fade variables
	transitioning = 0;
	alpha = 0.0f;

	// reset life to max health
	for (int i = 0; i <= 2; i++) {
		life[i] = 255;
	}
}

void Main_Menu_Update(void)
{
	
	// Point to be in the Center of Rectangle
	float center_x = CP_System_GetWindowWidth() / 2.0f;
	float center_y = CP_System_GetWindowHeight() / 2.0f;

	// Color Settings
	CP_Color Fontcolor_PLAY = CP_Color_Create(255, 165, 0, 255);
	CP_Color Fontcolor = CP_Color_Create(255, 255, 78, 255);

	// BG Color
	CP_Image_Draw(BGimage, center_x, center_y, 1920, 1080, 255);

	// PLAY BUTTON
	// font color
	CP_Font_Set(myfont);
	CP_Settings_Fill(Fontcolor_PLAY);
	CP_Settings_TextSize(90.0f);
	CP_Font_DrawText("START GAME", center_x, 195.0f);

	// INSTRUCTIONS BUTTON
	// font color
	CP_Font_Set(myfont);
	CP_Settings_Fill(Fontcolor);
	CP_Settings_TextSize(40.0f);
	CP_Font_DrawText("How To Play", center_x, 290.0f);

	// CREDITS BUTTON
	// font
	CP_Font_Set(myfont);
	CP_Settings_Fill(Fontcolor);
	CP_Settings_TextSize(40.0f);
	CP_Font_DrawText("Credits", center_x, 370.0f);

	// EXIT BUTTON
	// font color 
	CP_Settings_Fill(Fontcolor);
	CP_Settings_TextSize(40.0f);
	CP_Font_DrawText("Exit", center_x, 450.0f);

	if (!transitioning) {
		// PLAY GAME button
		if (IsAreaClicked(center_x, 200.0f, 720.0f, 100.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked())
		{
			transitioning = 1; // Start fading effect
		}
		// INSTRUCTIONS button
		else if (IsAreaClicked(center_x, 290.0f, 500.0f, 60.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(instructions_Init, instructions_Update, instructions_Exit);
		}
		// CREDITS button
		else if (IsAreaClicked(center_x, 370.0f, 300.0f, 60.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked())
		{
			CP_Engine_SetNextGameState(credits_Init, credits_Update, credits_Exit);
		}
		// EXIT button
		else if (IsAreaClicked(center_x, 450.0f, 180.0f, 60.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked())
		{
			CP_Engine_Terminate();
		}
	}
	else
	{
		// Fading logic
		alpha += 255.0f * CP_System_GetDt(); // Increase alpha value over time
		if (alpha >= 255.0f)
		{
			alpha = 255.0f;
			CP_Engine_SetNextGameState(cutscene_Init, cutscene_Update, cutscene_Exit); // Transition to Level 1
		}

		// Draw the fade-to-black effect
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)alpha));
		CP_Graphics_DrawRect(center_x, center_y, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());
	}
}

void Main_Menu_Exit(void)
{
	// Cleanup resources
	CP_Image_Free(&BGimage);
}