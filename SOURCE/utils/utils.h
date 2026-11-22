/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file utils.h
@author Low JianLin (jianlin.low)
@author Gwen Leo Yuhan(leo.y)
@author Yar Xuan (xuan.yar)
@author Beh Shi Wei (beh.s)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#pragma once

// JianLin 
int CheckOverlap(float x1, float y1, float x2, float y2);
void timer(double* startTime, int* draw, double intervalGreen, double intervalRed);
// Gwen
int IsAreaClicked(float area_center_x, float area_center_y, float area_width, float area_height, float click_x, float click_y);
// Gwen & Yar Xuan
void move_player(int player, char img_mode, float* player_x, float* player_y, CP_Image* player_image, CP_Image player_up, CP_Image player_down, CP_Image player_left, CP_Image player_right);
// Gwen & Yar Xuan & Jianlin
void move_playerLevel2(int player, char img_mode, float* player_x, float* player_y, CP_Image* player_image, CP_Image player_front, CP_Image player_back, CP_Image player_left, CP_Image player_right);
// Jianlin
void handlePlayerDeath();
int PresentsCollectedP1(float p1_x, float p1_y, float presentX, float presentY);
int PresentsCollectedP2(float p1_x, float p1_y, float presentX, float presentY);
// Shi Wei
int checkGrinchCollide(float player_x, float player_y, float grinch_x, float grinch_y); 
