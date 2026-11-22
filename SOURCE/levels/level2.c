/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file level2.c
@author Low JianLin (jianlin.low)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include <stdbool.h>
#include <stdio.h>
#include "../mainmenu/mainmenu.h"
#include "level2.h"
#include "lvl3.h"
#include "../utils/utils.h"

CP_Image P1_back, P1_front, P1_left, P1_right, P2_back, P2_front, P2_left, P2_right;
CP_Image P1_current, P2_current;

CP_Image Grinch_back, Grinch_front;
CP_Image Background, Heart, PresentP1, PresentP2;
CP_Font font_title, font_text;

//Global Variable
extern float player_w, player_h, grinch_size; // get these variables from main.c file
double startTime;
double elapsedTime;
extern int draw;

extern double fadeInTime;

extern bool LifeLostThisFrame;
extern int life[3];
extern int count;

extern float PresentP1X[6], PresentP1Y[6], PresentP2X[6], PresentP2Y[6];
extern int PresentP1Opacity[6], PresentP2Opacity[6];

double WinWidth = 1600.0f;
double WinHeight = 900.0f;

float p1_x = 775.0f, p1_y = 850.0f, p2_x = 825.0f, p2_y = 850.0f;

void Level2_Init(void) {
	p1_x = 775.0f, p1_y = 850.0f, p2_x = 825.0f, p2_y = 850.0f;

	//Set Present Count to 0
	count = 0;

	//Presents Opacity
	for (int i = 0; i < 6; i++) {
		PresentP1Opacity[i] = 255;
	}

	for (int i = 0; i < 6; i++) {
		PresentP2Opacity[i] = 255;
	}

	PresentP1 = CP_Image_Load("Assets/Gift-red.png");
	PresentP2 = CP_Image_Load("Assets/Gift-green.png");

	//Presents Positions
	for (int i = 0; i < 6; i++) {
		int overlap;
		do {
			overlap = 0;
			PresentP1X[i] = CP_Random_RangeFloat(37.5, 1562.5);
			PresentP1Y[i] = CP_Random_RangeFloat(180.0, 782);
			PresentP2X[i] = CP_Random_RangeFloat(37.5, 1562.5);
			PresentP2Y[i] = CP_Random_RangeFloat(180.0, 782);

			for (int j = 0; j < i; j++) {
				if (CheckOverlap(PresentP1X[i], PresentP1Y[i], PresentP1X[j], PresentP1Y[j]) ||
					CheckOverlap(PresentP2X[i], PresentP2Y[i], PresentP1X[j], PresentP1Y[j]) ||
					CheckOverlap(PresentP2X[i], PresentP2Y[i], PresentP2X[j], PresentP2Y[j])) {
					overlap = 1;
					break;
				}
			}
		} while (overlap);
	}

	//Player Graphics
	P1_back = CP_Image_Load("Assets/P1-Back.png");
	P1_front = CP_Image_Load("Assets/P1-Front.png");
	P1_left = CP_Image_Load("Assets/P1-Left.png");
	P1_right = CP_Image_Load("Assets/P1-Right.png");

	P2_back = CP_Image_Load("Assets/P2-Back.png");
	P2_front = CP_Image_Load("Assets/P2-Front.png");
	P2_left = CP_Image_Load("Assets/P2-Left.png");
	P2_right = CP_Image_Load("Assets/P2-Right.png");

	// Set default image for p1 p2
	P1_current = P1_front;
	P2_current = P2_front;

	//Grinch Graphics
	Grinch_back = CP_Image_Load("Assets/Grinch_Back.png");
	Grinch_front = CP_Image_Load("Assets/Grinch_Front.png");

	//Heart Graphics
	Heart = CP_Image_Load("Assets/Heart.png");

	//Background Graphics
	Background = CP_Image_Load("Assets/floor.jpg");

	// Font Settings
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	font_title = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	font_text = CP_Font_Load("Assets/font/ABeeZee-Regular.ttf");	

	// Rectangle Settings
	CP_Settings_RectMode(CP_POSITION_CENTER);

	//Time Interval
	startTime = CP_System_GetSeconds();
	draw = 0;
}

