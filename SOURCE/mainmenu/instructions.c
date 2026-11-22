/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file instructions.c
@author Gwen Leo Yuhan(leo.y)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include <stdio.h>
#include "mainmenu.h"
#include "../utils/utils.h"

CP_Font title_font;
CP_Font text_font;

void instructions_Init(void)
{
	title_font = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	text_font = CP_Font_Load("Assets/font/ABeeZee-Regular.ttf");
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_RectMode(CP_POSITION_CENTER);
}

void instructions_Update(void)
{
	// SETTINGS
	CP_Color BGcolor = CP_Color_Create(26, 28, 44, 255);
	CP_Graphics_ClearBackground(BGcolor);
	CP_Color Fontcolor_Title = CP_Color_Create(255, 165, 0, 255);
	CP_Color Exit_title_color = CP_Color_Create(255, 255, 78, 255);
	CP_Color Box_color = CP_Color_Create(184,136,81,255);
	CP_Color Fontcolor_box = CP_Color_Create(0, 0, 0, 255);
	CP_Color controls_color = CP_Color_Create(255, 255, 255, 255);

	// Point to be in the Center of Rectangle
	float center_x = CP_System_GetWindowWidth() / 2.0f;
	float center_y = CP_System_GetWindowHeight() / 2.0f;

	// HOW TO PLAY - title
	CP_Font_Set(title_font);
	CP_Settings_Fill(Fontcolor_Title);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("HOW TO PLAY", center_x, 70.0f);

	// controls
	CP_Font_Set(title_font);
	CP_Settings_Fill(controls_color);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("To move UP, DOWN, LEFT, and RIGHT:", center_x, 140.0f);
	CP_Font_DrawText("Player 1 = WASD Keys, Player 2 = Arrow Keys", center_x, 200.0f);

	// LEVEL 1 BOX
	CP_Settings_Fill(Box_color);
	CP_Graphics_DrawRect(400.0f, 370.0f, 700.0f, 250.0f);
	// Title 
	CP_Font_Set(title_font);
	CP_Settings_Fill(Exit_title_color);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Level 1", 400.0f, 290.0f);
	// Text
	CP_Font_Set(text_font);
	CP_Settings_Fill(Fontcolor_box);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Players have to collect presents based on their", 400.0f, 350.0f);
	CP_Font_DrawText("respective color and enter the Grinch's house.", 400.0f, 400.0f);

	// LEVEL 3 BOX
	CP_Settings_Fill(Box_color);
	CP_Graphics_DrawRect(400.0f, 650.0f, 700.0f, 250.0f);
	// Title 
	CP_Font_Set(title_font);
	CP_Settings_Fill(Exit_title_color);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Level 3", 400.0f, 570.0f);
	// Text
	CP_Font_Set(text_font);
	CP_Settings_Fill(Fontcolor_box);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Players have to collect presents from various rooms", 400.0f, 610.0f);
	CP_Font_DrawText("while avoiding the Grinch in the hallway,", 400.0f, 660.0f);
	CP_Font_DrawText("and safely escape through the door.", 400.0f, 710.0f);

	// LEVEL 2 BOX
	CP_Settings_Fill(Box_color);
	CP_Graphics_DrawRect(1200.0f, 370.0f, 700.0f, 250.0f);
	// Title 
	CP_Font_Set(title_font);
	CP_Settings_Fill(Exit_title_color);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Level 2", 1200.0f, 290.0f);
	// Text
	CP_Font_Set(text_font);
	CP_Settings_Fill(Fontcolor_box);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Players have to collect the presents while", 1200.0f, 330.0f);
	CP_Font_DrawText("Grinch is turned away.", 1200.0f, 380.0f);
	CP_Font_DrawText("Once done, players have to escape through the door.", 1200.0f, 430.0f);

	// LEVEL 4 BOX
	CP_Settings_Fill(Box_color);
	CP_Graphics_DrawRect(1200.0f, 650.0f, 700.0f, 250.0f);
	// Title 
	CP_Font_Set(title_font);
	CP_Settings_Fill(Exit_title_color);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Level 4", 1200.0f, 570.0f);
	// Text
	CP_Font_Set(text_font);
	CP_Settings_Fill(Fontcolor_box);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("To complete the final level, players have to", 1200.0f, 610.0f);
	CP_Font_DrawText("navigate their way in the dark while avoid getting", 1200.0f, 660.0f);
	CP_Font_DrawText("caught to reach the door at the end of the hallway.", 1200.0f, 710.0f);

	// font color
	CP_Font_Set(title_font);
	CP_Settings_Fill(Exit_title_color);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("BACK", center_x, 840.0f);

	if (IsAreaClicked(center_x, 840.0f, 180.0f, 80.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()) && CP_Input_MouseClicked()) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void instructions_Exit(void){
}