/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file utils.c
@author Low JianLin (jianlin.low)
@author Gwen Leo Yuhan(leo.y)
@author Yar Xuan (xuan.yar)
@author Beh Shi Wei (beh.s)
*//*______________________________________________________________________*/

#include <math.h>
#include "cprocessing.h"
#include "utils.h"
#include "../mainmenu/mainmenu.h"

#define MinDistance 30.0f

// Jianlin
int CheckOverlap(float x1, float y1, float x2, float y2) {
	float dx = x1 - x2;
	float dy = y1 - y2;
	double distance = sqrt((double) (dx * dx + dy * dy));
	return distance < MinDistance;
}

void timer(double* startTime, int* draw, double intervalGreen, double intervalRed) {
	double elapsedTime = CP_System_GetSeconds() - *startTime;

	if (elapsedTime >= (intervalGreen + intervalRed)) {
		*startTime = CP_System_GetSeconds();
	}

	if (elapsedTime < intervalGreen) {
		*draw = 0;
	}
	else if (elapsedTime >= intervalGreen && elapsedTime < (intervalGreen + intervalRed)) {
		*draw = 1;
	}
}

// Gwen
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y)
{
	float area_left_x = (area_center_x - (area_width / 2));
	float area_right_x = (area_center_x + (area_width / 2));
	float area_left_y = (area_center_y - (area_height / 2));
	float area_right_y = (area_center_y + (area_height / 2));

	if ((area_left_x <= click_x && click_x <= area_right_x) && (area_left_y <= click_y && click_y <= area_right_y)) {
		return 1;
	}
	else {
		return 0;
	}
}

// Gwen & Yar Xuan
extern float speed, player_w, player_h; // get speed variable from main.c

void move_player(int player, char img_mode, float* player_x, float* player_y, CP_Image *player_image, CP_Image player_front, CP_Image player_back, CP_Image player_left, CP_Image player_right) {
	float dt = CP_System_GetDt();
	// need img_mode to know if the player image is drawn from corner or center
	int drawn_center = img_mode == 'm';

	float player_left_x = drawn_center ? *player_x - (player_w / 2) : *player_x;
	float player_top_y = drawn_center ? *player_y - (player_h / 2) : *player_y;

	if (CP_Input_KeyDown(player == 1 ? KEY_W : KEY_UP)) {
		*player_image = player_back;
		if (player_top_y > 0) *player_y -= speed * dt;
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_S : KEY_DOWN)) {
		*player_image = player_front;
		if (player_top_y < CP_System_GetWindowHeight() - player_h) *player_y += speed * dt;
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_A : KEY_LEFT)) {
		*player_image = player_left;
		if (player_left_x > 0) *player_x -= speed * dt;
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_D : KEY_RIGHT)) {
		*player_image = player_right;
		if (player_left_x < CP_System_GetWindowWidth() - player_w) *player_x += speed * dt;
	}
}

// Gwen & Yar Xuan & Jianlin
void move_playerLevel2(int player, char img_mode, float* player_x, float* player_y, CP_Image* player_image, CP_Image player_front, CP_Image player_back, CP_Image player_left, CP_Image player_right) {
	float dt = CP_System_GetDt();
	// need img_mode to know if the player image is drawn from corner or center
	int drawn_center = img_mode == 'm';

	float player_left_x = drawn_center ? *player_x - (player_w / 2) : *player_x;
	float player_top_y = drawn_center ? *player_y - (player_h / 2) : *player_y;

	if (CP_Input_KeyDown(player == 1 ? KEY_W : KEY_UP)) {
		*player_image = player_back;
		if (player_top_y > 80) *player_y -= speed * dt;
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_S : KEY_DOWN)) {
		*player_image = player_front;
		if (player_top_y < CP_System_GetWindowHeight() - player_h) *player_y += speed * dt;
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_A : KEY_LEFT)) {
		*player_image = player_left;
		if (player_left_x > 0) *player_x -= speed * dt;
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_D : KEY_RIGHT)) {
		*player_image = player_right;
		if (player_left_x < CP_System_GetWindowWidth() - player_w) *player_x += speed * dt;
	}
}

// Jianlin
extern int life[];
extern double fadeInTime;

void handlePlayerDeath() {
	//If dead, exit to Main Menu
	if (life[0] == 0) {
		int fade = 0;

		fadeInTime += CP_System_GetDt();

		if (fadeInTime < 2.0)
			fade = (int)(fadeInTime / 2.0 * 255);
		else fade = 255;

		CP_Settings_Fill(CP_Color_Create(0, 0, 0, fade));
		CP_Settings_RectMode(CP_POSITION_CENTER);
		CP_Graphics_DrawRect(800.0, 450.0, 1600.0, 900.0);

		if (fadeInTime >= 2.0) {
			CP_Engine_SetNextGameState(Main_Menu_Init, Main_Menu_Update, Main_Menu_Exit);
			fadeInTime = 0.0; 
			return;
		}
	}
}

int PresentsCollectedP1(float const p1_x, float const p1_y, float presentX, float presentY){
	CP_Vector CenterCircle1 = CP_Vector_Set(p1_x, p1_y);
	CP_Vector CenterCircle2 = CP_Vector_Set(presentX, presentY);

	float distance = CP_Vector_Distance(CenterCircle1, CenterCircle2);

	if (distance <= 30.0)
		return 1;
	else return 0;

}

int PresentsCollectedP2(float p2_x, float p2_y, float presentX, float presentY) {
	CP_Vector CenterCircle1 = CP_Vector_Set(p2_x, p2_y);
	CP_Vector CenterCircle2 = CP_Vector_Set(presentX, presentY);

	float distance = CP_Vector_Distance(CenterCircle1, CenterCircle2);

	if (distance <= 30.0)
		return 1;
	else return 0;

}

// Shi Wei
extern float player_w, player_h, grinch_size;

int checkGrinchCollide(float player_x, float player_y, float grinch_x, float grinch_y) {
	// calculate distance between player and grinch using their center points
	// because player and grinch x and y = top left of their sprites
	float player_center_x = player_x + (player_w / 2);
	float player_center_y = player_y + (player_h / 2);
	float grinch_center_x = grinch_x + (grinch_size / 2);
	float grinch_center_y = grinch_y + (grinch_size / 2);

	CP_Vector player = CP_Vector_Set(player_center_x, player_center_y);
	CP_Vector grinch = CP_Vector_Set(grinch_center_x, grinch_center_y);

	float distance = CP_Vector_Distance(player, grinch);
	if (distance < (grinch_size / 2) + 10) return 1;
	return 0;
}
