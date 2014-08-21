// File containing stuff related to boss

#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

int bossStatus = 0; // Check what the boss is currently doing. 0 = Standing, 1 = Using skill1, 2 = using skill2. 
double skillDelay = 0; // delay between using skills
double bossFrameDelay = 0; // delay between boss animations

extern COORD charLocation;
extern COORD consoleSize;
extern int gamestate;

std::vector<bossAttack> meteor;
std::vector<bossAttack> splint;
std::vector<bossAttack> laser;
std::vector<bossAttack> lava;

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
	gotoXY(60, 4);	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(60, 8);	std::cout << "    I777777IIIIIIII?,:,,";
	gotoXY(60, 9);	std::cout << "    II777IIIIIIIIIII?++=";
	gotoXY(60, 10);	std::cout << "   IIIIIIIIIIIII7III?+++~";
	gotoXY(60, 11);	std::cout << "   II+.=IIIIIII?..III+?+=";
	gotoXY(60, 12);	std::cout << "    I=.=IIIIIII?..III?++=~              ";
	gotoXY(60, 13);	std::cout << "    ++III~I:IIII7I++I?++=~         ??~~:";
	gotoXY(60, 14);	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       = ,'   ";
	gotoXY(50, 15);	std::cout << "             +II          +I??7?++=~     =        ";
	gotoXY(50, 16);	std::cout << "             ?77              7I++=~    I";
	gotoXY(50, 17);	std::cout << "            I777              7I?=~~   I";
	gotoXY(50, 18);	std::cout << "            +777            77II?===   =";
	gotoXY(50, 19);	std::cout << "            +I            77IIII======";
	gotoXY(50, 20);	std::cout << "             +III7777777IIIIII?=~=";
	gotoXY(50, 21);	std::cout << "          ,~~~.+IIIIIIIIIII??+.~:,,";
}

void bossMeteor1()
{
	gotoXY(60, 4);	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(56, 8);	std::cout << ",I??    I777777IIIIIIII?,:,,";
	gotoXY(55, 9);	std::cout << ":I77+7+.?II777IIIIIIIIIII?++=           ";
	gotoXY(54, 10);	std::cout << ",?7=++I~?IIIIIIIIIIIIIIII7III?+++~      ";
	gotoXY(53, 11);	std::cout << "=.=777=?+?II+.=IIIIIII?..III+?+=               ";
	gotoXY(60, 12);	std::cout << "    I=.=IIIIIII?..III?++=~              ";
	gotoXY(60, 13);	std::cout << "    ++III~I:IIII7I++I?++=~         ??~~:";
	gotoXY(60, 14);	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       = ,'   ";
	gotoXY(60, 15);	std::cout << "   +II          +I??7?++=~     =        ";
	gotoXY(60, 16);	std::cout << "   ?77              7I++=~    I         ";
	gotoXY(60, 17);	std::cout << "  I777              7I?=~~   I          ";
	gotoXY(60, 18);	std::cout << "  +777            77II?===   =          ";
	gotoXY(60, 19);	std::cout << "  +I            77IIII======            ";
	gotoXY(60, 20);	std::cout << "   +III7777777IIIIII?=~=";
	gotoXY(60, 21);	std::cout << ",~~~.+IIIIIIIIIII??+.~:,,";
	
}

void bossMeteor2()
{
	gotoXY(60, 4);	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(56, 8);	std::cout << " ,I??   I777777IIIIIIII?,:,,";
	gotoXY(55, 9);	std::cout << " :I77+7+.II777IIIIIIIIIII?++=";
	gotoXY(54, 10);	std::cout << " ,?7=++I~IIIIIIIIIIIIIIII7III?+++~     ";
	gotoXY(53, 11);	std::cout << "  =.=777=?II+.=IIIIIII?..III+?+=            ?";
	gotoXY(60, 12);	std::cout << "    I=.=IIIIIII?..III?++=~          ?  ";
	gotoXY(60, 13);	std::cout << "    ++III~I:IIII7I++I?++=~         ?    ";
	gotoXY(60, 14);	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =     ";
	gotoXY(60, 15);	std::cout << "   +II          +I??7?++=~     =";
	gotoXY(60, 16);	std::cout << "   ?77              7I++=~    I";
	gotoXY(60, 17);	std::cout << "  I777              7I?=~~   I";
	gotoXY(60, 18);	std::cout << "  +777            77II?===   =";
	gotoXY(60, 19);	std::cout << "  +I            77IIII======";
	gotoXY(60, 20);	std::cout << "   +III7777777IIIIII?=~=";
	gotoXY(60, 21);	std::cout << ",~~~.+IIIIIIIIIII??+.~:,,";
	
}

void bossMeteor3()
{
	gotoXY(60, 4);	std::cout << "    ~,~~             ?=:,";
	gotoXY(60, 5);	std::cout << "    =~,~~,,      ,==?~~~";
	gotoXY(60, 6);	std::cout << "    =~~7IIIIIIIII+~=~~,,~";
	gotoXY(60, 7);	std::cout << "    =.7777IIIIIIII~~~::,~";
	gotoXY(56, 8);	std::cout << "        I777777IIIIIIII?,:,,";
	gotoXY(55, 9);	std::cout << "         II777IIIIIIIIIII?++=";
	gotoXY(54, 10);	std::cout << "       I~IIIIIIIIIIIIIIII7III?+++~     ";
	gotoXY(53, 11);	std::cout << "          II+.=IIIIIII?..III+?+=             ";
	gotoXY(60, 12);	std::cout << "    I=.=IIIIIII?..III?++=~          ???";
	gotoXY(60, 13);	std::cout << "    ++III~I:IIII7I++I?++=~         ?    ";
	gotoXY(60, 14);	std::cout << "   ?IIIIIIIIIIIIIIIII?++=~       =     ";
	gotoXY(60, 15);	std::cout << "   +II          +I??7?++=~     =";
	gotoXY(60, 16);	std::cout << "   ?77              7I++=~    I";
	gotoXY(60, 17);	std::cout << "  I777              7I?=~~   I";
	gotoXY(60, 18);	std::cout << "  +777            77II?===   =";
	gotoXY(60, 19);	std::cout << "  +I            77IIII======";
	gotoXY(60, 20);	std::cout << "   +III7777777IIIIII?=~=";
	gotoXY(60, 21);	std::cout << ",~~~.+IIIIIIIIIII??+.~:,,";
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

