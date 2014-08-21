// This is the main file for the game logic and function
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
int gamestate = 0;
COORD charLocation;
COORD consoleSize;

unsigned char map[25][120]; // stores the level map
int checkLevel = 0; // Check current level
int hasLevelRendered = 0; // Check if level has been rendered. 0 = Not loaded, 1 = Loaded
int isJumping = 0; // Check if character is jumping. 0 = Not jumping, 1 = Jumping
int hasbeenStabbed = 0; // Check if character has been stabbed by a needle/spike to determine if spikes need to be re rendered
int hasbeenDamaged = 0; // Check if character was damaged. If yes, need to re-render HP. All to prevent flickering ); 0 = No change, 1 = Changed
int bossStatus = 0; // Check what the boss is currently doing. 0 = Standing, 1 = Using skill1, 2 = using skill2. 
int treasure = 0;//Treasure :DD
int isBossLevel = 0; //Check if it is a boss level. 0 = No, 1 = Boss, 2= Fishy

double canJump = 0; // Check if you have jumped in the past 0.8 ms
double jumpDelay = 0; // delay between y coordinate change while jumping
double fallDelay = 0; // delay between falling (no delay for initial fall)
double skillDelay = 0; // delay between using skills
double bossFrameDelay = 0; // delay between boss animations
double snailMoveDelay = 0; // delay between each snail movement :D
double floaterMoveDelay = 0; // delay between each floater movement
double InnerFearMoveDelay = 0; // delay between each InnerFear movement
double RatMoveDelay = 0; // delay between each Rat movement

int PlayerHealth = 3; // Player's HP. Default = 3.

struct Monster
{
	int x;
	int y;
	int	health;
};

std::vector<Monster> MonsterSnail;
std::vector<Monster> Floater;
std::vector<Monster> InnerFear;
std::vector<Monster> Rat;


struct bossAttack {
	int X;
	int Y;
};

std::vector<bossAttack> meteor;
std::vector<bossAttack> splint;
std::vector<bossAttack> laser;
std::vector<bossAttack> lava;

//menu ~ Gabriel Wong :)

void initmainmenu()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"Main Menu");

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	charLocation.X = 55;
	charLocation.Y = 20;
}
void updatemainmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_UP])
	{
		if (charLocation.Y == 20 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 20;
		}

		else if (charLocation.Y == 22)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 20;
		}

		else if (charLocation.Y == 24)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 22;
		}
	}

	if(keyPressed[K_DOWN])
	{
		if (charLocation.Y == 20 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 22;
		}

		else if (charLocation.Y == 22)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 24;
		}

		else if (charLocation.Y == 24)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 24;
		}
	}

	if(keyPressed[K_ENTER])
	{
		if(charLocation.Y == 20)
		{
			gamestate = LEVELMENU;
		}

		if(charLocation.Y == 22)
		{
			gamestate = SHOP;
		}

		if(charLocation.Y == 24)
		{
			g_quitGame = true;
		}
	}
	
	if(keyPressed[K_ESCAPE])
	{
		g_quitGame = true;
	}
}
void rendermainmenu()
{
	cls();
	std::string linemenuthing;
	for(int i = 0; i < 20; i++)
	{
		linemenuthing += (char)196;
	}
	gotoXY(48, 18);
	std::cout << (char)218 << linemenuthing << (char)191;
	gotoXY(57, 20);
	std::cout << "Play!";
	gotoXY(57, 22);
	std::cout << "Shop";
	gotoXY(57, 24);
	std::cout << "Quit";

	gotoXY(charLocation);
	colour(0x0C);
	std::cout << (char)16;
	colour(0x0F);
}

void initlevelmenu()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"Level Menu");

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	charLocation.X = 46; //default cursor position
	charLocation.Y = 23;
}
void updatelevelmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_LEFT])
	{
		if (charLocation.X != 46 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X -= 3;
		}
	}

	if(keyPressed[K_RIGHT])
	{
		if (charLocation.X != 73 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X += 3;
		}
	}

	if(keyPressed[K_DOWN])
	{
		if(charLocation.Y != 25)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y += 2;
		}
	}

	if(keyPressed[K_UP])
	{
		if(charLocation.Y != 23)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y -= 2;
		}
	}

	if(keyPressed[K_ENTER])
	{
		hasLevelRendered = 0;

		if(charLocation.X == 46)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 1;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 11;
			}
		}

		else if(charLocation.X == 49)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 2;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 12;
			}
		}

		else if(charLocation.X == 52)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 3;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 13;
			}
		}

		else if(charLocation.X == 55)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 4;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 14;
			}
		}

		else if(charLocation.X == 58)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 5;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 15;
			}
		}

		else if(charLocation.X == 61)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 6;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 16;
			}
		}

		else if(charLocation.X == 64)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 7;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 17;
			}
		}

		else if(charLocation.X == 67)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 8;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 18;
			}
		}

		else if(charLocation.X == 70)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 9;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 19;
			}
		}

		else if(charLocation.X == 73)
		{
			if(charLocation.Y == 23)
			{
				checkLevel = 10;
			}

			else if(charLocation.Y == 25)
			{
				checkLevel = 20;
			}
		}

		gamestate = GAME;

	}//keypress enter

	if(keyPressed[K_ESCAPE])
	{
		gamestate = MENU;
	}
}
void renderlevelmenu()
{
	cls();
	colour(0x0F);

	gotoXY(57, 20);
	std::cout << "Levels";
	gotoXY(46, 22);
	std::cout << "1";
	gotoXY(49, 22);
	std::cout << "2";
	gotoXY(52, 22);
	std::cout << "3";
	gotoXY(55, 22);
	std::cout << "4";
	gotoXY(58, 22);
	std::cout << "5";
	gotoXY(61, 22);
	std::cout << "6";
	gotoXY(64, 22);
	std::cout << "7";
	gotoXY(67, 22);
	std::cout << "8";
	gotoXY(70, 22);
	std::cout << "9";
	gotoXY(73, 22);
	std::cout << "10";

	gotoXY(46, 24);
	std::cout << "11";
	gotoXY(49, 24);
	std::cout << "12";
	gotoXY(52, 24);
	std::cout << "13";
	gotoXY(55, 24);
	std::cout << "14";
	gotoXY(58, 24);
	std::cout << "15";
	gotoXY(61, 24);
	std::cout << "16";
	gotoXY(64, 24);
	std::cout << "17";
	gotoXY(67, 24);
	std::cout << "18";
	gotoXY(70, 24);
	std::cout << "19";
	gotoXY(73, 24);
	std::cout << "20";

	gotoXY(charLocation);
	colour(0x0C);
	std::cout << (char)94;
	colour(0x0F);
}

void initdeathmenu()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"Death Menu");

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	charLocation.X = 50;
	charLocation.Y = 22;
}
void updatedeathmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_LEFT])
	{
		if (charLocation.X == 60 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 50;
		}

		else if(charLocation.X == 50)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 50;
		}
	}

	if(keyPressed[K_RIGHT])
	{
		if (charLocation.X == 60 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 60;
		}

		else if(charLocation.X == 50)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 60;
		}
	}

	if(keyPressed[K_ENTER])
	{
		if(charLocation.X == 60)
		{
			gamestate = LEVELMENU;
		}

		if(charLocation.X == 50)
		{
			gamestate = GAME;
		}
	}
}
void renderdeathmenu()
{
	cls();
	colour(0x0F);

	gotoXY(50, 20);
	colour(0x0C);
	std::cout << "YOU DIED :C TRY AGAIN?";
	gotoXY(52, 22);
	colour(0x0F);
	std::cout << "Yes :D";
	gotoXY(62, 22);
	std::cout << "SCREW IT I'M OUTTA HERE";

	colour(0x0C);
	gotoXY(charLocation);
	std::cout << (char)16;
	colour(0x0F);
}

