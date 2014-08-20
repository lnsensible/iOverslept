#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern StopWatch g_timer;
extern bool g_quitGame;
extern int gamestate;
extern int checkLevel;
extern const unsigned char FPS; // FPS of this game
extern const unsigned int frameTime; // time for each frame

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
    K_RIGHT,
    K_ESCAPE,
	K_SPACE,
	K_ENTER,
    K_COUNT
};

enum Sequence
{
	MENU,
	GAME,
	ENDGAME,
	SHOP,
	LEVELMENU,
	LEVELONE,
	LEVELTWO,
	LEVELTHREE,
	LEVELFOUR,
	LEVELFIVE,
	LEVELSIX,
	LEVELSEVEN,
	LEVELEIGHT,
	LEVELNINE,
	LEVELTEN,
	DEATH,
};

void init();                // initialize your variables, allocate memory, etc
void getInput();            // get input from player
void update(double dt);     // update the game and the state of the game
void render();              // renders the current state of the game to the console
void shutdown();            // do clean up, free memory


//menu
void initmainmenu();
void updatemainmenu(double dt);
void rendermainmenu();

void initlevelmenu();
void updatelevelmenu(double dt);
void renderlevelmenu();

void initdeathmenu();
void updatedeathmenu(double dt);
void renderdeathmenu();

void initendmenu();
void updateendmenu(double dt);
void renderendmenu();

//player environment intewractions.
void checkForGoal();
void resetElements();

#endif // _GAME_H