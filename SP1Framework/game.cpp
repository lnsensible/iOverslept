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
int isBossLevel = 0; //Check if it is a boss level. 0 = No, 1 = Yep.
double canJump = 0; // Check if you have jumped in the past 0.8 ms
double jumpDelay = 0; // delay between y coordinate change while jumping
double fallDelay = 0; // delay between falling (no delay for initial fall)
double skillDelay = 0; // delay between using skills
double bossFrameDelay = 0; // delay between boss animations

int PlayerHealth = 3; // Player's HP. Default = 3.

struct Monster
{
	std::vector<int> x;
	std::vector<int> y;
	std::vector<int> health;
};

Monster MonsterSnail;


struct bossAttack {
	std::vector<int> X;
	std::vector<int> Y;
};

bossAttack meteor;
bossAttack splint;

//menu ~ Gabriel Wong

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

	charLocation.X = 50; //default cursor position
	charLocation.Y = 23;
}
void updatelevelmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_LEFT])
	{
		if (charLocation.X != 50 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X -= 2;
		}
	}

	if(keyPressed[K_RIGHT])
	{
		if (charLocation.X != 68 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X += 2;
		}
	}

	if(keyPressed[K_ENTER])
	{
		hasLevelRendered = 0;

		if(charLocation.X == 50)
		{
			checkLevel = 1;
		}

		else if(charLocation.X == 52)
		{
			checkLevel = 2;
		}

		else if(charLocation.X == 54)
		{
			checkLevel = 3;
		}

		else if(charLocation.X == 56)
		{
			checkLevel = 4;
		}

		else if(charLocation.X == 58)
		{
			checkLevel = 5;
		}

		else if(charLocation.X == 60)
		{
			checkLevel = 6;
		}

		else if(charLocation.X == 62)
		{
			checkLevel = 7;
		}

		else if(charLocation.X == 64)
		{
			checkLevel = 8;
		}

		else if(charLocation.X == 66)
		{
			checkLevel = 9;
		}

		else if(charLocation.X == 68)
		{
			checkLevel = 10;
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
	gotoXY(50, 22);
	std::cout << "1";
	gotoXY(52, 22);
	std::cout << "2";
	gotoXY(54, 22);
	std::cout << "3";
	gotoXY(56, 22);
	std::cout << "4";
	gotoXY(58, 22);
	std::cout << "5";
	gotoXY(60, 22);
	std::cout << "6";
	gotoXY(62, 22);
	std::cout << "7";
	gotoXY(64, 22);
	std::cout << "8";
	gotoXY(66, 22);
	std::cout << "9";
	gotoXY(68, 22);
	std::cout << "10";

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
			g_quitGame = true;
		}

		if(charLocation.X == 50)
		{
			gamestate = LEVELMENU;
		}
	}
}
void renderdeathmenu()
{
	cls();
	colour(0x0F);

	gotoXY(52, 20);
	std::cout << "YOU DIED :C TRY AGAIN?";
	gotoXY(52, 22);
	std::cout << "Yes :D";
	gotoXY(62, 22);
	std::cout << "SCREW IT I'M OUTTA HERE";

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
				MonsterSnail.x.push_back(j); // location of X-coordinates of snail
				MonsterSnail.y.push_back(i); // location of Y-coordinates of snail
				MonsterSnail.health.push_back(2); // health of snail
			}

			if ( map[i][j] == 'T' ) // TREASURE HORRYY SHEET $$$
			{
				map[i][j] = 15;
			}

			if ( map[i][j] == 'G' ) // GOAL
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
			else
			{
				std::cout << map[i][j]; // else print what's in the array
			}
		}
	}
	for (int i = 0; i < (MonsterSnail.x).size(); i++)
	{
		gotoXY( MonsterSnail.x[i], MonsterSnail.y[i] ); // spawns at XY coordinates 
		std::cout << "@/'"; // spawn snail appearance 
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
	for ( int i = 0; i < PlayerHealth; i++ )
	{
		std::cout << (char)3 << " ";
	}
}

void bossStand1()
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
	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =         ";
	gotoXY(50, 15);
	std::cout << "             +II          +I??7?++=~     =           ";
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
	(meteor.X).push_back(13);
	(meteor.Y).push_back(0);

	(meteor.X).push_back(29);
	(meteor.Y).push_back(0);
}

