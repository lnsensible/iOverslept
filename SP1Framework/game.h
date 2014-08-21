#ifndef _GAME_H
#define _GAME_H

#include "Framework\timer.h"

extern unsigned char map[25][120];
extern StopWatch g_timer;
extern bool g_quitGame;
extern int gamestate;
extern int checkLevel;
extern int hasbeenDamaged;
extern int bossStatus;
extern int PlayerHealth;
extern const unsigned char FPS; // FPS of this game
extern const unsigned int frameTime; // time for each frame
extern double elapsedTime;
extern double deltaTime;
extern double skillDelay;
extern double bossFrameDelay;

     
extern bool rangeORmelee;             
extern bool rightORleft;          
extern COORD WEAPON;

struct bossAttack {
	int X;
	int Y;
};

struct Monster
{
	int x;
	int y;
	int	health;
};

enum Keys
{
    K_UP,
    K_DOWN,
    K_LEFT,
	K_C,
	K_E,
	K_Q,
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

//menu :D
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

//Boss functions
void PianusStand1();
void PianusStand2();
void PianusLava1();
void PianusLava2();
void PianusLava3();
void PianusLaser1();
void PianusLaser2();
void PianusLaser3();
void PianusLaserEffect();
void PianusLavaEffect();
void updateLaser();
void updateLava();
void renderLaser();
void renderLava();
void checkPianusStatus();
void checkCollisionLaser();
void checkCollisionLava();

void BossStand1();
void BossStand2();
void BossSplint1();
void BossSplint2();
void BossSplint3();
void BossMeteor1();
void BossMeteor2();
void BossMeteor3();
void BossSplintEffect();
void BossMeteorEffect();
void updateSplint();
void updateMeteor();
void renderSplint();
void renderMeteor();
void checkBossStatus();
void checkCollisionSplint();
void checkCollisionMeteor();

// Monster functions
void checkCollisionSnail();
void checkCollisionFloater();
void checkCollisionInnerFear();
void checkCollisionRat();
void updateSnails();
void updateFloater();
void updateInnerFear();
void updateRat();

//player
void jump();
void gravity();
void checkforDeath();
void checkforSpike();

//weapon
void WEAPON_PROPERTIES();
void Atk();

#endif // _GAME_H