void initendmenu()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"You Win!");

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	charLocation.X = 47;
	charLocation.Y = 22;
}
void updateendmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_LEFT])
	{
		if (charLocation.X == 63 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 47;
		}

		else if(charLocation.X == 47)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 47;
		}
	}

	if(keyPressed[K_RIGHT])
	{
		if (charLocation.X == 63 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 63;
		}

		else if(charLocation.X == 47)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 63;
		}
	}

	if(keyPressed[K_ENTER])
	{
		if(charLocation.X == 63)
		{
			if(checkLevel != 20)
			{
				checkLevel++;
			}
			gamestate = GAME;
		}

		if(charLocation.X == 47)
		{
			gamestate = LEVELMENU;
		}
	}
}
void renderendmenu()
{
	cls();
	colour(0x0F);

	gotoXY(45, 20);
	colour(0x0A);
	std::cout << "Level completed, Congratulations!";
	gotoXY(49, 22);
	colour(0x0F);
	std::cout << "Return menu";
	gotoXY(65, 22);
	std::cout << "Next level";

	colour(0x0C);
	gotoXY(charLocation);
	std::cout << (char)16;
	colour(0x0F);
}


void loadLevel(std::string filename) // loads level map from file.
{
	std::fstream LevelMap;
	LevelMap.open(filename);

	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			LevelMap >> map[i][j];
		}
	}

	LevelMap.close();
} 

void prepareLevel() // Prepares level map for cout
{
	resetElements();
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == '.' ) // Whitespace placeholder
			{
				map[i][j] = ' ';
			}
			if ( map[i][j] == 'C' ) //Character placeholder
			{
				charLocation.X = j; // Assign coordinates of placeholder
				charLocation.Y = i; // to actual character ~
				map[i][j] = ' '; // Remove character placeholder
			}
			if ( map[i][j] == 'x' ) // Floor trap placeholder
			{
				map[i][j] = 30;
			}
			if ( map[i][j] == 'X' ) // Ceiling trap placeholder
			{
				map[i][j] = 31;
			}
			if ( map[i][j] == 'n' ) // Wall trap placeholder ( a spike facing left )
			{
				map[i][j] = 17;
			}
			if ( map[i][j] == 'N' ) // Wall trap placeholder ( a spike facing right )
			{
				map[i][j] = 16;
			}
			if ( map[i][j] == 'S' ) // Snail Monster placeholder ( a @/' )
			{
				Monster Monstersnail;

				Monstersnail.x = j; // location of X-coordinates of snail
				Monstersnail.y = i; // location of Y-coordinates of snail
				Monstersnail.health = 2; // health of snail

				MonsterSnail.push_back(Monstersnail);
			}

			if ( map[i][j] == 'M' ) // Floater Monster placeholder ( a ascii 235 )
			{
				Monster floater;

				floater.x = j; // location of X-coordinates of floater
				floater.y = i; // location of Y-coordinates of floater
				floater.health = 1; // health of floater

				Floater.push_back(floater);
			}

			if ( map[i][j] == 'F' ) // InnerFear Monster placeholder 
			{
				Monster innerfear;

				innerfear.x = j; // location of X-coordinates of InnerFear
				innerfear.y = i; // location of Y-coordinates of InnerFear
				innerfear.health = 1; // health of InnerFear

				InnerFear.push_back(innerfear);
			}

			if ( map[i][j] == 'R' ) // Rat Monster placeholder 
			{
				Monster rat;

				rat.x = j; // location of X-coordinates of Rat
				rat.y = i; // location of Y-coordinates of Rat
				rat.health = 1; // health of Rat

				Rat.push_back(rat);
			}

			if ( map[i][j] == 'T' ) // TREASURE HORRYY SHEET $$$
			{
				map[i][j] = 15;
			}

			if ( map[i][j] == 'P' ) // Portal to next
			{
				map[i][j] = 239;
			}

			if ( map[i][j] == 'p' ) // Portal to back
			{
				map[i][j] = 234;
			}

		}
	}
}

void renderLevel() // Renders map into console
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			gotoXY(j, i); // go to XY coords respectively,
			if ( map[i][j] == '#')
			{
				std::cout << (char)219; // and print block to replace walls
			}

			if ( map[i][j] == 239)
			{
				colour(0x0A);
				std::cout << (char)239; // Portal next
				colour(0x0F);
			}

			if ( map[i][j] == 234)
			{
				colour(0x0A);
				std::cout << (char)234; // Portal back
				colour(0x0F);
			}

			else
			{
				std::cout << map[i][j]; // else print what's in the array
			}
		}
	}
	for (unsigned int i = 0; i < MonsterSnail.size(); i++)
	{
		gotoXY( MonsterSnail[i].x, MonsterSnail[i].y ); // spawns at XY coordinates 
		std::cout << "@/'"; // spawn snail appearance 
	}

	for (unsigned int i = 0; i < Floater.size(); i++)
	{
		gotoXY( Floater[i].x, Floater[i].y ); // spawns at XY coordinates 
		std::cout << (char)235; // spawn floater appearance 
	}

	for (unsigned int i = 0; i < InnerFear.size(); i++)
	{
		gotoXY( InnerFear[i].x, InnerFear[i].y ); // spawns at XY coordinates 
		std::cout << (char)12; // spawn InnerFear appearance 
	}

	for (unsigned int i = 0; i < Rat.size(); i++)
	{
		gotoXY( Rat[i].x, Rat[i].y ); // spawns at XY coordinates 
		 std::cout << "~~(_^" << (char)249 << ">"; // spawn Rat appearance 
	}
}

void renderSpikes() // re-render spikes after being stabbed
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 30 ) // Floor trap placeholder
			{
				gotoXY(j, i);
				std::cout << map[i][j];
			}
			if ( map[i][j] == 31 ) // Ceiling trap placeholder
			{
				gotoXY(j, i);
				std::cout << map[i][j];
			}
			if ( map[i][j] == 17 ) // Wall trap placeholder ( a spike facing left )
			{
				gotoXY(j, i);
				std::cout << map[i][j];
			}
			if ( map[i][j] == 16 ) // Wall trap placeholder ( a spike facing right )
			{
				gotoXY(j, i);
				std::cout << map[i][j];
			}
		}
	}
}

void renderHP() // displays amount of HP player still has.
{
	gotoXY(14, 26); // Clear HP section for render again
	std::cout << "        ";
	colour(0x0F);
	gotoXY(6, 26);
	std::cout << "Health: ";
	gotoXY(14, 26);
	colour(0x0C);
	for ( int i = 0; i < PlayerHealth; i++ )
	{
		std::cout << (char)3 << " ";
	}
	colour(0x0F);
	gotoXY(25, 26); // Clear HP section for render again
	std::cout << "          ";
}

void pianusStand1()
{
	gotoXY(65, 7);	std::cout << "                        :?              ";
	gotoXY(65, 8);	std::cout << "                      ~+?III=           ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?I,          ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??         ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?        ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::        ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~::::::::::::,,,::      ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "      =++++===~~:::::::::~==+++,:,,,    ";
	gotoXY(65, 16);	std::cout << "    :=++++====~~?+=~::::,:::~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << " ??IIII?~~==~~~:,~~~::::,,,:~==,,,,     ";
	gotoXY(65, 18);	std::cout << " IIIIII?:~:~:::::,+:,::::,,,,,,,,,,,,   ";
	gotoXY(65, 19);	std::cout << "~~=====~~::::~:~:~::::::~,,,,,,,,,,,,,, ";
	gotoXY(65, 20);	std::cout << "     +===~::~~~~~~~~~::~,:~+:,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "       +++++=~~~~~~~~~~,~==++++,,,,,,,, ";
}

