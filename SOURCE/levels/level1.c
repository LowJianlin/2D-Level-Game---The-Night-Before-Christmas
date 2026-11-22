/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file level1.c
@author Gwen Leo Yuhan(leo.y)
*//*______________________________________________________________________*/

#include <stdlib.h>
#include <stdio.h>
#include "cprocessing.h"
#include "../mainmenu/mainmenu.h"
#include "../utils/utils.h"
#include "level1.h"
#include "level2.h"

// SETTINGS
CP_Image Presentp1, Presentp2;
CP_Image BG_Image = NULL;
CP_Image Heart = NULL;
extern float player_w, player_h, grinch_size; // get these variables from main.c file
extern int count;

// PLAYER 1 (WASD Keys)
float player1_x = 780.0f;
float player1_y = 800.0f;
CP_Image Player1_Down, Player1_Up, Player1_Left, Player1_Right;
CP_Image CurrentImage_Player_1; // The image currently displayed

// PLAYER 2 (ARROW Keys)
float player2_x = 880.0f;
float player2_y = 800.0f;
CP_Image Player2_Down, Player2_Up, Player2_Left, Player2_Right;
CP_Image CurrentImage_Player_2;

// COLLECTIBLE GIFTS
#define MAX_GIFTS 6
#define GET_WIDTH 75
#define GET_HEIGHT 75
struct Gift {
	float x;
	float y;
	CP_Image image;
	int collected; 
	int player_id;
};
struct Gift gifts[MAX_GIFTS];

// fade variables
float fade_alpha = 0.0f;
int fade_direction = 1;

// Generate float within a range
static float get_random(float min, float max) {
	return min + ((float)rand() / (float)RAND_MAX) * (max - min);
}

// TEXT SETTINGS
CP_Font Font_title;
CP_Font Font_Text;

extern int count;
float Presentp1X[4];
float Presentp1Y[4];
float Presentp2X[4];
float Presentp2Y[4];
int Presentp1Opacity[4], Presentp2Opacity[4];

extern float game_start_time;

void level1_Init(void)
{
	// Set Count to 0
	count = 0;

	fade_direction = 1;
	fade_alpha = 0.0f;
	
	player1_x = 780.0f;
	player1_y = 800.0f;
	player2_x = 880.0f;
	player2_y = 800.0f;

	game_start_time = CP_System_GetSeconds();

	// BACKGROUND IMAGE	
	BG_Image = CP_Image_Load("Assets/House.jpg");
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// FONT
	Font_title = CP_Font_Load("Assets/font/PressStart2P-Regular.ttf");
	Font_Text = CP_Font_Load("Assets/font/ABeeZee-Regular.ttf");
	CP_Settings_TextAlignment(CP_TEXT_ALIGN_H_CENTER, CP_TEXT_ALIGN_V_MIDDLE);
	CP_Settings_RectMode(CP_POSITION_CENTER);

	// Heart
	Heart = CP_Image_Load("Assets/Heart.png");

	// PLAYER 1
	Player1_Up = CP_Image_Load("Assets/P1-Back.png");
	Player1_Down = CP_Image_Load("Assets/P1-Front.png");
	Player1_Left = CP_Image_Load("Assets/P1-Left.png");
	Player1_Right = CP_Image_Load("Assets/P1-Right.png");
	CurrentImage_Player_1 = Player1_Down; // default image for Player 1

	// PLAYER 2
	Player2_Up = CP_Image_Load("Assets/P2-Back.png");
	Player2_Down = CP_Image_Load("Assets/P2-Front.png");
	Player2_Left = CP_Image_Load("Assets/P2-Left.png");
	Player2_Right = CP_Image_Load("Assets/P2-Right.png");
	CurrentImage_Player_2 = Player2_Down; // default image for Player 2

	//Set Present Count to 0
	count = 0;

	//Presents Graphics
	Presentp1 = CP_Image_Load("Assets/Gift-red.png");
	Presentp2 = CP_Image_Load("Assets/Gift-green.png");

	//Presents Opacity
	for (int i = 0; i < 4; i++) {
		Presentp1Opacity[i] = 255;
	}

	for (int i = 0; i < 4; i++) {
		Presentp2Opacity[i] = 255;
	}
	//Presents Positions
	for (int i = 0; i < 4; i++) {
		int overlap;
		do {
			overlap = 0;
			Presentp1X[i] = CP_Random_RangeFloat(37.5, 1562.5);
			Presentp1Y[i] = CP_Random_RangeFloat(320.0, 782);
			Presentp2X[i] = CP_Random_RangeFloat(37.5, 1562.5);
			Presentp2Y[i] = CP_Random_RangeFloat(320.0, 782);

			for (int j = 0; j < i; j++) {
				if (CheckOverlap(Presentp1X[i], Presentp1Y[i], Presentp1X[j], Presentp1Y[j]) ||
					CheckOverlap(Presentp2X[i], Presentp2Y[i], Presentp1X[j], Presentp1Y[j]) ||
					CheckOverlap(Presentp2X[i], Presentp2Y[i], Presentp2X[j], Presentp2Y[j])) {
					overlap = 1;
					break;
				}
			}
		} while (overlap);
	}

	// Draw rectangle
	CP_Settings_RectMode(CP_POSITION_CENTER);
}


