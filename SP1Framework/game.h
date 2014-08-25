#ifndef _GAME_H
#define _GAME_H
#define MAPWIDTH 120
#define MAPHEIGHT 24
#define SIGNHEIGHT 12
#define SIGNWIDTH 38
#define NUMBEROFLEVELS 20

#include "Framework\timer.h"

extern unsigned char map[MAPHEIGHT][MAPWIDTH];
extern StopWatch g_timer;
extern bool g_quitGame;
extern bool spawnwhere;
extern int gamestate;
extern int checkLevel;
extern int checkPrevLevel;
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

struct Bullets_Properties{
	int x, y;
	bool faceWhere; // left = false, right = true
	int Damage;
	bool isRENDERED; // if 1, render. if 0, clear and remove
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
void checkForElement();
void resetElements();
void resetCounters();
void renderHP();
void renderMoney();
void renderUIborders();
void renderSign();

//Boss functions
void PianusStand1();
void PianusStand2();
void PianusLava1();
void PianusLava2();
void PianusLava3();
void PianusLaser1();
void PianusLaser2();
void PianusLaser3();
void PianusDeath1();
void PianusDeath2();
void PianusDeath3();
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
void BossDeath1();
void BossDeath2();
void BossDeath3();
void BossSplintEffect();
void BossMeteorEffect();
void updateSplint();
void updateMeteor();
void renderSplint();
void renderMeteor();
void checkBossStatus();
void checkCollisionSplint();
void checkCollisionMeteor();
void checkCollisionLava();
void checkCollisionLaser();

// Monster functions
void checkCollisionSnail();
void checkCollisionFloater();
void checkCollisionInnerFear();
void checkCollisionRat();
void checkCollisionWengyew();
void checkCollisionCatFish();
void updateSnails();
void updateFloater();
void updateInnerFear();
void updateRat();
void updateWengyew();
void updateCatFish();
void checkMonsterDead();
void renderMonster();

//player
void jump();
void gravity();
void checkforDeath();
void checkforSpike();
void spawnWhere();

//weapon
void Attack();
void spawnBullets();
void updateBullets();
void checkCollisionWithMonster();
void checkCollisionWithWall();

#endif // _GAME_H