void pianusStand2()
{
	gotoXY(65, 7);	std::cout << "                        :?              ";
	gotoXY(65, 8);	std::cout << "                      ~+?III=           ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?I,          ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??         ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?        ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::        ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::      ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "      =++++===~~:::::::::~==+++,:,,,    ";
	gotoXY(65, 16);	std::cout << "    :=++++====~~?+=~::::,:::~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << " ??IIII?~~==~~~:,~~~::::,,,:~=,,,,,     ";
	gotoXY(65, 18);	std::cout << " IIIIII?:~:~:::::,+:,::::,,,,,,,,,,,,   ";
	gotoXY(65, 19);	std::cout << "~~=====~~::::~:~:~::::::~=~,,,,,,,,,,,, ";
	gotoXY(65, 20);	std::cout << "     +===~::~~~~~~~~~::~,:~+:,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "       +++++=~~~~~~~~~~,~==+++,,,,,,,,, ";
}

void pianusLaser1()
{
	gotoXY(65, 7);	std::cout << "                        :?              ";
	gotoXY(65, 8);	std::cout << "                      ~+?III=           ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?I,          ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??         ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?        ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::        ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::      ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "    :I??++===~~~~::::::::=~=+++,:,,,,   ";
	gotoXY(65, 16);	std::cout << "    :=++++====~~?+=~::::,:::~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << "  ??IIII?~~==~~~:,~~~::::,,,:~=,,,,,    ";
	gotoXY(65, 18);	std::cout << "  ====~~:+==~~~====~:::,:::~~==,,,,,,,  ";
	gotoXY(65, 19);	std::cout << "   ====~~:+==~~~====~:::,:::~~==,,,,,,, ";
	gotoXY(65, 20);	std::cout << "   =,:~~~~?:~~~~~~~~~~~,,~=:,,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "  ========~~~~~~~~~~:~,,===+++?,,,,,,,, ";
}

void pianusLaser2()
{
	gotoXY(65, 7);	std::cout << "                        :?              ";
	gotoXY(65, 8);	std::cout << "                      ~+?III=           ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?I,          ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??         ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?        ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::        ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::      ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "    :I??++===~~~~::::::::=~=+++,:,,,,   ";
	gotoXY(65, 16);	std::cout << "    :=++++====~~?+=~::::,:::~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << "  ??IIII?~~==~~~:,~~~::::,,,:~=,,,,,    ";
	gotoXY(65, 18);	std::cout << "  ====~~:+==~~~====~:::,:::~~==,,,,,,   ";
	gotoXY(65, 19);	std::cout << "       :::~:~~~~::::::~~,,,,,,,,,,,,,,, ";
	gotoXY(65, 20);	std::cout << "   =,:~~~~?:~~~~~~~~~~~,,~=:,,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "  ========~~~~~~~~~~:~,,===+++?,,,,,,,, ";
}

void pianusLaser3()
{
	gotoXY(65, 7);	std::cout << "                        :?              ";
	gotoXY(65, 8);	std::cout << "                      ~+?III=           ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?I,          ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??         ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?        ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::        ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::      ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "    :I??++===~~~~::::::::=~=+++,:,,,,   ";
	gotoXY(65, 16);	std::cout << "  ====~~:+==~~~====~:::,:::~~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << "        :::~~::+7::::::~,,,:~==,,,,     ";
	gotoXY(65, 18);	std::cout << "         ,:~::::=I?~::::,,,,,,,,,,,,,   ";
	gotoXY(65, 19);	std::cout << "       :::~:~~~~::::::~~,,,,,,,,,,,,,,, ";
	gotoXY(65, 20);	std::cout << "   =,:~~~~?:~~~~~~~~~~~,,~=:,,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "  ========~~~~~~~~~~:~,,===+++?,,,,,,,, ";
}

void pianusLaserEffect()
{
	bossAttack Laser;
	Laser.X = 68;
	Laser.Y = 18;

	laser.push_back(Laser);
}

void updateLaser()
{
	for (unsigned int i = 0; i < laser.size(); i++ ) // when laser still moving lefts
	{
		if ( laser[i].X > 5 )
		{
			for ( int j = laser[0].Y -6; j < laser[0].Y +2; j++)
			{
				gotoXY( laser[i].X, j );
				if ( map[j][laser[i].X] == '#')
				{
					std::cout << (char)219; // and print block to replace walls
				}
				else
				{
					std::cout << map[j][laser[i].X]; // else print what's in the array
				}
			}
			laser[i].X-- ;
		}
		else // when laser reaches the left
		{
			for ( int j = laser[i].Y -6; j < laser[i].Y +2; j++) // remove the lazor
			{
				for ( int k = 66; k > 0; k--) // CLEAN UP THE MESS >:((
				{
					gotoXY(k, j);
					if ( map[j][k] == '#')
					{
						std::cout << (char)219; // and print block to replace walls
					}
					else
					{
						std::cout << map[j][k]; // else print what's in the array
					}
				}
			}

			laser.clear(); // removes laser
		}
	}
}

void renderLaser()
{
	for (unsigned int i = 0; i < laser.size(); i++ )
	{
		for ( int j = laser[i].Y -6; j < laser[i].Y +2; j++)
		{
			gotoXY( laser[i].X, j );
			std::cout << (char)27;
		}
	}

}

void pianusLava1()
{
	gotoXY(65, 7);	std::cout << "                        :?              ";
	gotoXY(65, 8);	std::cout << "                      ~+?III=           ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?I,          ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??         ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?        ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::        ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::      ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "    :I??++===~~~~::::::::=~=+++,:,,,,   ";
	gotoXY(65, 16);	std::cout << "    :=++++====~~?+=~::::,:::~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << "  ??IIII?~~==~~~:,~~~::::,,,:~=,,,,,    ";
	gotoXY(65, 18);	std::cout << "  ====~~:+==~~~====~:::,:::~~==,,,,,,,  ";
	gotoXY(65, 19);	std::cout << "   ====~~:+==~~~====~:::,:::~~==,,,,,,, ";
	gotoXY(65, 20);	std::cout << "   =,:~~~~?:~~~~~~~~~~~,,~=:,,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "  ========~~~~~~~~~~:~,,===+++?,,,,,,,, ";
}

void pianusLava2()
{
	gotoXY(65, 7);	std::cout << "                        :?              ";
	gotoXY(65, 8);	std::cout << "                      ~+?III=           ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?I,          ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??         ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?        ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::        ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::      ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "    :I??++===~~~~::::::::=~=+++,:,,,,   ";
	gotoXY(65, 16);	std::cout << "    :=++++====~~?+=~::::,:::~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << "  ??IIII?~~==~~~:,~~~::::,,,:~=,,,,,    ";
	gotoXY(65, 18);	std::cout << "  ====~~:+==~~~====~:::,:::~~==,,,,,,   ";
	gotoXY(65, 19);	std::cout << "       :::~:~~~~::::::~~,,,,,,,,,,,,,,, ";
	gotoXY(65, 20);	std::cout << "   =,:~~~~?:~~~~~~~~~~~,,~=:,,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "  ========~~~~~~~~~~:~,,===+++?,,,,,,,, ";
}

void pianusLava3()
{
	gotoXY(65, 7);	std::cout << "                        :?              ";
	gotoXY(65, 8);	std::cout << "                      ~+?III=           ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?I,          ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??         ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?        ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::        ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::      ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "    :I??++===~~~~::::::::=~=+++,:,,,,   ";
	gotoXY(65, 16);	std::cout << "  ====~~:+==~~~====~:::,:::~~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << "        :::~~::+7::::::~,,,:~==,,,,     ";
	gotoXY(65, 18);	std::cout << "         ,:~::::=I?~::::,,,,,,,,,,,,,   ";
	gotoXY(65, 19);	std::cout << "       :::~:~~~~::::::~~,,,,,,,,,,,,,,, ";
	gotoXY(65, 20);	std::cout << "   =,:~~~~?:~~~~~~~~~~~,,~=:,,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "  ========~~~~~~~~~~:~,,===+++?,,,,,,,, ";
}

