/*!
© 2024 DIGIPEN INSTITUTE OF TECHNOLOGY SINGAPORE
@file main.c
@author Low JianLin (jianlin.low)
@author Gwen Leo Yuhan (leo.y)
@author Yar Xuan (xuan.yar)
@author Beh Shi Wei (beh.s)
*//*______________________________________________________________________*/

#include "cprocessing.h"
#include "stdbool.h"
#include "mainmenu/mainmenu.h"
#include "credits/Logo.h"

// global variables
float player_w = 47.0f, player_h = 80.0f, grinch_size = 130.0f;
float speed = 200.0f;

float game_start_time = 0.0f, game_complete_time;
double startTime;
double elapsedTime;
int draw;
double fadeInTime = 0.0;
bool LifeLostThisFrame = false;
int life[3] = { 255, 255, 255 };
int count;

float PresentP1X[6], PresentP1Y[6], PresentP2X[6], PresentP2Y[6];
int PresentP1Opacity[6], PresentP2Opacity[6];

void game_init(void)
{
	CP_System_SetWindowSize(1600, 900);
}

void game_update(void)
{
	CP_Engine_SetNextGameState(Logo_Init, Logo_Update, Logo_Exit);
}

void game_exit(void)
{
}

int main(void)
{
	CP_Engine_SetNextGameState(game_init, game_update, game_exit);
	CP_Engine_Run(0);
	return 0;
}