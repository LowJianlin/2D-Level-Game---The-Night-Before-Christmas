/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE 
@file map_utils.c
@author Yar Xuan (xuan.yar)
@author Beh Shi Wei (beh.s)
*//*______________________________________________________________________*/

#include "cprocessing.h"
extern float speed, player_w, player_h; // get speed variable from main.c
float player_hat_height = 25.0f;

// Shi Wei
void draw_lvl3_map() {
	float window_right = (float) CP_System_GetWindowWidth();
	float window_bottom = (float) CP_System_GetWindowHeight();
	float center_x = window_right / 2;
	float center_y = window_bottom / 2;

	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(black);

	// Left
	CP_Graphics_BeginShape();

	CP_Graphics_AddVertex(0.0f, window_bottom);
	CP_Graphics_AddVertex(center_x - 70, window_bottom); // Corridor
	CP_Graphics_AddVertex(center_x - 70, window_bottom - 100); // Corridor
	CP_Graphics_AddVertex(center_x - 158, window_bottom - 100);
	CP_Graphics_AddVertex(center_x - 158, window_bottom - 50);
	CP_Graphics_AddVertex(182.0f, window_bottom - 50); 
	CP_Graphics_AddVertex(182.0f, center_y + 143); 
	CP_Graphics_AddVertex(center_x - 158, center_y + 143);
	CP_Graphics_AddVertex(center_x - 158, center_y + 216); // TOP ROOM
	CP_Graphics_AddVertex(center_x - 70, center_y + 216); // Corridor
	CP_Graphics_AddVertex(center_x - 70, center_y - 90); // Corridor
	CP_Graphics_AddVertex(center_x - 158, center_y - 90);
	CP_Graphics_AddVertex(center_x - 158, center_y + 40);
	CP_Graphics_AddVertex(228.0f, center_y + 40);
	CP_Graphics_AddVertex(228.0f, 125.0f);
	CP_Graphics_AddVertex(center_x - 158, 125.0f);
	CP_Graphics_AddVertex(center_x - 158, 203.0f);
	CP_Graphics_AddVertex(center_x - 70, 203.0f); // Corridor
	CP_Graphics_AddVertex(center_x - 70, 0.0f); // Corridor
	CP_Graphics_AddVertex(0.0f, 0.0f);

	CP_Graphics_EndShape();

	// Right
	CP_Graphics_BeginShape();

	CP_Graphics_AddVertex(window_right, window_bottom);
	CP_Graphics_AddVertex(center_x + 70, window_bottom); // corridor bottom
	CP_Graphics_AddVertex(center_x + 70, window_bottom - 100); // move up, doorway bottom left
	CP_Graphics_AddVertex(center_x + 158, window_bottom - 100); // right, same y, doorway bottom right
	CP_Graphics_AddVertex(center_x + 158, window_bottom - 50); // same x, down
	CP_Graphics_AddVertex(window_right - 182, window_bottom - 50); // higher
	CP_Graphics_AddVertex(window_right - 182, 600.0f); // all the way up
	CP_Graphics_AddVertex(center_x + 158, 600.0f);
	CP_Graphics_AddVertex(center_x + 158, center_y + 216); // doorway top right
	CP_Graphics_AddVertex(center_x + 70, center_y + 216); // doorway top left
	CP_Graphics_AddVertex(center_x + 70, center_y - 90);
	CP_Graphics_AddVertex(center_x + 158, center_y - 90);
	CP_Graphics_AddVertex(center_x + 158, 490.0f);
	CP_Graphics_AddVertex(window_right - 182, 490.0f);
	CP_Graphics_AddVertex(window_right - 182, 110.0f);
	CP_Graphics_AddVertex(center_x + 158, 110.0f);
	CP_Graphics_AddVertex(center_x + 158, 205.0f);
	CP_Graphics_AddVertex(center_x + 70, 205.0f);
	CP_Graphics_AddVertex(center_x + 70, 0.0f);
	CP_Graphics_AddVertex(window_right, 0.0f);

	CP_Graphics_EndShape();
}