void pianusLavaEffect()
{
	for ( int i = 5; i < 46; i++ )
	{
		bossAttack Lava;
		Lava.X = i;
		Lava.Y = 21;

		lava.push_back(Lava);
	}
}

void updateLava()
{
	if ( lava[0].Y > 17 )
	{
		for ( int i = 0; i < 41; i++)
		{
			lava[i].Y--;
		}
	}
	else // when lava reaches top platform
	{
		for ( int j = 5; j < 46; j++) // remove the lava
		{
			for ( int k = 20; k > 15; k--) // CLEAN UP THE MESS >:((
			{
				gotoXY(j, k);
				if ( map[k][j] == '#')
				{
					std::cout << (char)219; // and print block to replace walls
				}
				else
				{
					std::cout << map[k][j]; // else print what's in the array
				}
			}
		}
		
		lava.clear(); // remove lava
	}
}

void renderLava()
{
	for (unsigned int i = 0; i < lava.size(); i++ )
	{
		for (unsigned int j = 0; j < lava.size(); j++)
		{
			gotoXY( lava[j].X, lava[i].Y );
			std::cout << (char)30;
		}
	}
}

void bossStand1()
{
	gotoXY(60, 4);	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(60, 8);	std::cout << "    I777777IIIIIIII?,:,,";
	gotoXY(60, 9);	std::cout << "    II777IIIIIIIIIII?++=";
	gotoXY(60, 10);	std::cout << "   IIIIIIIIIIIII7III?+++~";
	gotoXY(60, 11);	std::cout << "   II+.=IIIIIII?..III+?+=";
	gotoXY(60, 12);	std::cout << "    I=.=IIIIIII?..III?++=~         7I7:    ";
	gotoXY(60, 13);	std::cout << "    ++III~I:IIII7I++I?++=~         ~~~:    ";
	gotoXY(60, 14);	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =         ";
	gotoXY(50, 15);	std::cout << "             +II          +I??7?++=~     =           ";
	gotoXY(50, 16);	std::cout << "             ?77              7I++=~    I";
	gotoXY(50, 17);	std::cout << "            I777              7I?=~~   I";
	gotoXY(50, 18);	std::cout << "            +777            77II?===   =";
	gotoXY(50, 19);	std::cout << "            +I            77IIII======";
	gotoXY(50, 20);	std::cout << "             +III7777777IIIIII?=~=";
	gotoXY(50, 21);	std::cout << "          ,~~~.+IIIIIIIIIII??+.~:,,";
}

void bossStand2()
{
	gotoXY(60, 4);
	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);
	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);
	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);
	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(60, 8);
	std::cout << "    I777777IIIIIIII?,:,,";
	gotoXY(60, 9);
	std::cout << "    II777IIIIIIIIIII?++=";
	gotoXY(60, 10);
	std::cout << "   IIIIIIIIIIIII7III?+++~";
	gotoXY(60, 11);
	std::cout << "   II+.=IIIIIII?..III+?+=";
	gotoXY(60, 12);
	std::cout << "    I=.=IIIIIII?..III?++=~              ";
	gotoXY(60, 13);
	std::cout << "    ++III~I:IIII7I++I?++=~         ??~~:";
	gotoXY(60, 14);
	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       = ,'   ";
	gotoXY(50, 15);
	std::cout << "             +II          +I??7?++=~     =        ";
	gotoXY(50, 16);
	std::cout << "             ?77              7I++=~    I";
	gotoXY(50, 17);
	std::cout << "            I777              7I?=~~   I";
	gotoXY(50, 18);
	std::cout << "            +777            77II?===   =";
	gotoXY(50, 19);
	std::cout << "            +I            77IIII======";
	gotoXY(50, 20);
	std::cout << "             +III7777777IIIIII?=~=";
	gotoXY(50, 21);
	std::cout << "          ,~~~.+IIIIIIIIIII??+.~:,,";
}

void bossMeteor1()
{
	gotoXY(60, 4);
	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);
	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);
	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);
	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(56, 8);
	std::cout << ",I??    I777777IIIIIIII?,:,,";
	gotoXY(55, 9);
	std::cout << ":I77+7+.?II777IIIIIIIIIII?++=           ";
	gotoXY(54, 10);
	std::cout << ",?7=++I~?IIIIIIIIIIIIIIII7III?+++~      ";
	gotoXY(53, 11);
	std::cout << "=.=777=?+?II+.=IIIIIII?..III+?+=               ";
	gotoXY(60, 12);
	std::cout << "    I=.=IIIIIII?..III?++=~              ";
	gotoXY(60, 13);
	std::cout << "    ++III~I:IIII7I++I?++=~         ??~~:";
	gotoXY(60, 14);
	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       = ,'   ";
	gotoXY(60, 15);
	std::cout << "   +II          +I??7?++=~     =        ";
	gotoXY(60, 16);
	std::cout << "   ?77              7I++=~    I         ";
	gotoXY(60, 17);
	std::cout << "  I777              7I?=~~   I          ";
	gotoXY(60, 18);
	std::cout << "  +777            77II?===   =          ";
	gotoXY(60, 19);
	std::cout << "  +I            77IIII======            ";
	gotoXY(60, 20);
	std::cout << "   +III7777777IIIIII?=~=";
	gotoXY(60, 21);
	std::cout << ",~~~.+IIIIIIIIIII??+.~:,,";
	
}

void bossMeteor2()
{
	gotoXY(60, 4);
	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);
	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);
	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);
	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(56, 8);
	std::cout << " ,I??   I777777IIIIIIII?,:,,";
	gotoXY(55, 9);
	std::cout << " :I77+7+.II777IIIIIIIIIII?++=";
	gotoXY(54, 10);
	std::cout << " ,?7=++I~IIIIIIIIIIIIIIII7III?+++~     ";
	gotoXY(53, 11);
	std::cout << "  =.=777=?II+.=IIIIIII?..III+?+=            ?";
	gotoXY(60, 12);
	std::cout << "    I=.=IIIIIII?..III?++=~          ?  ";
	gotoXY(60, 13);
	std::cout << "    ++III~I:IIII7I++I?++=~         ?    ";
	gotoXY(60, 14);
	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =     ";
	gotoXY(60, 15);
	std::cout << "   +II          +I??7?++=~     =";
	gotoXY(60, 16);
	std::cout << "   ?77              7I++=~    I";
	gotoXY(60, 17);
	std::cout << "  I777              7I?=~~   I";
	gotoXY(60, 18);
	std::cout << "  +777            77II?===   =";
	gotoXY(60, 19);
	std::cout << "  +I            77IIII======";
	gotoXY(60, 20);
	std::cout << "   +III7777777IIIIII?=~=";
	gotoXY(60, 21);
	std::cout << ",~~~.+IIIIIIIIIII??+.~:,,";
	
}

