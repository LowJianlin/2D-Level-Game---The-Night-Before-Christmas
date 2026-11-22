/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file Logo2.c
@author Gwen Leo YuhanYuhan(leo.y)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include "../mainmenu/mainmenu.h"

CP_Font font;
CP_Image credits_image;
CP_Image bgimage;
extern double fadeInTime;

void Logo2_Init(void){
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	font = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	bgimage = CP_Image_Load("Assets/background.jpg");
}

void Logo2_Update(void){

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
		CP_Engine_SetNextGameState(Main_Menu_Init,Main_Menu_Update, Main_Menu_Exit);
		fadeInTime = 0.0;
		return;
	}

	// Settings
	CP_Color Fontcolor= CP_Color_Create(255, 165, 0, 255);
	CP_Font_Set(font);

	// BG Color
	CP_Image_Draw(bgimage, center_x, center_y, 1920, 1080, 255);

	// Game Name
	CP_Settings_Fill(Fontcolor);
	CP_Settings_TextSize(80.0f);
	CP_Font_DrawText("The Night", center_x, 250.0f);
	CP_Font_DrawText("Before Christmas", center_x, 380.0f);
}

void Logo2_Exit(void){
}