// Shi Wei
// return 1 if player is going to collide with wall
int lvl3_wall_collision(int player, float player_x, float player_y) {
	float dt = CP_System_GetDt();
	float mvment = speed * dt;

	int window_width = CP_System_GetWindowWidth();
	int window_height = CP_System_GetWindowHeight();
	float center_x = window_width / 2.0f;
	float center_y = window_height / 2.0f;

	if (CP_Input_KeyDown(player == 1 ? KEY_W : KEY_UP)) {
		float end_y = player_y - mvment;
		// if player_y going above top left room & player_x within top left room
		if (end_y < 125 &&
			player_x >= 228 &&
			player_x <= center_x - 158 - player_w) {
			return 1;
		}
		// if player_y going above top left room entrance && player_x within entrance
		if (end_y + player_hat_height < 203 &&
			player_x + player_w >= center_x - 158 &&
			player_x <= center_x - 70) {
			return 1;
		}
		// if player_y going above bottom left room & player_x within bottom left room ca
		if (end_y < center_y + 143 &&
			end_y > center_y + 40 &&
			player_x >= 182 && player_x < center_x - 158 - player_w) {
			return 1;
		}
		// if player_y going above bottom left room entrance & player_x within bot left room entrance
		if (end_y + player_hat_height < center_y + 216 &&
			end_y >= center_y - 90 &&
			player_x + player_w >= center_x - 158 &&
			player_x <= center_x - 70) {
			return 1;
		}
		// if player_y going above top right room & player_x within top right room
		if (end_y < 110 &&
			player_x >= center_x + 158 &&
			player_x <= window_width - 182 - player_w) {
			return 1;
		}
		// if player_y going above top right room entrance & player_x within top right room entrance
		if (end_y + player_hat_height < 205 &&
			player_x + player_w >= center_x + 70 &&
			player_x <= center_x + 158) {
			return 1;
		}		
		// if player_y going above bottom right room & player_x within bottom right room
		if (end_y < 600 &&
			end_y > center_y + 40 &&
			player_x >= center_x + 158 &&
			player_x <= window_width - 182 - player_w) {
			return 1;
		}
		// if player_y going above bottom right room entrance & player_x within bottom right room entrance
		if (end_y + player_hat_height < 666 &&
			end_y > 360 &&
			player_x + player_w >= center_x + 70 &&
			player_x <= center_x + 158) {
			return 1;
		}
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_S : KEY_DOWN)) {
		float end_y = player_y + mvment;
		// if player_y going below top left room & player_x within top left room
		if (end_y > center_y + 40 - player_h &&
			end_y < center_y + 143 - player_h &&
			player_x >= 228 && player_x <= center_x - 158 - player_w) {
			return 1;
		}
		// if player_y going below top left room entrance && player_x within entrance
		if (end_y > center_y - 90 - player_h &&
			end_y < center_y + 216 - player_h &&
			player_x + player_w >= center_x - 158 && player_x <= center_x - 70) {
			return 1;
		}
		// if player_y going below bottom left room & player_x within bottom left room 
		if (end_y > window_height - 50 - player_h &&
			player_x >= 182 &&
			player_x < center_x - 158 - player_w) {
			return 1;
		}
		// if player_y going below bottom left room entrance & player_x within bot left room entrance
		if (end_y > window_height - 100 - player_h &&
			player_x + player_w >= center_x - 158 &&
			player_x <= center_x - 70) {
			return 1;
		}
		// if player_y going below top right room & player_x within top right room
		if (end_y > center_y + 40 - player_h &&
			end_y < 600 &&
			player_x >= center_x + 158 && player_x <= window_width - 182 - player_w) {
			return 1;
		}
		// if player_y going below top right room entrance & player_x within top right room entrance
		if (end_y > center_y - 90 - player_h &&
			end_y + player_hat_height < center_y + 216 &&
			player_x + player_w >= center_x + 70 &&
			player_x <= center_x + 158) {
			return 1;
		}
		// if player_y going below bottom right room & player_x within bottom right room
		if (end_y + player_h > window_height - 50 &&
			player_x >= center_x + 158 &&
			player_x <= window_width - 182 - player_w) {
			return 1;
		}
		// if player_y going below bottom right room entrance & player_x within bottom right room entrance
		if (end_y + player_h > window_height - 100 &&
			player_x + player_w >= center_x + 70 &&
			player_x <= center_x + 158) {
			return 1;
		}
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_A : KEY_LEFT)) {
		float end_x = player_x - mvment;
		// if player_x going left of top left room & player_y within top left room
		if (end_x < 228 &&
			player_y >= 125 &&
			player_y + player_h < center_y + 40) {
			return 1;
		}
		// if player_x going left of bottom left room & player_y within bottom left room
		if (end_x < 182 && player_y >= center_y + 143) {
			return 1;
		}
		// if player_x going left of corridor & player_y not in left rooms entrances
		if (end_x < center_x - 70 && end_x >= center_x - 158 &&
			!((player_y + player_hat_height >= 203 && player_y + 80 <= center_y - 90)
				|| (player_y + player_hat_height >= center_y + 216 && player_y + 80 <= window_height - 100))) {
			return 1;
		}
		// if player_x going left of top / bottom right room & 
		// player_y not within top / bottom right room entrance
		if (end_x < center_x + 158 &&
			end_x >= center_x + 70 &&
			!((player_y + player_hat_height >= 205 && player_y + player_h <= center_y - 90) ||
				(player_y + player_hat_height >= center_y + 216 && player_y + player_h <= window_height - 100))) {
			return 1;
		}
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_D : KEY_RIGHT)) {
		float end_x = player_x + mvment;
		// if player_x going right of top left room / bottom left room & 
		// player_y not within top left room / bottom left room entrance
		if (end_x + player_w > center_x - 158 && end_x + player_w < center_x - 70 &&
			!((player_y + player_hat_height >= 203 && player_y + player_h <= center_y - 90) ||
				(player_y + player_hat_height >= center_y + 216 && player_y + player_h <= window_height - 100))) {
			return 1;
		}
		// if player_x going right of corridor & player_y not in right rooms entrances
		if (end_x + player_w > center_x + 70 && end_x < center_x + 158 &&
			!((player_y + player_hat_height >= 205 && player_y + player_h <= center_y - 90) ||
				((player_y + player_hat_height >= center_y + 216 && player_y + player_h <= window_height - 100)))) {
			return 1;
		}
		// if player_x going right of top / bottom right room & 
		// player_y within top / bottom right room 
		if (end_x + player_w > window_width - 182 &&
			((player_y >= 110 && player_y + player_h <= center_y + 40) ||
				(player_y >= 600 && player_y + player_h <=  window_height - 50))) {
			return 1;
		}
	}

	return 0;
}

