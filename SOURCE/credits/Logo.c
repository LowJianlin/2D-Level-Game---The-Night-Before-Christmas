/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file Logo.c
@author Gwen Leo Yuhan(leo.y)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include "Logo2.h"

CP_Image credits_image;
CP_Image bgimage;
extern double fadeInTime;

void Logo_Init(void){
	credits_image = CP_Image_Load("Assets/Logo.jpg");
}

void Logo_Update(void){

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
		CP_Engine_SetNextGameState(Logo2_Init, Logo2_Update, Logo2_Exit);
		fadeInTime = 0.0;
		return;
	}

	// BG Color
	CP_Image_Draw(credits_image, center_x, center_y, 1600, 900, 255);
}

void Logo_Exit(void){}