void updateMeteor() // moves meteors / delete meteors and adjust coordinates
{
	gotoXY(20, 3);
	std::cout << "        "; // clean up mess after spawning
	gotoXY(36, 3);
	std::cout << "         ";
	for (unsigned int i = 0; i < (meteor.X).size(); i++ ) // for all the meteors
	{
		if ( (meteor.Y)[i] < 19 ) // when meteor is still falling ~
		{
			for ( int j = (meteor.Y)[i]-2; j < (meteor.Y)[i]+3; j++) //clean up the path behind the meteor 
			{
				for ( int k = (meteor.X)[i]-5; k < (meteor.X)[i]+6; k++) //  WHAT THE METEOR DESTROYEDDD.
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
		( (meteor.Y)[i] )++;
		}
		else // when meteor hits the ground
		{
			for ( int j = (meteor.Y)[i]-2; j < (meteor.Y)[i]+3; j++) //clean up the ground
			{
				for ( int k = (meteor.X)[i]-5; k < (meteor.X)[i]+6; k++) // CLEAN UP THE GROUNDD >:((
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

			(meteor.X).erase( (meteor.X).begin() + i ); //erase coords
			(meteor.Y).erase( (meteor.Y).begin() + i ); //erase coords
		}
	}
}

void renderMeteor() // cout meteors to console
{
	for (unsigned int i = 0; i < (meteor.X).size(); i++ )
	{
		gotoXY( (meteor.X)[i]-5, (meteor.Y)[i] );
		std::cout << "x@*(&@(*&%x";
		gotoXY( (meteor.X)[i]-5, (meteor.Y)[i]+1 );
		std::cout << "'x?HQ(*@&x'";
		gotoXY( (meteor.X)[i]-5, (meteor.Y)[i]-1 );
		std::cout << ",xQ)(&@FJx,";
		gotoXY( (meteor.X)[i]-5, (meteor.Y)[i]+2 );
		std::cout << " 'xxxxxxx' ";
		gotoXY( (meteor.X)[i]-5, (meteor.Y)[i]-2 );
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
	(splint.X).push_back(22);
	(splint.Y).push_back(22);
}

void updateSplint()
{
	for (unsigned int i = 0; i < (splint.Y).size(); i++ ) // when spike still moving upwards
	{
		if ( (splint.Y)[i] > 3 )
		{
			(splint.Y)[i]--;
		}
		else // when spike reaches the top
		{
			for ( int j = (splint.X)[i]-3; j < (splint.X)[i]+2; j++) // remove the spikes
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

			(splint.X).erase( (splint.X).begin() + i ); //erase coords
			(splint.Y).erase( (splint.Y).begin() + i ); //erase coords
		}
	}
}

void renderSplint()
{
	for (unsigned int i = 0; i < (splint.X).size(); i++ )
	{
		gotoXY( (splint.X)[i]-3, (splint.Y)[i] );
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
	if (map[charLocation.Y][charLocation.X] == 234)
	{
		gamestate = ENDGAME;
	}
}

void checkCollisionSplint()
{
	if ( (splint.X).size() != 0 ) // confirming there is a splint
	{
		if ( charLocation.X >= (splint.X)[0]-3 && charLocation.X <= (splint.X)[0]+1 ) // if player standing within x coordinates of splint attack
		{
			if ( charLocation.Y >= (splint.Y)[0] ) // if player is within the splint
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
	if ( (meteor.X).size() != 0 )
	{
		for ( int i = 0; i < (meteor.X).size(); i++ )
		{
			if ( charLocation.X >= (meteor.X)[i]-5 && charLocation.X <= (meteor.X)[i]+5 ) // if player standing within x coordinates of splint attack
			{
				if ( charLocation.Y >= (meteor.Y)[i]-2 && charLocation.Y >= (meteor.Y)[i]+2 ) // if player is within the splint
				{
					hasbeenDamaged = 1;
					if ( PlayerHealth > 0 )
						PlayerHealth--;
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
					if ( map[i][j+1] != '#' && map[i+1][j+1] == '#' )
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

void renderSnails() // re-render snails after being hit
{
	for (int i = 0; i < 24; i++)
	{
		for (int j = 0; j < 120; j++)
		{
			if ( map[i][j] == 'S' )
			{
				gotoXY(j, i);
				std::cout << "@/'";
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

	PlayerHealth = 3;//-------------------------

	hasbeenStabbed = 0;
	hasbeenDamaged = 0;
	bossStatus = 0;
	isBossLevel = 0;

	//loads level from file
	if ( checkLevel == 1 )
	{
		loadLevel("level1.txt");
		SetConsoleTitle(L"Level One");
	}
	else if ( checkLevel == 2 )
	{
		loadLevel("level2.txt");
		SetConsoleTitle(L"Level Two");
	}
	else if ( checkLevel == 3 )
	{
		loadLevel("level3.txt");
		SetConsoleTitle(L"Level Three");
	}
	else if ( checkLevel == 4 )
	{
		loadLevel("level4.txt");
		SetConsoleTitle(L"Level Four");
	}
	else if ( checkLevel == 5 )
	{
		loadLevel("level5.txt");
		SetConsoleTitle(L"Level Five");
	}
	else if ( checkLevel == 6 )
	{
		loadLevel("level6.txt");
		SetConsoleTitle(L"Level Six");
	}
	else if ( checkLevel == 7 )
	{
		loadLevel("level7.txt");
		SetConsoleTitle(L"Level Seven");
	}
	else if ( checkLevel == 8 )
	{
		SetConsoleTitle(L"Level Eight");
		loadLevel("level8.txt");
	}
	else if ( checkLevel == 9 )
	{
		loadLevel("level9.txt");
		SetConsoleTitle(L"Level Nine");
	}
	else if ( checkLevel == 10 )
	{
		isBossLevel = 1;
		SetConsoleTitle(L"Level Ten");
		loadLevel("level10.txt");
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
	canJump += dt;
    deltaTime = dt;

	gravity();
	checkforSpike();
	checkForGoal();

	if ( hasbeenStabbed == 1 ) 
	{
		colour(0x0F);
		renderSpikes();
		hasbeenStabbed = 0;
		gotoXY(14, 8);
	}

	if ( isBossLevel == 1 )
	{
		
		if ( (meteor.X).size() != 0 ) // If there are meteors
		{
			updateMeteor();
			checkCollisionMeteor();
		}

		if ( (splint.X).size() != 0 ) // If boss used splint
		{
			updateSplint();
			checkCollisionSplint();
		}
	}

	updateSnails();

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
		if ( (meteor.X).size() != 0 ) // If boss spawned meteors
		{
			renderMeteor();
		}

		if ( (splint.X).size() != 0 ) // If boss used splint
		{
			renderSplint();
		}

		checkBossStatus();
	}

	renderSnails();

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