// Yar Xuan
void draw_lvl4_map() {
	float window_width = (float) CP_System_GetWindowWidth();
	float screen_bottom = (float) CP_System_GetWindowHeight();
	float center_x = window_width / 2.0f;
	float center_y = CP_System_GetWindowHeight() / 2.0f;

	CP_Color black = CP_Color_Create(0, 0, 0, 255);
	CP_Settings_Fill(black);
	// Left side
	CP_Graphics_BeginShape();

	CP_Graphics_AddVertex(0.0f, screen_bottom);
	CP_Graphics_AddVertex(center_x - 70, screen_bottom);
	CP_Graphics_AddVertex(center_x - 70, screen_bottom - 100);
	CP_Graphics_AddVertex(center_x - 158, screen_bottom - 100);
	CP_Graphics_AddVertex(center_x - 158, screen_bottom - 50);
	CP_Graphics_AddVertex(182.0f, screen_bottom - 50);
	CP_Graphics_AddVertex(182.0f, center_y + 143);
	CP_Graphics_AddVertex(center_x - 158, center_y + 143);
	CP_Graphics_AddVertex(center_x - 158, center_y + 216);
	CP_Graphics_AddVertex(center_x - 70, center_y + 216);
	CP_Graphics_AddVertex(center_x - 70, center_y - 90);
	CP_Graphics_AddVertex(center_x - 158, center_y - 90);
	CP_Graphics_AddVertex(center_x - 158, center_y + 40);
	CP_Graphics_AddVertex(228.0f, center_y + 40);
	CP_Graphics_AddVertex(228.0f, 125.0f);
	CP_Graphics_AddVertex(center_x - 158, 125.0f);
	CP_Graphics_AddVertex(center_x - 158, 203.0f);
	CP_Graphics_AddVertex(center_x - 70, 203.0f);
	CP_Graphics_AddVertex(center_x - 70, 0.0f);
	CP_Graphics_AddVertex(0.0f, 0.0f);

	CP_Graphics_EndShape();

	// Right side
	CP_Graphics_BeginShape();

	CP_Graphics_AddVertex(window_width, screen_bottom);
	CP_Graphics_AddVertex(center_x + 70, screen_bottom);
	CP_Graphics_AddVertex(center_x + 70, screen_bottom - 100);
	CP_Graphics_AddVertex(center_x + 158, screen_bottom - 100);
	CP_Graphics_AddVertex(center_x + 158, screen_bottom - 50);
	CP_Graphics_AddVertex(window_width - 182, screen_bottom - 50);
	CP_Graphics_AddVertex(window_width - 182, 180.0f);
	CP_Graphics_AddVertex(center_x + 158, 180.0f);
	CP_Graphics_AddVertex(center_x + 158, center_y + 216);
	CP_Graphics_AddVertex(center_x + 70, center_y + 216);
	CP_Graphics_AddVertex(center_x + 70, 0.0f);
	CP_Graphics_AddVertex(window_width, 0.0f);

	CP_Graphics_EndShape();
}

