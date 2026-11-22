/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file level4.c
@author Yar Xuan (xuan.yar)
*//*______________________________________________________________________*/

#include <stdio.h>
#include <stdbool.h>
#include "cprocessing.h"
#include "../utils/map_utils.h"
#include "../utils/utils.h"
#include "../credits/ending.h"
#include "../mainmenu/mainmenu.h"

CP_Image bg_floor, life_heart;
CP_Image p1_front, p1_back, p1_left, p1_right, p2_front, p2_back, p2_left, p2_right;
CP_Image grinch_front, grinch_back, grinch_left, grinch_right;
CP_Image p1_current, p2_current, grinch_current;
CP_Font font_title, font_text;

// global variables from main.c
extern float player_w, player_h, grinch_size, speed; 
extern bool LifeLostThisFrame;
extern int life[3], count;

extern float PresentP1X[6], PresentP1Y[6], PresentP2X[6], PresentP2Y[6];
extern int PresentP1Opacity[6], PresentP2Opacity[6];
CP_Image PresentP1, PresentP2;

extern double fadeInTime;

float temp = 0.0f; // temp variable to stop moving player when they reach edges of window
float p1_x, p1_y, p2_x, p2_y, grinch_x, grinch_y;
int currentPt; // index of grinch current position

// array of xy points in grinch path
float grinch_path[][2] = { 
	{735.0f, 60.0f}, // start pt
	{735.0f, 215.0f}, {228.0f, 215.0f}, {735.0f, 215.0f}, // top left room
	{735.0f, 670.0f}, {182.0f, 670.0f}, // bottom left room
	{1280.0f, 670.0f}, {1280.0f, 180.0f}, {960.0f, 180.0f}, {960.0f, 670.0f}, {735.0f, 670.0f}, // right room
	{735.0f, 60.0f} // back to start pt
}; 

// coords array for presents to spawn for each room. {startx, endx, starty, endy}
float roomCoords[3][4] = {
	{235.0f, 550.0f, 130.0f, 400.0f}, // top left room
	{200.0f, 550.0f, 600.0f, 750.0f}, // bottom left room
	{960.0f, 1300.0f, 200.0f, 750.0f} // right room
};

// last time player collided with grinch, in seconds
float last_hit_time;

void Level4_init(void)
{
	// reset grinch current point in its path
	currentPt = 0;

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

	// generate random positions for presents (4 in each room, 2 per player per room) - Jianlin
	for (int i = 0, room = 0; i < 6; i++) {
		int overlap;
		do {
			overlap = 0;
			PresentP1X[i] = CP_Random_RangeFloat(roomCoords[room][0], roomCoords[room][1]);
			PresentP1Y[i] = CP_Random_RangeFloat(roomCoords[room][2], roomCoords[room][3]);

			PresentP2X[i] = CP_Random_RangeFloat(roomCoords[room][0], roomCoords[room][1]);
			PresentP2Y[i] = CP_Random_RangeFloat(roomCoords[room][2], roomCoords[room][3]);
			
			for (int j = 0; j < i; j++) {
				if (CheckOverlap(PresentP1X[i], PresentP1Y[i], PresentP1X[j], PresentP1Y[j]) ||
					CheckOverlap(PresentP2X[i], PresentP2Y[i], PresentP1X[j], PresentP1Y[j]) ||
					CheckOverlap(PresentP2X[i], PresentP2Y[i], PresentP2X[j], PresentP2Y[j])) {
					overlap = 1;
					break;
				}
			}
		} while (overlap);

		// every 2 iterations, move on to next room
		if (i % 2 != 0) room++;
	}

	// load images
	life_heart = CP_Image_Load("Assets/Heart.png");
	bg_floor = CP_Image_Load("Assets/floor.jpg");

	p1_front = CP_Image_Load("Assets/P1-Front.png");
	p1_back = CP_Image_Load("Assets/P1-Back.png");
	p1_left = CP_Image_Load("Assets/P1-Left.png");
	p1_right = CP_Image_Load("Assets/P1-Right.png");

	p2_front = CP_Image_Load("Assets/P2-Front.png");
	p2_back = CP_Image_Load("Assets/P2-Back.png");
	p2_left = CP_Image_Load("Assets/P2-Left.png");
	p2_right = CP_Image_Load("Assets/P2-Right.png");

	grinch_front = CP_Image_Load("Assets/Grinch_Front.png");
	grinch_back = CP_Image_Load("Assets/Grinch_Back.png");
	grinch_left = CP_Image_Load("Assets/Grinch_Left.png");
	grinch_right = CP_Image_Load("Assets/Grinch_Right.png");

	PresentP1 = CP_Image_Load("Assets/Gift-red.png");
	PresentP2 = CP_Image_Load("Assets/Gift-green.png");

	// load fonts
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	font_title = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	font_text = CP_Font_Load("Assets/font/ABeeZee-Regular.ttf");

	int window_w = CP_System_GetWindowWidth();
	int window_h = CP_System_GetWindowHeight();
	float center = (float)window_w / 2;

	// set starting position and image for p1 p2 and grinch
	p1_x = center - player_w - 10;
	p1_y = window_h - player_h;
	p1_current = p1_front;

	p2_x = center + 10;
	p2_y = window_h - player_h;
	p2_current = p2_front;

	grinch_x = center - grinch_size / 2;
	grinch_y = 0;
	grinch_current = grinch_front;
}

