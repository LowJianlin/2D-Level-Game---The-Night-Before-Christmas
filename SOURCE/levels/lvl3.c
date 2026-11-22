/*!
* © 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file       lvl3.c
@author     Beh Shi Wei (beh.s)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include <stdbool.h>
#include <stdio.h>
#include "../utils/map_utils.h"
#include "../utils/utils.h"
#include "../mainmenu/mainmenu.h"
#include "level4.h"

CP_Image heart;
CP_Image bg_floor;
CP_Image grinch_up;		CP_Image grinch_down;
CP_Image grinch_left;	CP_Image grinch_right;

CP_Image CurrentImage_Player_1; // The image currently displayed
CP_Image CurrentImage_Player_2; // The image currently displayed
CP_Image CurrentImageGrinch;

CP_Image p1_up;			CP_Image p1_down;
CP_Image p1_left;		CP_Image p1_right;

CP_Image p2_up;			CP_Image p2_down;
CP_Image p2_left;		CP_Image p2_right;
CP_Image PresentP1, PresentP2;
CP_Font font, font_text;

extern float PresentP1X[6], PresentP1Y[6], PresentP2X[6], PresentP2Y[6];
extern int PresentP1Opacity[6], PresentP2Opacity[6];
extern int count;

extern float player_w, player_h, grinch_size; // get these variables from main.c file
extern int draw;
extern double fadeInTime;
extern bool LifeLostThisFrame;
extern int life[3];

float dt;
float p1speed, p2speed;
float p1_x, p1_y;	float p2_x, p2_y;
float grinch_x, grinch_y;
float grinch_speed;
float dt;
float temp; // for lvl 3 wall collision
// path points for grinch movement
int path[][2] = { {735, 0}, {735, 650}, {735, 0} };
int pathPoint = 0;
float last_collide_time;

void Lvl3_Init(void)
{
	LifeLostThisFrame = false;
	// Set Presents Count to 0
	count = 0;

	// Presents Opacity
	for (int i = 0; i < 6; i++) {
		PresentP1Opacity[i] = 255;
	}

	for (int i = 0; i < 6; i++) {
		PresentP2Opacity[i] = 255;
	}

	// generate random positions for presents (3 in each room, 1/2 per player per room)
	// top left room (3 presents for p1) - JianLin
	for (int i = 0; i < 3; i++) {
		int overlap;
		do {
			overlap = 0;
			PresentP1X[i] = CP_Random_RangeFloat(230.0f, 550.0f);
			PresentP1Y[i] = CP_Random_RangeFloat(130.0f, 400.0f);

			for (int j = 0; j < i; j++) {
				if (CheckOverlap(PresentP1X[i], PresentP1Y[i], PresentP1X[j], PresentP1Y[j])) {
					overlap = 1;
					break;
				}
			}
		} while (overlap);
	}

	// bottom left room (3 presents for p2) - JianLin
	for (int i = 0; i < 3; i++) {
		int overlap;
		do {
			overlap = 0;
			PresentP2X[i] = CP_Random_RangeFloat(200.0f, 550.0f);
			PresentP2Y[i] = CP_Random_RangeFloat(600.0f, 750.0f);

			for (int j = 0; j < i; j++) {
				if (CheckOverlap(PresentP2X[i], PresentP2Y[i], PresentP2X[j], PresentP2Y[j])) {
					overlap = 1;
					break;
				}
			}
		} while (overlap);
	}

	// top right room (3 presents for p2) - JianLin
	for (int i = 3; i < 6; i++) {
		int overlap;
		do {
			overlap = 0;
			PresentP2X[i] = CP_Random_RangeFloat(960.0f, 1300.0f);
			PresentP2Y[i] = CP_Random_RangeFloat(120.0f, 400.0f);

			for (int j = 0; j < i; j++) {
				if (CheckOverlap(PresentP2X[i], PresentP2Y[i], PresentP2X[j], PresentP2Y[j])) {
					overlap = 1;
					break;
				}
			}
		} while (overlap);
	}

	// bottom right room (3 presents for p1) - JianLin
	for (int i = 3; i < 6; i++) {
		int overlap;
		do {
			overlap = 0;
			PresentP1X[i] = CP_Random_RangeFloat(960.0f, 1300.0f);
			PresentP1Y[i] = CP_Random_RangeFloat(610.0f, 750.0f);

			for (int j = 0; j < i; j++) {
				if (CheckOverlap(PresentP1X[i], PresentP1Y[i], PresentP1X[j], PresentP1Y[j])) {
					overlap = 1;
					break;
				}
			}
		} while (overlap);
	}

	float window_w = (float) CP_System_GetWindowWidth();
	float window_h = (float) CP_System_GetWindowHeight();
	float center_w = window_w / 2;
	float center_h = window_h / 2;

	// Background
	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));

	// Font type
	font = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	font_text = CP_Font_Load("Assets/font/ABeeZee-Regular.ttf");
	CP_Font_Set(font);
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);

	// Load hearts image files
	heart = CP_Image_Load("Assets/Heart.png");

	// Load presents images
	PresentP1 = CP_Image_Load("Assets/Gift-red.png");
	PresentP2 = CP_Image_Load("Assets/Gift-green.png");

	// Grinch info
	grinch_up = CP_Image_Load("Assets/Grinch_Back.png");	grinch_down = CP_Image_Load("Assets/Grinch_Front.png");
	grinch_left = CP_Image_Load("Assets/Grinch_Left.png");	grinch_right = CP_Image_Load("Assets/Grinch_Right.png");
	grinch_x = center_w - grinch_size / 2;					grinch_y = 0.0f;
	CurrentImageGrinch = grinch_down;

	// Player 1 info
	p1_up = CP_Image_Load("Assets/P1-Back.png");			p1_down = CP_Image_Load("Assets/P1-Front.png");
	p1_left = CP_Image_Load("Assets/P1-Left.png");			p1_right = CP_Image_Load("Assets/P1-Right.png");
	p1_x = center_w - player_w - 10;							p1_y = window_h - player_h;
	CurrentImage_Player_1 = p1_down;

	// Player 2 info
	p2_up = CP_Image_Load("Assets/P2-Back.png");			p2_down = CP_Image_Load("Assets/P2-Front.png");
	p2_left = CP_Image_Load("Assets/P2-Left.png");			p2_right = CP_Image_Load("Assets/P2-Right.png");
	p2_x = center_w + 10;											p2_y = window_h - player_h;
	CurrentImage_Player_2 = p2_down;

	// Mapping
	bg_floor = CP_Image_Load("Assets/floor.jpg");
	CP_Settings_ImageWrapMode(CP_IMAGE_WRAP_CLAMP);
}


void Lvl3_Update(void) // every frame
{
	float window_w = (float) CP_System_GetWindowWidth();
	float window_h = (float) CP_System_GetWindowHeight();
	float center_w = window_w / 2;
	float center_h = window_h / 2;
	grinch_speed = 200.0f * CP_System_GetDt();

	CP_Graphics_ClearBackground(CP_Color_Create(0, 0, 0, 255));
	CP_Color black = CP_Color_Create(0, 0, 0, 255);

	// Map design - corridor
	float aisle = CP_System_GetWindowHeight() - 30.0f;
	CP_Graphics_DrawRect(window_w, window_h, 50.0f, aisle);

	int p1_colliding_wall = lvl3_wall_collision(1, p1_x, p1_y);
	int p2_colliding_wall = lvl3_wall_collision(2, p2_x, p2_y);

	// move_player function from utils.c - Gwen
	// if player next movement will collide with wall, give temp var as x and y 
	// so that it doesn't actually change the player x y values
	move_player(1, 'c', p1_colliding_wall ? &temp : &p1_x, p1_colliding_wall ? &temp : &p1_y, &CurrentImage_Player_1, p1_down, p1_up, p1_left, p1_right);
	move_player(2, 'c', p2_colliding_wall ? &temp : &p2_x, p2_colliding_wall ? &temp : &p2_y, &CurrentImage_Player_2, p2_down, p2_up, p2_left, p2_right);

	// Grinch movement - PSG
	// if grinch reach last point, reset pathPoint to 0
	if (pathPoint == 2) pathPoint = 0;
	int nextPathPointY = path[pathPoint + 1][1];
	float ydiff = nextPathPointY - grinch_y;
	int direction = ydiff > 0 ? 1 : -1;
	ydiff = ydiff > 0 ? ydiff : -1 * ydiff;
	// if distance between current point and next point on the path is more than what grinch move in one frame
	if (ydiff > grinch_speed) {
		grinch_y += direction * grinch_speed;
		if (direction > 0) {
			CurrentImageGrinch = grinch_down;
		}
		else {
			CurrentImageGrinch = grinch_up;
		}
	}
	else {
		grinch_y = (float) nextPathPointY;
		pathPoint++;
	}

	// reset LiftLostThisFrame if more than 4s has passed since the last time players collided with grinch - JianLin
	if (LifeLostThisFrame && CP_System_GetSeconds() - last_collide_time >= 4) {
		LifeLostThisFrame = false;
	}

	// check collision with grinch & decrease life - ShiWei
	if ((checkGrinchCollide(p1_x, p1_y, grinch_x, grinch_y) || checkGrinchCollide(p2_x, p2_y, grinch_x, grinch_y)) && !LifeLostThisFrame) {
		for (int i = 2; i >= 0; i--) {
			if (life[i] > 0) {
				life[i] = 0;
				LifeLostThisFrame = true;
				last_collide_time = CP_System_GetSeconds();
				break;
			}
		}
	}

	// Loading floor
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(bg_floor, 0, 0, window_w, window_h, 255);
	draw_lvl3_map();

	//Presents Collected? - JianLin
	for (int i = 0; i < 6; i++) {
		if (PresentsCollectedP1(p1_x, p1_y, PresentP1X[i], PresentP1Y[i]) == 1 && PresentP1Opacity[i] != 0) {
			PresentP1Opacity[i] = 0;
			count += 1;
		}

		if (PresentsCollectedP2(p2_x, p2_y, PresentP2X[i], PresentP2Y[i]) == 1 && PresentP2Opacity[i] != 0) {
			PresentP2Opacity[i] = 0;
			count += 1;
		}
	}

	//Presents - JianLin
	for (int i = 0; i < 6; i++) {
		CP_Image_Draw(PresentP1, PresentP1X[i], PresentP1Y[i], 75.0f, 75.0f, PresentP1Opacity[i]);
		CP_Image_Draw(PresentP2, PresentP2X[i], PresentP2Y[i], 75.0f, 75.0f, PresentP2Opacity[i]);
	}

	// draw door - JianLin
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_StrokeWeight(3.0f);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Settings_Fill(white);

	if (count == 12) {
		CP_Color green = CP_Color_Create(34, 139, 34, 255);
		CP_Settings_Fill(green);
	}

	CP_Graphics_DrawRect(730.0f, 0.0f, 140.0f, 50.0f);


	// Grinch
	CP_Image_Draw(CurrentImageGrinch, grinch_x, grinch_y, grinch_size, grinch_size, 255);
	// Player 1
	CP_Image_Draw(CurrentImage_Player_1, p1_x, p1_y, player_w, player_h, 255);
	// Player 2
	CP_Image_Draw(CurrentImage_Player_2, p2_x, p2_y, player_w, player_h, 255);

	// Positioning hearts
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(heart, 80.0f, 67.5f, 100.0f, 100.0f, life[0]);
	CP_Image_Draw(heart, 190.0f, 67.5f, 100.0f, 100.0f, life[1]);
	CP_Image_Draw(heart, 300.0f, 67.5f, 100.0f, 100.0f, life[2]);

	//Count - JianLin
	CP_Settings_Fill(white);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(200.0f, 875.0f, 395.0f, 45.0f);

	CP_Settings_Fill(black);
	CP_Font_Set(font);
	CP_Settings_TextSize(25.0f);
	char text[50];
	sprintf_s(text, sizeof(text), "Presents: %d/12", count);
	CP_Font_DrawText(text, 200.0f, 875.0f);

	// draw instructions box
	CP_Color brown = CP_Color_Create(184, 136, 81, 255);
	CP_Settings_Fill(brown);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(1400.0f, 70.0f, 370.0f, 100.0f);

	// draw instructions title
	CP_Settings_Fill(white);
	CP_Font_Set(font);
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText("Goal", 1400.0f, 40.0f);

	// draw instructions text
	CP_Font_Set(font_text);
	CP_Font_DrawText("~The grinch have noticed your presence.", 1400.0f, 70.0f);
	CP_Font_DrawText("~Collect the presents and avoid the Grinch!", 1400.0f, 100.0f);

// Location to next level - ShiWei
	int giftct_p1 = 0;
	int giftct_p2 = 0;

// Allow players to disappear and pass the top border if presents are all collected
// Count amt of gifts each player collected - ShiWei
	for (int i = 0; i < 6; i++) {
		if (PresentP1Opacity[i] == 0) {
			giftct_p1++;
		}
		if (PresentP2Opacity[i] == 0) {
			giftct_p2++;
		}
	}
	// Teleports player to out of map if gifts collected equate to 6 - ShiWei
	p1_y = ((giftct_p1 == 6) && (p1_y <= 20.0f)) ? -100.0f : p1_y;
	p2_y = ((giftct_p2 == 6) && (p2_y <= 20.0f)) ? -100.0f : p2_y;

	// If both players are above border, next game state - ShiWei
	if (count == 12 && p1_y < 0 && p2_y < 0) {
		int fade = 0;
		fadeInTime += CP_System_GetDt();
		if (fadeInTime < 2.0) fade = (int)(fadeInTime / 2.0 * 255);
		else fade = 255;
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, fade)); CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(800.0, 450.0, 1600.0, 900.0);
		if (fadeInTime >= 2.0) {
			CP_Engine_SetNextGameState(Level4_init, Level4_update, Level4_exit);
			fadeInTime = 0.0; return;
		}
	}

	// back button to main menu
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}

	handlePlayerDeath();
}

void Lvl3_Exit(void)
{
	CP_Image_Free(&bg_floor);
	CP_Image_Free(&heart);

	CP_Image_Free(&p1_up);
	CP_Image_Free(&p1_down);
	CP_Image_Free(&p1_left);
	CP_Image_Free(&p1_right);

	CP_Image_Free(&p2_up);
	CP_Image_Free(&p2_down);
	CP_Image_Free(&p2_left);
	CP_Image_Free(&p2_right);

	CP_Image_Free(&grinch_up);
	CP_Image_Free(&grinch_down);
	CP_Image_Free(&grinch_left);
	CP_Image_Free(&grinch_right);

	CP_Image_Free(&PresentP1);
	CP_Image_Free(&PresentP2);
}