void bossMeteor3()
{
	gotoXY(60, 4);
	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);
	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);
	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);
	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(56, 8);
	std::cout << "        I777777IIIIIIII?,:,,";
	gotoXY(55, 9);
	std::cout << "         II777IIIIIIIIIII?++=";
	gotoXY(54, 10);
	std::cout << "       I~IIIIIIIIIIIIIIII7III?+++~     ";
	gotoXY(53, 11);
	std::cout << "          II+.=IIIIIII?..III+?+=             ";
	gotoXY(60, 12);
	std::cout << "    I=.=IIIIIII?..III?++=~          ???";
	gotoXY(60, 13);
	std::cout << "    ++III~I:IIII7I++I?++=~         ?    ";
	gotoXY(60, 14);
	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =     ";
	gotoXY(60, 15);
	std::cout << "   +II          +I??7?++=~     =";
	gotoXY(60, 16);
	std::cout << "   ?77              7I++=~    I";
	gotoXY(60, 17);
	std::cout << "  I777              7I?=~~   I";
	gotoXY(60, 18);
	std::cout << "  +777            77II?===   =";
	gotoXY(60, 19);
	std::cout << "  +I            77IIII======";
	gotoXY(60, 20);
	std::cout << "   +III7777777IIIIII?=~=";
	gotoXY(60, 21);
	std::cout << ",~~~.+IIIIIIIIIII??+.~:,,";
}

void bossMeteorEffect() // spawns meteors !
{
	bossAttack Meteor;
	Meteor.X = 13;
	Meteor.Y = 0;

	meteor.push_back(Meteor);

	Meteor.X = 29;

	meteor.push_back(Meteor);
	std::cout << meteor.size();
}

void updateMeteor() // moves meteors / delete meteors and adjust coordinates
{
	gotoXY(20, 3);
	std::cout << "        "; // clean up mess after spawning
	gotoXY(36, 3);
	std::cout << "         ";
	for (unsigned int i = 0; i < meteor.size(); i++ ) // for all the meteors
	{
		if ( meteor[i].Y < 19 ) // when meteor is still falling ~
		{
			for ( int j = meteor[i].Y -2; j < meteor[i].Y +3; j++) //clean up the path behind the meteor 
			{
				for ( int k = meteor[i].X -5; k < meteor[i].X +6; k++) //  WHAT THE METEOR DESTROYEDDD.
				{
					if ( j < 0 ) // lowest Y coord is 0.
						j = 0;

					gotoXY(k, j); // go to XY coords respectively,
					if ( map[j][k] == '#')
					{
						std::cout << (char)219; // and print block to replace walls
					}
					else
					{
						std::cout << map[j][k]; // else print what's in the array
					}
				}
			}
		 meteor[i].Y++;
		}
		else // when meteor hits the ground
		{
			for ( int j = meteor[i].Y -2; j < meteor[i].Y +3; j++) //clean up the ground
			{
				for ( int k = meteor[i].X -5; k < meteor[i].X +6; k++) // CLEAN UP THE GROUNDD >:((
				{
					gotoXY(k, j);
					if ( map[j][k] == '#')
					{
						std::cout << (char)219; // and print block to replace walls
					}
					else
					{
						std::cout << map[j][k]; // else print what's in the array
					}
				}
			}
		}
	}
	if ( meteor[0].Y > 18 )
		meteor.clear(); // clear meteors when reached ground
}

void renderMeteor() // cout meteors to console
{
	for (unsigned int i = 0; i < meteor.size(); i++ )
	{
		gotoXY( meteor[i].X -5, meteor[i].Y );
		std::cout << "x@*(&@(*&%x";
		gotoXY( meteor[i].X -5, meteor[i].Y +1 );
		std::cout << "'x?HQ(*@&x'";
		gotoXY( meteor[i].X -5, meteor[i].Y -1 );
		std::cout << ",xQ)(&@FJx,";
		gotoXY( meteor[i].X -5, meteor[i].Y +2 );
		std::cout << " 'xxxxxxx' ";
		gotoXY( meteor[i].X -5, meteor[i].Y -2 );
		std::cout << " ,xxxxxxx, ";
	}

}

void bossSplint1()
{
	gotoXY(60, 4);
	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);
	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);
	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);
	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(60, 8);
	std::cout << "    I777777IIIIIIII?,:,,";
	gotoXY(60, 9); 
	std::cout << "    II777IIIIIIIIIII?++=";
	gotoXY(60, 10);
	std::cout << "   IIIIIIIIIIIII7III?+++~";
	gotoXY(60, 11);
	std::cout << "   II+.=IIIIIII?..III+?+=";
	gotoXY(60, 12);
	std::cout << "    I=.=IIIIIII?..III?++=~         7I7:    ";
	gotoXY(60, 13);
	std::cout << "    ++III~I:IIII7I++I?++=~         ~~~:    ";
	gotoXY(60, 14);
	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =       ";
	gotoXY(60, 15);
	std::cout << "   +II          +I??7?++=~     =";
	gotoXY(60, 16);
	std::cout << "   ?77              7I++=~    I";
	gotoXY(60, 17);
	std::cout << "  I777              7I?=~~   I";
	gotoXY(60, 18);
	std::cout << "  +777            77II?===   =";
	gotoXY(50, 19);
	std::cout << " =???++==~= +I            77IIII======";
	gotoXY(51, 20);
	std::cout << " ++???=~~   +III7777777IIIIII?=~=";
	gotoXY(51, 21);
	std::cout << " =????=~=,~~~.+IIIIIIIIIII??+.~:,,";
}

void bossSplint2()
{
	gotoXY(60, 4);
	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);
	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);
	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);
	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(60, 8);
	std::cout << "    I777777IIIIIIII?,:,,";
	gotoXY(60, 9); 
	std::cout << "    II777IIIIIIIIIII?++=";
	gotoXY(60, 10);
	std::cout << "   IIIIIIIIIIIII7III?+++~";
	gotoXY(60, 11);
	std::cout << "   II+.=IIIIIII?..III+?+=";
	gotoXY(60, 12);
	std::cout << "    I=.=IIIIIII?..III?++=~         7I7:       ";
	gotoXY(60, 13);
	std::cout << "    ++III~I:IIII7I++I?++=~         ~  ?      ";
	gotoXY(60, 14);
	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =         ";
	gotoXY(60, 15);
	std::cout << "   +II          +I??7?++=~     =";
	gotoXY(60, 16);
	std::cout << "   ?77              7I++=~    I";
	gotoXY(60, 17);
	std::cout << "  I777              7I?=~~   I";
	gotoXY(50, 18);
	std::cout << "     xx     +777            77II?===   =";
	gotoXY(50, 19);
	std::cout << " =???++==~= +I            77IIII======";
	gotoXY(51, 20);
	std::cout << " ++???=~~   +III7777777IIIIII?=~=";
	gotoXY(51, 21);
	std::cout << " =????=~=,~~~.+IIIIIIIIIII??+.~:,,";
}

void bossSplint3()
{
	gotoXY(60, 4);
	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);
	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);
	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);
	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(60, 8);
	std::cout << "    I777777IIIIIIII?,:,,";
	gotoXY(60, 9); 
	std::cout << "    II777IIIIIIIIIII?++=";
	gotoXY(60, 10);
	std::cout << "   IIIIIIIIIIIII7III?+++~";
	gotoXY(60, 11);
	std::cout << "   II+.=IIIIIII?..III+?+=";
	gotoXY(60, 12);
	std::cout << "    I=.=IIIIIII?..III?++=~         7I7:    ";
	gotoXY(60, 13);
	std::cout << "    ++III~I:IIII7I++I?++=~         ~~~:   ";
	gotoXY(60, 14);
	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =       ";
	gotoXY(60, 15);
	std::cout << "   +II          +I??7?++=~     =";
	gotoXY(60, 16);
	std::cout << "   ?77              7I++=~    I";
	gotoXY(50, 17);
	std::cout << "     xx     I777              7I?=~~   I";
	gotoXY(50, 18);
	std::cout << "    xxxx    +777            77II?===   =";
	gotoXY(50, 19);
	std::cout << " =???++==~= +I            77IIII======";
	gotoXY(51, 20);
	std::cout << " ++???=~~   +III7777777IIIIII?=~=";
	gotoXY(51, 21);
	std::cout << " =????=~=,~~~.+IIIIIIIIIII??+.~:,,";
}