void Level2_Update(void) {

	//Settings
	CP_Color brown = CP_Color_Create(184, 136, 81, 255);
	CP_Color green = CP_Color_Create(34, 139, 34, 255);
	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);

	//Background
	CP_Image_Draw(Background, 800.0f, 450.0f, 1600, 900, 255);
	CP_Graphics_ClearBackground(brown);

	//Stage
	CP_Settings_StrokeWeight(3.0f); CP_Settings_Fill(black); CP_Graphics_DrawRect(800.0f, 67.5f, 1600.0f, 135.0f);
	//Door
	CP_Settings_StrokeWeight(3.0f); CP_Settings_Fill(white); CP_Graphics_DrawRect(550.0f, 67.5f, 110.0f, 135.0f);
	if (count == 12) {
		CP_Settings_StrokeWeight(3.0f); CP_Settings_Fill(green); CP_Graphics_DrawRect(550.0f, 67.5f, 110.0f, 135.0f);
	}

	//Count
	CP_Settings_Fill(white);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(200.0f, 875.0f, 395.0f, 45.0f);

	CP_Settings_Fill(black);
	CP_Font_Set(font_title);
	CP_Settings_TextSize(25.0f);
	char text[50];
	sprintf_s(text, sizeof(text), "Presents: %d/12", count);
	CP_Font_DrawText(text, 200.0f, 875.0f);

	//Timer
	timer(&startTime, &draw, 4.0, 1.0);

	// move p1 and p2 - Gwen
	move_playerLevel2(1, 'm', &p1_x, &p1_y, &P1_current, P1_front, P1_back, P1_left, P1_right);
	move_playerLevel2(2, 'm', &p2_x, &p2_y, &P2_current, P2_front, P2_back, P2_left, P2_right);

	//Presents Collected?
	for (int i = 0; i < 6; i++) {
		if (PresentsCollectedP1(p1_x, p1_y, PresentP1X[i], PresentP1Y[i]) == 1 && PresentP1Opacity[i] != 0) {
			PresentP1Opacity[i] = 0;
			count += 1;
		}

		if (PresentsCollectedP2(p2_x, p2_y, PresentP2X[i], PresentP2Y[i]) == 1 && PresentP2Opacity[i] != 0){
			PresentP2Opacity[i] = 0;
			count += 1;
		}
	}

	//Presents
	for (int i = 0; i < 6; i++) {
		CP_Image_Draw(PresentP1, PresentP1X[i], PresentP1Y[i], 75.0f, 75.0f, PresentP1Opacity[i]);
		CP_Image_Draw(PresentP2, PresentP2X[i], PresentP2Y[i], 75.0f, 75.0f, PresentP2Opacity[i]);
	}

	//Grinch Position
	if (draw == 0) {
		CP_Image_Draw(Grinch_back, 800.0f, 67.5f, grinch_size, grinch_size, 255);
	}
	else {
		CP_Image_Draw(Grinch_front, 800.0f, 67.5f, grinch_size, grinch_size, 255);
	}

	//Player Position
	CP_Image_Draw(P1_current, p1_x, p1_y, player_w, player_h, 255);
	CP_Image_Draw(P2_current, p2_x, p2_y, player_w, player_h, 255);

	//Heart Position
	CP_Image_Draw(Heart, 80.0f, 67.5f, 100.0f, 100.0f, life[0]);
	CP_Image_Draw(Heart, 190.0f, 67.5f, 100.0f, 100.0f, life[1]);
	CP_Image_Draw(Heart, 300.0f, 67.5f, 100.0f, 100.0f, life[2]);

	//Life Count
	if (draw == 1 && !LifeLostThisFrame){
		for (int i = 2; i >= 0; i--) {
			if (life[i] > 0 &&
				(CP_Input_KeyDown(KEY_W) == 1 || CP_Input_KeyDown(KEY_A) == 1 || CP_Input_KeyDown(KEY_S) == 1 || CP_Input_KeyDown(KEY_D) == 1 ||
					CP_Input_KeyDown(KEY_UP) == 1 || CP_Input_KeyDown(KEY_LEFT) == 1 || CP_Input_KeyDown(KEY_DOWN) == 1 || CP_Input_KeyDown(KEY_RIGHT) == 1)) {
				life[i] = 0;
				LifeLostThisFrame = true;
				break;
			}
		}
	}
	else if (draw == 0)
		LifeLostThisFrame = false;

	// draw instructions box
	CP_Settings_Fill(brown);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(1430.0f, 80.0f, 300.0f, 150.0f); //change by +30(x) -20(y)

	// draw instructions title
	CP_Settings_Fill(white);
	CP_Font_Set(font_title);
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText("Goal", 1440.0f, 40.0f);

	// draw instructions text
	CP_Font_Set(font_text);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("~Collect the presents", 1430.0f, 80.0f);
	CP_Font_DrawText("~DONT BE SEEN MOVING!", 1430.0f, 120.0f);

	// Location to next level - Shi Wei
	int giftct_p1 = 0;
	int giftct_p2 = 0;

	// Allow players to disappear and pass the top border if presents are all collected
	// Count amt of gifts each player collected
	for (int i = 0; i < 6; i++) {
		if (PresentP1Opacity[i] == 0) {
			giftct_p1++;
		}
		if (PresentP2Opacity[i] == 0) {
			giftct_p2++;
		}
	}

	// Teleports player to out of map if gifts collected equate to 6
	p1_y = ((giftct_p1 == 6) && (p1_x >= 495.0 && p1_x <= 605.0) && (p1_y <= 140.0f)) ? -100.0f : p1_y;
	p2_y = ((giftct_p2 == 6) && (p2_x >= 495.0 && p2_x <= 605.0) && (p2_y <= 140.0f)) ? -100.0f : p2_y;

	// If both players are above border, next game state
	if (count == 12 && p1_y < 0 && p2_y < 0) {
		int fade = 0;

		fadeInTime += CP_System_GetDt();

		if (fadeInTime < 2.0)
			fade = (int)(fadeInTime / 2.0 * 255);
		else fade = 255;

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, fade));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(800.0, 450.0, 1600.0, 900.0);

		if (fadeInTime >= 2.0) {
			CP_Engine_SetNextGameState(Lvl3_Init, Lvl3_Update, Lvl3_Exit);
			fadeInTime = 0.0;
			return;
		}
	}

	handlePlayerDeath();

	// back to main menu on esc press - Shi Wei
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Level2_Exit(void) {
	CP_Image_Free(&P1_back);
	CP_Image_Free(&P1_front);
	CP_Image_Free(&P1_left);
	CP_Image_Free(&P1_right);

	CP_Image_Free(&P2_back);
	CP_Image_Free(&P2_front);
	CP_Image_Free(&P2_left);
	CP_Image_Free(&P2_right);

	CP_Image_Free(&Grinch_back);
	CP_Image_Free(&Grinch_front);
	CP_Image_Free(&Heart);
	CP_Image_Free(&Background);

	CP_Image_Free(&PresentP1);
	CP_Image_Free(&PresentP2);
}
