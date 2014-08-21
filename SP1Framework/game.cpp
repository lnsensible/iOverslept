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

extern std::vector<bossAttack> meteor;
extern std::vector<bossAttack> splint;
extern std::vector<bossAttack> laser;
extern std::vector<bossAttack> lava;

extern std::vector<Monster> MonsterSnail;
extern std::vector<Monster> Floater;
extern std::vector<Monster> InnerFear;
extern std::vector<Monster> Rat;

extern int hasbeenStabbed;
extern int weaponDAMAGE;       
extern int weaponSPEED;         
extern int weaponHITCOUNT;   
extern std::string beforeATTACK,afterATTACK;
extern std::string weaponHITBOX; 
extern std::string weaponSTATE;  

extern double jumpDelay;
extern double fallDelay;
extern double canJump;

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
int gamestate = 0;
COORD charLocation;
COORD consoleSize;

unsigned char map[25][120]; // stores the level map
int checkLevel = 0; // Check current level
int hasLevelRendered = 0; // Check if level has been rendered. 0 = Not loaded, 1 = Loaded

int treasure = 0;//Treasure :DD
int isBossLevel = 0; //Check if it is a boss level. 0 = No, 1 = Boss, 2= Fishy

double snailMoveDelay = 0; // delay between each snail movement :D
double floaterMoveDelay = 0; // delay between each floater movement
double InnerFearMoveDelay = 0; // delay between each InnerFear movement
double RatMoveDelay = 0; // delay between each Rat movement

int PlayerHealth = 3; // Player's HP. Default = 3.

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

void prepareLevel() // Prepares level map for cout.
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
	keyPressed[K_Q] = isKeyPressed(0x51);
    keyPressed[K_E] = isKeyPressed(0x45);
    keyPressed[K_C] = isKeyPressed(0x43);
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
			WEAPON.X = charLocation.X - 2;
			rightORleft = false;
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
			WEAPON.X = charLocation.X + 2;
			rightORleft = true;
		}
    }

	if (keyPressed[K_SPACE])
	{
		jump();
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
        gamestate = LEVELMENU;

	WEAPON.Y = charLocation.Y;
        if (keyPressed[K_Q])
        {
                rangeORmelee = true;
        }
 
        if (keyPressed[K_E])
        {
                rangeORmelee = false;
        }
 
        WEAPON_PROPERTIES();
 
        if (keyPressed[K_C])
        {
                Atk();
        }
 
        //for when the player faces the left direction
        if (rightORleft == false && rangeORmelee == true && weaponSTATE == afterATTACK)
        {WEAPON.X = charLocation.X - 4;}
 
        if (rightORleft == false && rangeORmelee == false)
        {WEAPON.X = charLocation.X - 5;
        if (weaponSTATE == afterATTACK)
        {WEAPON.X = charLocation.X - 6;}}

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

	 //render Equipped Weapons
     gotoXY(WEAPON);
     if (rangeORmelee == true)
     {
		 std::cout<< weaponSTATE;
	 }
     else if (rangeORmelee == false)
     {
		 std::cout<< weaponSTATE;
	 }
}

