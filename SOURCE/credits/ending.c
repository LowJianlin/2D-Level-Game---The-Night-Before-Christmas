/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file ending.c
@author Yar Xuan (xuan.yar)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include <stdio.h>
#include "credits.h"
#include "../utils/utils.h"

CP_Image EndingScene;
CP_Font font;

extern float game_start_time, game_complete_time;
extern double fadeInTime;
int startFade = 0;

void ending_init(void)
{
	EndingScene = CP_Image_Load("Assets/EndingScene.jpg");
	CP_Settings_ImageMode(CP_POSITION_CORNER);

	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	font = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	CP_Font_Set(font);

	game_complete_time = CP_System_GetSeconds();
	fadeInTime = 0.0;
	startFade = 0;
}

void ending_update(void)
{
	// draw background image
	CP_Image_Draw(EndingScene, 0, 0, 1600, 900, 255);
	
	// draw "show credits" text
	float center_x = (float) CP_System_GetWindowWidth() / 2;
	CP_Color yellow = CP_Color_Create(255, 255, 78, 255);
	CP_Settings_Fill(yellow);
	CP_Settings_TextSize(30.0f);
	CP_Font_DrawText("Show Credits", center_x, 500.0f);

	// don't show game completion timing if player did not go through level 1
	// meaning player went through level select and didn't play through all 4 levels
	if (game_start_time != 0.0f) {
		// calculate completion timing
		float completion_timing = game_complete_time - game_start_time;
		int minutes = (int) completion_timing / 60;
		int seconds = (int)completion_timing - (minutes * 60);

		// draw completion timing text
		CP_Color white = CP_Color_Create(255, 255, 255, 255);
		CP_Settings_Fill(white);
		CP_Settings_TextSize(25.0f);
		char text[50];
		sprintf_s(text, sizeof(text), "You completed the game in %d minutes, %d seconds!", minutes, seconds);
		CP_Font_DrawText(text, center_x, 450.0f);
	}

	// if player clicked on "show credits" text
	if (CP_Input_MouseClicked() && IsAreaClicked(center_x, 500.0f, 540.0f, 30.0f, CP_Input_GetMouseX(), CP_Input_GetMouseY())) {
		startFade = 1;
	}

	if (startFade) {
		int fade = 0;
		fadeInTime += CP_System_GetDt();

		if (fadeInTime < 2.0)
			fade = (int)(fadeInTime / 2.0 * 255);
		else fade = 255;
	
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, fade));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(800.0, 450.0, 1600.0, 900.0);

		if (fadeInTime >= 2.0) {
			CP_Engine_SetNextGameState(credits_Init, credits_Update, credits_Exit);
			fadeInTime = 0.0;
			startFade = 0;
		}
	}
}

void ending_exit(void) {
	CP_Image_Free(&EndingScene);
	CP_Settings_ImageMode(CP_POSITION_CENTER);
}