void level1_Update(void)
{

	// Allignment Settings
	float center_x = CP_System_GetWindowWidth() / 2.0f;
	float center_y = CP_System_GetWindowHeight() / 2.0f;

	//Color Settings
	CP_Image_Draw(BG_Image, center_x, center_y, 1920, 1080, 255);
	CP_Color Box = CP_Color_Create(255, 255, 255, 0);

	// Get DT
	float DT = CP_System_GetDt();

	//Presents Collected
	for (int i = 0; i < 4; i++) {
		if (PresentsCollectedP1(player1_x, player1_y, Presentp1X[i], Presentp1Y[i]) == 1 && Presentp1Opacity[i] != 0) {
			Presentp1Opacity[i] = 0;
			count += 1;
		}

		if (PresentsCollectedP2(player2_x, player2_y, Presentp2X[i], Presentp2Y[i]) == 1 && Presentp2Opacity[i] != 0) {
			Presentp2Opacity[i] = 0;
			count += 1;
		}
	}

	//Presents
	for (int i = 0; i < 4; i++) {
		CP_Image_Draw(Presentp1, Presentp1X[i], Presentp1Y[i], 75.0f, 75.0f, Presentp1Opacity[i]);
		CP_Image_Draw(Presentp2, Presentp2X[i], Presentp2Y[i], 75.0f, 75.0f, Presentp2Opacity[i]);
	}

	// move_player function from utils.c
	move_player(1,'m', & player1_x, &player1_y, &CurrentImage_Player_1, Player1_Down, Player1_Up, Player1_Left, Player1_Right);
	move_player(2,'m', &player2_x, &player2_y, &CurrentImage_Player_2, Player2_Down, Player2_Up, Player2_Left, Player2_Right);

	// Render Player 1 and 2 with size 47x80
	CP_Image_Draw(CurrentImage_Player_1, player1_x, player1_y, player_w, player_h, 255);
	CP_Image_Draw(CurrentImage_Player_2, player2_x, player2_y, player_w, player_h, 255);

	// Heart Position
	CP_Image_Draw(Heart, 80.0f, 67.5f, 100.0f, 100.0f, 255);
	CP_Image_Draw(Heart, 190.0f, 67.5f, 100.0f, 100.0f, 255);
	CP_Image_Draw(Heart, 300.0f, 67.5f, 100.0f, 100.0f, 255);

	//Count
	CP_Settings_Fill(CP_Color_Create(255, 255, 255, 255));
	CP_Settings_RectMode(CP_POSITION_CENTER);
	CP_Graphics_DrawRect(200.0f, 875.0f, 395.0f, 45.0f);

	CP_Settings_Fill(CP_Color_Create(0, 0, 0, 255));
	CP_Font_Set(Font_title);
	CP_Settings_TextSize(25.0f);
	char text[50];
	sprintf_s(text, sizeof(text), "Presents: %d/8", count);
	CP_Font_DrawText(text, 200.0f, 875.0f);


	// Side Box - Instructions
	CP_Color SideBoxcolor = CP_Color_Create(184, 136, 81, 255);
	CP_Color Fontcolor = CP_Color_Create(255, 255,255, 255);
	CP_Settings_Fill(SideBoxcolor);
	CP_Settings_StrokeWeight(3);
	CP_Graphics_DrawRect(1430.0f, 80.0f, 300.0f, 150.0f);
	CP_Font_Set(Font_title);
	CP_Settings_Fill(Fontcolor);
	CP_Settings_TextSize(20.0f);
	CP_Font_DrawText("Goal", 1440.0f, 40.0f);
	CP_Font_Set(Font_Text);
	CP_Settings_Fill(Fontcolor);
	CP_Settings_TextSize(25.0f);
	CP_Font_DrawText("~Collect the presents", 1430.0f, 80.0f);
	CP_Font_DrawText("~Raid Grinch's house!", 1430.0f, 120.0f);

	// Trigger box
	CP_Settings_Fill(Box);
	CP_Settings_StrokeWeight(0);
	CP_Graphics_DrawRect(830.0f, 140.0f, 340.0f, 300.0f);

	// Check if both players enter the transition box
	int player1_in_box = player1_x > 830.0f && player1_x < 830.0f + 340.0f &&
		player1_y < 300.0f;
	int player2_in_box = player2_x > 830.0f && player2_x < 830.0f + 340.0f &&
		player2_y < 300.0f;

	// Location to next level - ShiWei
	int giftct_p1 = 0;
	int giftct_p2 = 0;

	// Allow players to disappear and pass the top border if presents are all collected
	// Count amt of gifts each player collected - ShiWei
	for (int i = 0; i < 4; i++) {
		if (Presentp1Opacity[i] == 0) {
			giftct_p1++;
		}
		if (Presentp2Opacity[i] == 0) {
			giftct_p2++;
		}
	}
	// Teleports player to out of map if gifts collected equate to 6
	player1_y = ((giftct_p1 == 4) && player1_in_box) ? -100.0f : player1_y;
	player2_y = ((giftct_p2 == 4) && player2_in_box) ? -100.0f : player2_y;

	// If both players are above border, next game state
	if (count == 8 && player1_y < 0 && player2_y < 0) {
		fade_direction = -1;
	}

	// Fade effect: increase or decrease alpha based on direction
	if (fade_direction == -1) {
		fade_alpha += 255.0f * DT;
		if (fade_alpha >= 255.0f) {
			fade_alpha = 255.0f;
			CP_Engine_SetNextGameState(Level2_Init, Level2_Update, Level2_Exit); // Transition to Level 2
		}
	}

	// Draw the fade-to-black effect if in transition
	if (fade_direction == -1) {
		CP_Settings_Fill(CP_Color_Create(0, 0, 0, (int)fade_alpha));
		CP_Graphics_DrawRect(center_x, center_y, (float)CP_System_GetWindowWidth(), (float)CP_System_GetWindowHeight());
	}

	// back to main menu on esc press - Shi Wei
	if (CP_Input_KeyTriggered(KEY_ESCAPE)) {
		CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
	}
}

void level1_Exit(void)
{
	// Free Player 1 images
	CP_Image_Free(&Player1_Down);
	CP_Image_Free(&Player1_Up);
	CP_Image_Free(&Player1_Left);
	CP_Image_Free(&Player1_Right);

	// Free Player 2 images
	CP_Image_Free(&Player2_Down);
	CP_Image_Free(&Player2_Up);
	CP_Image_Free(&Player2_Left);
	CP_Image_Free(&Player2_Right);

	// Free gifts image
	for (int i = 0; i < MAX_GIFTS; ++i) {
		CP_Image_Free(&gifts[i].image);
	}
}