void bossSplintEffect()
{
	bossAttack Splint;
	Splint.X = 22;
	Splint.Y = 22;
	
	splint.push_back(Splint);
}

void updateSplint()
{
	for (unsigned int i = 0; i < splint.size(); i++ ) // when spike still moving upwards
	{
		if ( splint[i].Y > 3 )
		{
			splint[i].Y--;
		}
		else // when spike reaches the top
		{
			for ( int j = splint[i].X -3; j < splint[i].X +2; j++) // remove the spikes
			{
				for ( int k = 2; k < 22; k++) // CLEAN UP THE MESS >:((
				{
					gotoXY(j, k);
					if ( map[k][j] == '#')
					{
						std::cout << (char)219; // and print block to replace walls
					}
					else
					{
						std::cout << map[k][j]; // else print what's in the array
					}
				}
			}
			splint.clear();
		}
	}
}

void renderSplint()
{
	for (unsigned int i = 0; i < splint.size(); i++ )
	{
		gotoXY( splint[i].X -3, splint[i].Y );
		std::cout << (char)24 << (char)24 << (char)24 << (char)24 << (char)24;
	}

}

void checkforSpike() // checks if character is standing on a trap.
{
	if ( map[charLocation.Y][charLocation.X] == 16 || map[charLocation.Y][charLocation.X] == 17 || map[charLocation.Y][charLocation.X] == 30 || map[charLocation.Y][charLocation.X] == 31 ) // You're standing on a SPIKEEE
	{
		hasbeenStabbed = 1;
		hasbeenDamaged = 1;
		if ( PlayerHealth > 0 )
			PlayerHealth--;
	}
}

void checkForGoal()
{
	if (map[charLocation.Y][charLocation.X] == 239)
	{
		if(checkLevel != 20)
		{
			checkLevel++;
		}
		init();
		gamestate = GAME;
	}

	if (map[charLocation.Y][charLocation.X] == 234)
	{
		if(checkLevel != 1)
		{
			checkLevel--;
		}
		init();
		gamestate = GAME;
	}
}

void checkForTreasure()
{
	if (map[charLocation.Y][charLocation.X] == 15)
	{
		treasure = treasure + 1;
	}
}
 
void checkCollisionSplint()
{
	if ( splint.size() != 0 ) // confirming there is a splint
	{
		if ( charLocation.X >= splint[0].X -3 && charLocation.X <= splint[0].X +1 ) // if player standing within x coordinates of splint attack
		{
			if ( charLocation.Y >= splint[0].Y ) // if player is within the splint
			{
				hasbeenDamaged = 1;
				if ( PlayerHealth > 0 )
					PlayerHealth--;
			}
		}
	}
}

void checkCollisionMeteor()
{
	if ( meteor.size() != 0 )
	{
		for ( unsigned int i = 0; i < meteor.size(); i++ )
		{
			if ( charLocation.X >= meteor[i].X -5 && charLocation.X <= meteor[i].X +5 ) // if player standing within x coordinates of meteors
			{
				if ( charLocation.Y >= meteor[i].Y -2 && charLocation.Y <= meteor[i].Y +2 ) // if player is within the meteor
				{
					hasbeenDamaged = 1;
					if ( PlayerHealth > 0 )
						PlayerHealth--;
				}
			}
		}
	}
}

void checkCollisionSnail()
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'S') // if snail spotted !
			{
				if ( charLocation.X >= j && charLocation.X <= j+2 ) // when within x coordinates of snail
				{
					if ( charLocation.Y == i ) //when within y coordinate of snail
					{
						hasbeenDamaged = 1;
						if ( PlayerHealth > 0 )
							PlayerHealth--;
					}
				}
			}
		}
	}
}

void checkCollisionFloater()
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'M') // if floater spotted !
			{
				if ( charLocation.X == j ) // when within x coordinates of floater
				{
					if ( charLocation.Y == i ) //when within y coordinate of floater
					{
						hasbeenDamaged = 1;
						if ( PlayerHealth > 0 )
							PlayerHealth--;
					}
				}
			}
		}
	}
}

void checkCollisionInnerFear()
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'F') // if InnerFear spotted !
			{
				if ( charLocation.X == j ) // when within x coordinates of InnerFear
				{
					if ( charLocation.Y == i ) //when within y coordinate of InnerFear
					{
						hasbeenDamaged = 1;
						if ( PlayerHealth > 0 )
							PlayerHealth--;
					}
				}
			}
		}
	}
}

void checkCollisionRat()
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'R') // if Rat spotted !
			{
				if ( charLocation.X >= j && charLocation.X <= j+7 ) // when within x coordinates of Rat
				{
					if ( charLocation.Y == i ) //when within y coordinate of Rat
					{
						hasbeenDamaged = 1;
						if ( PlayerHealth > 0 )
							PlayerHealth--;
					}
				}
			}
		}
	}
}

void updateSnails() // snail movement update
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'S' )
			{
				if ( rand() % 2 == 0 ) // movement left
				{
					if ( map[i][j-1] != '#' && map[i+1][j-1] == '#' )
					{
						gotoXY(j, i);
						std::cout << "   ";
						map[i][j] = ' ';
						map[i][j-1] = 'S';
					}
				}
				else // movement right
				{
					if ( map[i][j+3] != '#' && map[i+1][j+1] == '#' )
					{
						gotoXY(j, i);
						std::cout << "   ";
						map[i][j] = ' ';
						map[i][j+1] = 'S';
					}
				}
			}
		}
	}
}

void updateFloater() // floater movement update
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'M' )
			{
				if ( rand() % 2 == 0 ) // movement left
				{
					if ( map[i][j-1] != '#' && map[i+1][j-1] == '#' )
					{
						gotoXY(j, i);
						std::cout << " ";
						map[i][j] = ' ';
						map[i][j-1] = 'M';
					}
				}
				else // movement right
				{
					if ( map[i][j+1] != '#' && map[i+1][j+1] == '#' )
					{
						gotoXY(j, i);
						std::cout << " ";
						map[i][j] = ' ';
						map[i][j+1] = 'M';
					}
				}
			}
		}
	}
}

void updateInnerFear() // InnerFear movement update
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'F' )
			{
				if ( rand() % 2 == 0 ) // movement left
				{
					if ( map[i][j-1] != '#' && map[i+1][j-1] == '#' )
					{
						gotoXY(j, i);
						std::cout << " ";
						map[i][j] = ' ';
						map[i][j-1] = 'F';
					}
				}
				else // movement right
				{
					if ( map[i][j+1] != '#' && map[i+1][j+1] == '#' )
					{
						gotoXY(j, i);
						std::cout << " ";
						map[i][j] = ' ';
						map[i][j+1] = 'F';
					}
				}
			}
		}
	}
}

void updateRat() // Rat movement update
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'R' )
			{
				if ( rand() % 2 == 0 ) // movement left
				{
					if ( map[i][j-1] != '#' && map[i+1][j-1] == '#' )
					{
						gotoXY(j, i);
						std::cout << "       ";
						map[i][j] = ' ';
						map[i][j-1] = 'R';
					}
				}
				else // movement right
				{
					if ( map[i][j+7] != '#' && map[i+1][j+7] == '#' )
					{
						gotoXY(j, i);
						std::cout << "       ";
						map[i][j] = ' ';
						map[i][j+1] = 'R';
					}
				}
			}
		}
	}
}

