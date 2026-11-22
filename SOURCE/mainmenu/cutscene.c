/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file cutscene.c
@author Gwen Leo Yuhan(leo.y)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include "mainmenu.h"
#include "cutscene.h"
#include "../levels/level1.h"
#include "../levels/level2.h"
#include "../levels/lvl3.h"
#include "../levels/level4.h"
#include "../utils/utils.h"

CP_Font font, text_font;
CP_Image BG_image = NULL;
int Transitioning = 0; // Flag to check if fading is in progress
float Alpha = 0.0f; // Transparency value for fade effect

void cutscene_Init(void) {

	// Uploads
	font = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	text_font = CP_Font_Load("Assets/font/ABeeZee-Regular.ttf");
	BG_image = CP_Image_Load("Assets/background.jpg");

	// Allignment Settings
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Settings_ImageMode(CP_POSITION_CENTER);

	// Initialize fade variables
	Transitioning = 0;
	Alpha = 0.0f;

}

void cutscene_Update(void) {

	// Point to be in the Center of Rectangle
	float center_x = CP_System_GetWindowWidth() / 2.0f;
	float center_y = CP_System_GetWindowHeight() / 2.0f;

	// BG Color
	CP_Image_Draw(BG_image, center_x, center_y, 1920, 1080, 255);
	CP_Color Box_color = CP_Color_Create(184, 136, 81, 255);
	CP_Color title_color = CP_Color_Create(255, 165, 0, 255);
	CP_Color text_color = CP_Color_Create(255, 255, 255, 255);
	CP_Color buttoncolor = CP_Color_Create(255, 255, 78, 255);

	// Context
	CP_Font_Set(font);
	CP_Settings_Fill(title_color);
	CP_Settings_TextSize(50.0f);
	CP_Font_DrawText("THE NIGHT BEFORE CHRISTMAS", center_x, 195.0f);

	// font color
	CP_Font_Set(font);
	CP_Settings_Fill(text_color);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("It is the NIGHT BEFORE CHRISTMAS,", center_x, 290.0f);
	CP_Font_DrawText("the Grinch has stolen the town's presents.", center_x, 340.0f);
	CP_Font_DrawText("Help retrieve the presents and", center_x, 400.0f);
	CP_Font_DrawText("save Christmas!", center_x, 450.0f);

	// font color
	CP_Font_Set(font);
	CP_Settings_Fill(buttoncolor);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Select:", center_x, 550.0f);

	// Code to create a test on telling the user to return to main menu
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Settings_Fill(white);
	CP_Font_Set(font);
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText("Press 'ESC' to return to Main Menu", 400.0f, 40.0f);

	// Level 1 Box Color
	CP_Settings_Fill(Box_color);
	CP_Graphics_DrawRect(350.0f, 650.0f, 250.0f, 60.0f);
	// Button
	CP_Font_Set(font);
	CP_Settings_Fill(buttoncolor);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Level 1", 350.0f, 650.0f);

	// Level 2 Box Color
	CP_Settings_Fill(Box_color);
	CP_Graphics_DrawRect(650.0f, 650.0f, 250.0f, 60.0f);
	// Button
	CP_Font_Set(font);
	CP_Settings_Fill(buttoncolor);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Level 2", 650.0f, 650.0f);

	
	// Level 3 Box Color
	CP_Settings_Fill(Box_color);
	CP_Graphics_DrawRect(950.0f, 650.0f, 250.0f, 60.0f);
	// Button
	CP_Font_Set(font);
	CP_Settings_Fill(buttoncolor);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Level 3", 950.0f, 650.0f);

	// Level 4 Box Color
	CP_Settings_Fill(Box_color);
	CP_Graphics_DrawRect(1250.0f, 650.0f, 250.0f, 60.0f);
	// Button
	CP_Font_Set(font);
	CP_Settings_Fill(buttoncolor);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Level 4", 1250.0f, 650.0f);

	if (!Transitioning) {
		if (CP_Input_MouseClicked()) {
			// Level 1 button
			if (IsAreaClicked(350.0f, 650.0f, 250.0f, 60.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				Transitioning = 1; // Start fading effect
			}
			// Level 2 button
			else if (IsAreaClicked(650.0f, 650.0f, 250.0f, 60.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				CP_Engine_SetNextGameState(Level2_Init, Level2_Update, Level2_Exit);
			}
			// Level 3 button
			else if (IsAreaClicked(950.0f, 650.0f, 250.0f, 60.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				CP_Engine_SetNextGameState(Lvl3_Init, Lvl3_Update, Lvl3_Exit);
			}
			// Level 4 button
			else if (IsAreaClicked(1250.0f, 650.0f, 250.0f, 60.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY()))
			{
				CP_Engine_SetNextGameState(Level4_init, Level4_update, Level4_exit);
			}
		}
	}
	else
	{
		// Fading logic
		Alpha += 255.0f * CP_System_GetDt(); // Increase alpha value over time
		if (Alpha >= 255.0f)
		{
			Alpha = 255.0f;
			CP_Engine_SetNextGameState(level1_Init, level1_Update, level1_Exit); // Transition to Level 1
		}

		// Draw the fade-to-black effect
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)Alpha));
		CP_Graphics_DrawRect(center_x, center_y, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());
	}

	// back to main menu on esc press - Shi Wei
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}


void cutscene_Exit(void) {
}