void Level4_update(void) {
	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Graphics_ClearBackground(black);

	int window_w = CP_System_GetWindowWidth();
	int window_h = CP_System_GetWindowHeight();

	// draw bg image and map
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(bg_floor, 0, 0, (float)window_w, (float)window_h, 255);
	draw_lvl4_map();

	int p1_colliding_wall = lvl4_wall_collision(1, p1_x, p1_y);
	int p2_colliding_wall = lvl4_wall_collision(2, p2_x, p2_y);

	// move p1 and p2 - Gwen
	// if player next movement will collide with wall, give temp var as x and y 
	// so that it doesn't actually change the player x y values
	move_player(1, 'c', p1_colliding_wall ? &temp : &p1_x, p1_colliding_wall ? &temp : &p1_y, &p1_current, p1_front, p1_back, p1_left, p1_right);
	move_player(2, 'c', p2_colliding_wall ? &temp : &p2_x, p2_colliding_wall ? &temp : &p2_y, &p2_current, p2_front, p2_back, p2_left, p2_right);

	// move grinch
	float mvment = speed * CP_System_GetDt();
	int pathPoints = sizeof(grinch_path) / sizeof(grinch_path[0]);

	// reset currentPt if reached last point, so it will keep looping the path
	if (currentPt == pathPoints - 1) currentPt = 0;

	// do movement 
	if (currentPt < pathPoints - 1) {
		float nextX = (float) grinch_path[currentPt + 1][0];
		float nextY = (float) grinch_path[currentPt + 1][1];
		float dirX = nextX - grinch_x;
		float dirY = nextY - grinch_y;

		// if length between current position and next position > 0
		if (CP_Math_Distance(grinch_x, nextX, grinch_y, nextY) > 0) {
			// calculate absolute value of x diff and y diff
			float xdiff = grinch_x - nextX;
			float ydiff = grinch_y - nextY;
			xdiff = xdiff > 0 ? xdiff : -1 * xdiff;
			ydiff = ydiff > 0 ? ydiff : -1 * ydiff;

			// check if grinch position reached the next point
			if (xdiff < mvment && ydiff < mvment) {
				grinch_x = nextX;
				grinch_y = nextY;
				currentPt++;
			}
			else {
				dirX = dirX == 0 ? dirX : dirX > 0 ? 1 : -1;
				dirY = dirY == 0 ? dirY : dirY > 0 ? 1 : -1;

				grinch_x += dirX * mvment;
				grinch_y += dirY * mvment;

				// change grinch image to match direction
				if (dirX > 0) grinch_current = grinch_right;
				else if (dirX < 0) grinch_current = grinch_left;
				else if (dirY > 0) grinch_current = grinch_front;
				else if (dirY < 0) grinch_current = grinch_back;
			}
		}
	}

	// check presents collected - Jianlin
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

	// draw presents
	for (int i = 0; i < 6; i++) {
		CP_Image_Draw(PresentP1, PresentP1X[i], PresentP1Y[i], 75.0f, 75.0f, PresentP1Opacity[i]);
		CP_Image_Draw(PresentP2, PresentP2X[i], PresentP2Y[i], 75.0f, 75.0f, PresentP2Opacity[i]);
	}

	// draw door
	CP_Settings_RectMode(CP_POSITION_CORNER);
	CP_Settings_StrokeWeight(3.0f);
	CP_Color white = CP_Color_Create(255, 255, 255, 255);
	CP_Settings_Fill(white);

	if (count == 12) {
		CP_Color green = CP_Color_Create(34, 139, 34, 255);
		CP_Settings_Fill(green);
	}

	CP_Graphics_DrawRect(730.0f, 0.0f, 140.0f, 50.0f);

	// draw grinch
	CP_Image_Draw(grinch_current, grinch_x, grinch_y, grinch_size, grinch_size, 255);

	// take screenshot of players from top left, fovSize
	float fovSize = 160.0f;
	float ss_p1_x = p1_x - fovSize / 2;
	float ss_p1_y = p1_y - fovSize / 2;
	float ss_p2_x = p2_x - fovSize / 2;
	float ss_p2_y = p2_y - fovSize / 2;
	float screenshot_size = fovSize + player_w;

	CP_Image player1_ss = CP_Image_Screenshot((int)ss_p1_x, (int)ss_p1_y, (int)screenshot_size, (int)screenshot_size);
	CP_Image player2_ss = CP_Image_Screenshot((int)ss_p2_x, (int)ss_p2_y, (int)screenshot_size, (int)screenshot_size);
	
	// blackout screen
	CP_Color grey = CP_Color_Create(18, 18, 18, 255);
	CP_Settings_Fill(grey);
	CP_Graphics_DrawRect(0, 0, (float) window_w, (float) window_h);

	// draw screenshots
	CP_Image_Draw(player1_ss, ss_p1_x, ss_p1_y, screenshot_size, screenshot_size, 255);
	CP_Image_Draw(player2_ss, ss_p2_x, ss_p2_y, screenshot_size, screenshot_size, 255);
	
	// reset LifeLostThisFrame if more than 4s has passed since the last time players collided with grinch
	if (LifeLostThisFrame && CP_System_GetSeconds() - last_hit_time >= 4) {
		LifeLostThisFrame = false;
	}

	// check collision with grinch & decrease life - ShiWei (collision), Jianlin (life system)
	if ((checkGrinchCollide(p1_x, p1_y, grinch_x, grinch_y) || checkGrinchCollide(p2_x, p2_y, grinch_x, grinch_y)) && !LifeLostThisFrame) {
		for (int i = 2; i >= 0; i--) {
			if (life[i] > 0) {
				life[i] = 0;
				LifeLostThisFrame = true;
				last_hit_time = CP_System_GetSeconds();
				break;
			}
		}
	}

	// draw hearts
	CP_Settings_ImageMode(CP_POSITION_CENTER);
	CP_Image_Draw(life_heart, 80.0f, 67.5f, 100.0f, 100.0f, life[0]);
	CP_Image_Draw(life_heart, 190.0f, 67.5f, 100.0f, 100.0f, life[1]);
	CP_Image_Draw(life_heart, 300.0f, 67.5f, 100.0f, 100.0f, life[2]);

	// draw instructions box
	CP_Color brown = CP_Color_Create(184, 136, 81, 255);
	CP_Settings_Fill(brown);
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(1430.0f, 80.0f, 300.0f, 150.0f);
	
	// draw instructions title
	CP_Settings_Fill(white);
	CP_Font_Set(font_title);
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText("Goal", 1440.0f, 40.0f);
	
	// draw instructions text
	CP_Font_Set(font_text);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("~Collect the presents", 1430.0f, 80.0f);
	CP_Font_DrawText("~Avoid the Grinch!", 1430.0f, 120.0f);
	
	// draw p1 and p2
	CP_Settings_ImageMode(CP_POSITION_CORNER);
	CP_Image_Draw(p1_current, p1_x, p1_y, player_w, player_h, 255);
	CP_Image_Draw(p2_current, p2_x, p2_y, player_w, player_h, 255);

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
	p1_y = ((giftct_p1 == 6) && (p1_y <= 20.0f)) ? -200.0f : p1_y;
	p2_y = ((giftct_p2 == 6) && (p2_y <= 20.0f)) ? -200.0f : p2_y;

	// If both players are above border, next game state
	if (count == 12 && p1_y < 0 && p2_y < 0) {
		int fade = 0;
		fadeInTime += CP_System_GetDt();
		if (fadeInTime < 2.0) fade = (int)(fadeInTime / 2.0 * 255);
		else fade = 255;
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, fade)); CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(800.0, 450.0, 1600.0, 900.0);
		if (fadeInTime >= 2.0) {
			CP_Engine_SetNextGameState(ending_init, ending_update, ending_exit);
			fadeInTime = 0.0; return;
		}
	}

	handlePlayerDeath();

	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void Level4_exit(void)
{
	CP_Image_Free(&bg_floor);
	CP_Image_Free(&life_heart);

	CP_Image_Free(&p1_front);
	CP_Image_Free(&p1_back);
	CP_Image_Free(&p1_left);
	CP_Image_Free(&p1_right);

	CP_Image_Free(&p2_front);
	CP_Image_Free(&p2_back);
	CP_Image_Free(&p2_left);
	CP_Image_Free(&p2_right);

	CP_Image_Free(&grinch_front);
	CP_Image_Free(&grinch_back);
	CP_Image_Free(&grinch_left);
	CP_Image_Free(&grinch_right);

	CP_Image_Free(&PresentP1);
	CP_Image_Free(&PresentP2);
}