void renderMonster() // re-render mobs after being hit
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'S' ) // re-render snails after being hit
			{
				gotoXY(j, i);
				std::cout << "@/'";
			}
			if ( map[i][j] == 'M' ) // re-render Floaters
			{
				gotoXY(j, i);
				std::cout << (char)235;
			}
			if ( map[i][j] == 'F' ) // re-render InnerFear after being hit
			{
				gotoXY(j, i);
				std::cout << (char)12;
			}
			if ( map[i][j] == 'R' ) // re-render Rat after being hit
			{
				gotoXY(j, i);
				std::cout << "~~(_^" << (char)249 << ">";
			}
		}	
	}
}

void checkforDeath()
{
	if ( PlayerHealth <= 0 )
	{
		gamestate = DEATH;
	}
}

void resetElements() // removes monsters and effects on the map
{
	MonsterSnail.clear();
	Floater.clear();
	InnerFear.clear();
	Rat.clear();
	meteor.clear();
	splint.clear();
	laser.clear();
	lava.clear();
}

void checkBossStatus()
{
	if ( skillDelay > 5.0 )
	{
		bossStatus = ( rand() % 2 + 1 ); // Changes boss status to either 1 or 2 ( use either skill1 or skill2 ).
		skillDelay = 0.0; // reset skillDelay;
	}
    else if ( skillDelay < 0.5 && bossStatus == 0 )
	{
		bossStatus = 0; // not using skill, boss is standing
	}

	if ( bossStatus == 0 ) // when boss is standing
	{
		if ( bossFrameDelay > 1.0 ) // first frame
		{
			if ( bossFrameDelay > 2.0 ) //second frame
			{
				bossStand2();
				bossFrameDelay = 0.0;
			}
			else
			{
				bossStand1();
			}
		}
	}
	else if ( bossStatus == 1 ) // boss is using first skill (meteor)
	{
		if ( bossFrameDelay > 1.0 ) // first frame
		{
			if ( bossFrameDelay > 2.0 && bossFrameDelay <= 3.0) // second frame
			{
				bossMeteor2();
			}
			else if ( bossFrameDelay > 3.0 ) // third frame
			{
				bossMeteor3();
				bossMeteorEffect();
				bossFrameDelay = 0;
				bossStatus = 0;
				skillDelay = 0;
				// reset to standing animation ~
			}
			else
			{
				bossMeteor1();
			}
		}
	}
	else if ( bossStatus == 2 )
	{
		if ( bossFrameDelay > 1.0 ) // first frame
		{
			if ( bossFrameDelay > 2.0 && bossFrameDelay <= 3.0) // second frame
			{
				bossSplint2();
			}
			else if ( bossFrameDelay > 3.0 ) // third frame
			{
				bossSplint3();
				bossSplintEffect();
				bossFrameDelay = 0;
				bossStatus = 0;
				skillDelay = 0;
				// reset to standing animation ~
			}
			else
			{
				bossSplint1();
			}
		}
	}
}

void checkPianusStatus()
{
	if ( skillDelay > 5.0 )
	{
		bossStatus = ( rand() % 2 + 1 ); // Changes boss status to either 1 or 2 ( use either skill1 or skill2 ).
		skillDelay = 0.0; // reset skillDelay;
	}
    else if ( skillDelay < 0.5 && bossStatus == 0 )
	{
		bossStatus = 0; // not using skill, boss is standing
	}

	if ( bossStatus == 0 ) // when boss is standing
	{
		if ( bossFrameDelay > 1.0 ) // first frame
		{
			if ( bossFrameDelay > 2.0 ) //second frame
			{
				pianusStand2();
				bossFrameDelay = 0.0;
			}
			else
			{
				pianusStand1();
			}
		}
	}
	else if ( bossStatus == 1 ) // boss is using first skill (meteor)
	{
		if ( bossFrameDelay > 1.0 ) // first frame
		{
			if ( bossFrameDelay > 2.0 && bossFrameDelay <= 3.0) // second frame
			{
				pianusLaser2();
			}
			else if ( bossFrameDelay > 3.0 ) // third frame
			{
				pianusLaser3();
				pianusLaserEffect();
				bossFrameDelay = 0;
				bossStatus = 0;
				skillDelay = 0;
				// reset to standing animation ~
			}
			else
			{
				pianusLaser1();
			}
		}
	}
	else if ( bossStatus == 2 )
	{
		if ( bossFrameDelay > 1.0 ) // first frame
		{
			if ( bossFrameDelay > 2.0 && bossFrameDelay <= 3.0) // second frame
			{
				pianusLava2();
			}
			else if ( bossFrameDelay > 3.0 ) // third frame
			{
				pianusLava3();
				pianusLavaEffect();
				bossFrameDelay = 0;
				bossStatus = 0;
				skillDelay = 0;
				// reset to standing animation ~
			}
			else
			{
				pianusLava1();
			}
		}
	}
}

void jump()
{
	if ( map[charLocation.Y+1][charLocation.X] == '#' && map[charLocation.Y-1][charLocation.X] != '#' && canJump > 0.800 ) // You're standing on the ground, and there's no ceiling above you, and you haven't jumped in the last 0.8 seconds
	{
		Beep(1000,30);
		isJumping = 1;
		canJump = 0.0;
		gotoXY(charLocation); // Go to character's location,
		std::cout << " "; //and clear it! (prevent screen flicker)
		--charLocation.Y; // Initial Jump.
		jumpDelay = 0; // Reset delay since we jumped.
		render();
		while ( jumpDelay < 0.100 ) // You are in the middle of jumping, but still want to be able to take in input!
		{
			getInput();
			update(g_timer.getElapsedTime());
			render();
			g_timer.waitUntil(frameTime);
		}
		if ( map[charLocation.Y-1][charLocation.X] != '#' && isJumping == 1 ) // You are mid jump. If there's no ceiling above you, continue jumping
		{
			gotoXY(charLocation); // Go to character's location,
			std::cout << " "; //and clear it! (prevent screen flicker)
			--charLocation.Y; // Second Jump
			jumpDelay = 0; // Reset delay since we jumped.
			while ( jumpDelay < 0.100 ) // You are in the middle of jumping, but still want to be able to take in input.
			{
				getInput();
				update(g_timer.getElapsedTime());
				render();
				g_timer.waitUntil(frameTime);
			}
			if ( map[charLocation.Y-1][charLocation.X] != '#' && isJumping == 1) // You are mid jump. If there's no ceiling above you, continue jumping
			{
				gotoXY(charLocation); // Go to character's location,
				std::cout << " "; //and clear it! (prevent screen flicker)
				--charLocation.Y; // Third Jump
				jumpDelay = 0; // Reset delay since we jumped.
				while ( jumpDelay < 0.100 ) // You are in the middle of jumping, but still want to be able to take in input.
				{
					getInput();
					update(g_timer.getElapsedTime());
					render();
					g_timer.waitUntil(frameTime);
				}
				isJumping = 0;
			}
			else if ( map[charLocation.Y-1][charLocation.X] == '#' ) // If there is a ceiling, stop the jump.
			{
				isJumping = 0;
			}
		}
		else if ( map[charLocation.Y-1][charLocation.X] == '#' ) // If there is a ceiling, stop the jump.
			{
				isJumping = 0;
			}
	}
}

void gravity() // screw physics
{
	if ( map[charLocation.Y+1][charLocation.X] != '#' && isJumping == 0 ) // OMG THERE'S NO FLOOR BUT IM' NOT JUMPING
	{
		while ( fallDelay > 0.100 ) // Haven't fell within last 100ms
		{
			gotoXY(charLocation); // Clears character to prevent
			std::cout << " "; // screen flickering... >:(
			charLocation.Y++; // Fall!
			fallDelay = 0;
		}
	}
}