// Yar Xuan
// return 1 if player is going to collide with wall
int lvl4_wall_collision(int player, float player_x, float player_y) {
	float dt = CP_System_GetDt();
	float mvment = speed * dt;

	int window_width = CP_System_GetWindowWidth();
	int window_height = CP_System_GetWindowHeight();
	float center_x = window_width / 2.0f;
	float center_y = window_height / 2.0f;

	if (CP_Input_KeyDown(player == 1 ? KEY_W : KEY_UP)) {
		float end_y = player_y - mvment;
		// if player_y going above top left room & player_x within top left room
		if (end_y < 125 && player_x >= 228 && player_x <= center_x - 158 - player_w) {
			return 1;
		}
		// if player_y going above top left room entrance && player_x within entrance
		if (end_y + player_hat_height < 203 && player_x + player_w >= center_x - 158 && player_x <= center_x - 70) {
			return 1;
		}
		// if player_y going above right room & player_x within right room
		if (end_y < 180 && player_x >= center_x + 158 && player_x <= window_width - 182 - player_w) {
			return 1;
		}
		// if player_y going above bottom left room & player_x within bottom left room 
		if (end_y < center_y + 143 && end_y > center_y + 40 && player_x >= 182 && player_x < center_x - 158 - player_w) {
			return 1;
		}
		// if player_y going above bottom left room entrance & player_x within bot left room entrance
		if (end_y + player_hat_height < center_y + 216 && end_y >= center_y - 90 && (player_x + player_w >= center_x - 158 && player_x <= center_x - 70)) {
			return 1;
		}
		// if player_y going above right room entrance & player_x within right room entrance
		if (end_y + player_hat_height < center_y + 216 && player_x + player_w >= center_x + 70 && player_x <= center_x + 158) {
			return 1;
		}
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_S : KEY_DOWN)) {
		float end_y = player_y + mvment;
		// if player_y going below top left room & player_x within top left room
		if (end_y > center_y + 40 - player_h && end_y < center_y + 143 - 80 && player_x >= 228 && player_x <= center_x - 158 - player_w) {
			return 1;
		}
		// if player_y going below top left room entrance && player_x within entrance
		if (end_y > center_y - 90 - player_h && end_y < center_y + 216 - 80 && player_x + player_w >= center_x - 158 && player_x <= center_x - 70) {
			return 1;
		}
		// if player_y going below right room & player_x within right room
		if (end_y > window_height - 50 - player_h && player_x >= center_x + 158 && player_x <= window_width - 182 - player_w) {
			return 1;
		}
		// if player_y going below bottom left room & player_x within bottom left room 
		if (end_y > window_height - 50 - player_h && player_x >= 182 && player_x < center_x - 158 - player_w) {
			return 1;
		}
		// if player_y going below bottom left room entrance & player_x within bot left room entrance
		if (end_y > window_height - 100 - player_h && player_x + player_w >= center_x - 158 && player_x <= center_x - 70) {
			return 1;
		}
		// if player_y going below right room entrance & player_x within right room entrance
		if (end_y + player_hat_height > window_height - 100 - player_h && player_x + player_w >= center_x + 70 && player_x <= center_x + 158) {
			return 1;
		}
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_A : KEY_LEFT)) {
		float end_x = player_x - mvment;
		// if player_x going left of top left room & player_y within top left room
		if (end_x < 228 && player_y >= 125 && player_y + player_h < center_y + 40) {
			return 1;
		}
		// if player_x going left of corridor & player_y not in entrances
		if (end_x < center_x - 70 && end_x >= center_x - 158 &&
			!((player_y + player_hat_height >= 203 && player_y + player_h <= center_y - 90)
				|| (player_y + player_hat_height >= center_y + 216 && player_y + player_h <= window_height - 100))) {
			return 1;
		}
		// if player_x going left of right room & player_y not within right room entrance
		if (end_x < center_x + 158 && end_x >= center_x + 70 && 
			!(player_y + player_hat_height >= center_y + 216 && player_y + player_h <= window_height - 100)
			) {
			return 1;
		}
		// if player_x going left of bottom left room & player_y within bottom left room 
		if (end_x < 182 && player_y >= center_y + 143 && player_y + player_h <= window_height - 50) {
			return 1;
		}
	}
	if (CP_Input_KeyDown(player == 1 ? KEY_D : KEY_RIGHT)) {
		float end_x = player_x + mvment;
		// if player_x going right of top left room / bottom left room & 
		// player_y not within top left room / bottom left room entrance
		if (end_x + player_w > center_x - 158 && end_x + player_w < center_x - 70 &&
			!((player_y + player_hat_height >= 203 && player_y + player_h <= center_y - 90) ||
				(player_y + player_hat_height >= center_y + 216 && player_y + player_h <= window_height - 100))) {
			return 1;
		}
		// if player_x going right of corridor & player_y not in right room entrance
		if (end_x + player_w > center_x + 70 && end_x < center_x + 158 &&
			!(player_y + player_hat_height >= center_y + 216 && player_y + player_h <= window_height - 100)) {
			return 1;
		}
		// if player_x going right of right room & player_y within right room
		if (end_x + player_w > window_width - 182 && player_y >= 180 && player_y + player_h <= window_height - 50) {
			return 1;
		}
	}

	return 0;
}