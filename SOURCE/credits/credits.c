/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file credits.c
@author Gwen Leo Yuhan(leo.y)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include "credits2.h"

CP_Image credits1;
extern double fadeInTime;

void credits_Init(void) {
	credits1 = CP_Image_Load("Assets/credits1.jpg");
}

void credits_Update(void) {
	// Point to be in the Center of Rectangle
	float center_x = CP_System_GetWindowWidth() / 2.0f;
	float center_y = CP_System_GetWindowHeight() / 2.0f;

	int fade = 0;
	fadeInTime += CP_System_GetDt();

	if (fadeInTime < 3.0)
		fade = (int)(fadeInTime / 2.0 * 255);
	else fade = 255;

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, fade));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(800.0, 450.0, 1600.0, 900.0);

	if (fadeInTime >= 3.0) {
		CP_Engine_SetNextGameState(credits2_Init, credits2_Update, credits2_Exit);
		fadeInTime = 0.0;
		return;
	}

	// BG Color
	CP_Image_Draw(credits1, center_x, center_y, 1920, 1080, 255);
}

void credits_Exit(void) {

}