void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.

    elapsedTime = 0.0;
	hasLevelRendered = 0;
	skillDelay = 0.0;
	fallDelay = 0.0;
	jumpDelay = 0.0;
	snailMoveDelay = 0.0;
	RatMoveDelay = 0.0;

	PlayerHealth = 3;//-------------------------

	hasbeenStabbed = 0;
	hasbeenDamaged = 0;
	bossStatus = 0;
	isBossLevel = 0;

	//loads level from file
	if ( checkLevel == 1 )
	{
		isBossLevel = 0;
		loadLevel("level1.txt");
		SetConsoleTitle(L"Level One");
	}
	else if ( checkLevel == 2 )
	{
		isBossLevel = 0;
		loadLevel("level2.txt");
		SetConsoleTitle(L"Level Two");
	}
	else if ( checkLevel == 3 )
	{
		isBossLevel = 0;
		loadLevel("level3.txt");
		SetConsoleTitle(L"Level Three");
	}
	else if ( checkLevel == 4 )
	{
		isBossLevel = 0;
		loadLevel("level4.txt");
		SetConsoleTitle(L"Level Four");
	}
	else if ( checkLevel == 5 )
	{
		isBossLevel = 0;
		loadLevel("level5.txt");
		SetConsoleTitle(L"Level Five");
	}
	else if ( checkLevel == 6 )
	{
		isBossLevel = 0;
		loadLevel("level6.txt");
		SetConsoleTitle(L"Level Six");
	}
	else if ( checkLevel == 7 )
	{
		isBossLevel = 0;
		loadLevel("level7.txt");
		SetConsoleTitle(L"Level Seven");
	}
	else if ( checkLevel == 8 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Eight");
		loadLevel("level8.txt");
	}
	else if ( checkLevel == 9 )
	{
		isBossLevel = 0;
		loadLevel("level9.txt");
		SetConsoleTitle(L"Level Nine");
	}
	else if ( checkLevel == 10 )
	{
		isBossLevel = 1;
		SetConsoleTitle(L"Level Ten");
		loadLevel("level10.txt");
	}
	else if ( checkLevel == 11 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Eleven");
		loadLevel("level11.txt");
	}
	else if ( checkLevel == 12 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Twelve");
		loadLevel("level12.txt");
	}
	else if ( checkLevel == 13 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Thirteen");
		loadLevel("level13.txt");
	}
	else if ( checkLevel == 14 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Fourteen");
		loadLevel("level14.txt");
	}
	else if ( checkLevel == 15 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Fifteen");
		loadLevel("level15.txt");
	}
	else if ( checkLevel == 16 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Sixteen");
		loadLevel("level16.txt");
	}
	else if ( checkLevel == 17 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Seventeen");
		loadLevel("level17.txt");
	}
	else if ( checkLevel == 18 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Eighteen");
		loadLevel("level18.txt");
	}
	else if ( checkLevel == 19 )
	{
		isBossLevel = 0;
		SetConsoleTitle(L"Level Nineteen");
		loadLevel("level19.txt");
	}
	else if ( checkLevel == 20 )
	{
		isBossLevel = 2;
		SetConsoleTitle(L"Level Twenty");
		loadLevel("level20.txt");
	}
	// prepares map for rendering
	prepareLevel();
}

void shutdown()
{
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}

void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
}

void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
	jumpDelay += dt;
	fallDelay += dt;
	skillDelay += dt;
	bossFrameDelay += dt;
	snailMoveDelay += dt;
	floaterMoveDelay += dt;
	InnerFearMoveDelay += dt;
	RatMoveDelay += dt;
	canJump += dt;
    deltaTime = dt;

	gravity();
	checkforSpike();
	checkForGoal();
	checkForTreasure();

	if ( hasbeenStabbed == 1 ) 
	{
		colour(0x0F);
		renderSpikes();
		hasbeenStabbed = 0;
		gotoXY(14, 8);
	}

	if ( isBossLevel == 1 )
	{
		
		if ( meteor.size() != 0 ) // If there are meteors
		{
			updateMeteor();
			checkCollisionMeteor();
		}

		if ( splint.size() != 0 ) // If boss used splint
		{
			updateSplint();
			checkCollisionSplint();
		}
	}

	if ( isBossLevel == 2 )
	{
		if ( laser.size() != 0 ) // If there's laser
		{
			updateLaser();
			// check collision
		}

		if ( lava.size() != 0 ) // If there's lava
		{
			updateLava();
			// check collision
		}
	}

	if ( MonsterSnail.size() != 0 ) // When there are snails
	{
		if ( snailMoveDelay > 0.500 ) // Snails move every 500ms
		{
			updateSnails();
			snailMoveDelay = 0; // reset movement timer
		}
		checkCollisionSnail();
	}

	if ( Floater.size() != 0 ) // When there are floaters
	{
		if ( floaterMoveDelay > 0.750 ) // floaters move every 750ms
		{
			updateFloater();
			floaterMoveDelay = 0; // reset movement timer
		}
		checkCollisionFloater();
	}

	if ( Rat.size() != 0 ) // When there are Rats
	{
		if ( RatMoveDelay > 0.250 ) // Rats move every 250ms
		{
			updateRat();
			RatMoveDelay = 0; // reset movement timer
		}
		checkCollisionRat();
	}

	if ( InnerFear.size() != 0 ) // When there are InnerFears
	{
		if ( InnerFearMoveDelay > 0.400 ) // InnerFears move every 400ms
		{
			updateInnerFear();
			InnerFearMoveDelay = 0; // reset movement timer
		}
		checkCollisionInnerFear();
	}


    // Updating the location of the character based on the key press
    if (keyPressed[K_LEFT])
    {
       if (map[charLocation.Y][charLocation.X-1] != '#') // There is no wall on the left.
		{
			Beep(1440, 30);
			gotoXY(charLocation.X, charLocation.Y); // Preventing screen flickering.
			std::cout << " "; // Replace character with a space.
			charLocation.X--; // Move left.
		}
    }

    if (keyPressed[K_RIGHT])
    {
		if (map[charLocation.Y][charLocation.X+1] != '#') // There is no wall on the right.
		{
			Beep(1440, 30);
			gotoXY(charLocation.X, charLocation.Y); // Preventing screen flickering.
			std::cout << " "; // Replace character with a space.
			charLocation.X++;
		}
    }

	if (keyPressed[K_SPACE])
	{
		jump();
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        gamestate = LEVELMENU;

	checkforDeath();
}

void render()
{
    // clear previous screen
	if ( hasLevelRendered == 0 )
	{
		cls();
		colour(0x0F);
		renderLevel();
		renderHP();
		hasLevelRendered = 1;
	}

	if ( hasbeenDamaged == 1 )
		renderHP();
	
	if ( isBossLevel == 1 ) // These renders only occur when it's a boss level
	{
		if ( meteor.size() != 0 ) // If boss spawned meteors
		{
			renderMeteor();
		}

		if ( splint.size() != 0 ) // If boss used splint
		{
			renderSplint();
		}

		checkBossStatus();
	}

	if ( isBossLevel == 2 )
	{
		if ( laser.size() != 0 ) // If laz0r
		{
			renderLaser();
		}

		if ( lava.size() != 0 ) // If there's lavarh
		{
			renderLava();
			// check collision
		}

		checkPianusStatus();
	}

	renderMonster();

	//gotoXY(6, 3);
	//std::cout << "X: " << charLocation.X << " Y: " << charLocation.Y;

    colour(0x0F);

    //render the game

    // render time taken to calculate this frame
    //gotoXY(70, 0);
    //colour(0x1A);
    //std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    //gotoXY(0, 0);
    //colour(0x59);
    //std::cout << elapsedTime << "secs" << std::endl;

    // render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;
	colour(0x0F);

}

