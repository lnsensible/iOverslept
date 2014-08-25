// File containing stuff related to boss

#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

int bossStatus = 0; // Check what the boss is currently doing. 0 = Standing, 1 = Using skill1, 2 = using skill2. 
int Randomzxc = 0; // determine where hitbox will spawn
int RemovePianusHitbox = 0; // 0 = no need to remove, 1 = remove
double skillDelay = 0; // delay between using skills
double bossFrameDelay = 0; // delay between boss animations
double hitboxDelay = 0; // delay between hitbox movement

const int bossHP = 20; // max hp= 20
const int pianusHP = 20; // max hp= 20
int bosscurrentHP = 0;
int pianuscurrentHP = 0;

char bossHPbar[20];
char pianusHPbar[20];

extern int isBossLevel;

extern COORD charLocation;
extern COORD consoleSize;
extern int gamestate;
extern std::vector<Skill_Properties> FireOrb;

std::vector<bossAttack> meteor;
std::vector<bossAttack> splint;
std::vector<bossAttack> laser;
std::vector<bossAttack> lava;
std::vector<bossAttack> BossHitbox;
std::vector<Monster> PianusHitbox;

int PewPew = 0; // 0 = no shoot laser, 1 = pewpew, 2 = delete laser
int SpewSpew = 0; // 0 = no lava flood, 1 = spewspew, 2 = delete lava
int BoomBoom = 0; // 0 = no meteor, 1 = booom, 2 = delete meteor
int BlingBling = 0; // 0 = no splint, 1 = poke, 2 = delete splint

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
			PewPew = 1;
			laser[i].X-- ;
		}
		else // when laser reaches the left
		{	
			PewPew = 2;
		}
	}
}

void renderLaser()
{
	if ( PewPew == 1 )
	{
		for (unsigned int i = 0; i < laser.size(); i++ ) // when laser still moving lefts
		{
			for ( int j = laser[i].Y -6; j < laser[i].Y +2; j++)
			{
				gotoXY( laser[i].X+1, j );
				if ( map[j][laser[i].X+1] == '#')
				{
					std::cout << (char)219; // and print block to replace walls
				}
				else
				{
					std::cout << map[j][laser[i].X+1]; // else print what's in the array
				}
			}
		}

		for ( int j = laser[0].Y -6; j < laser[0].Y +2; j++)
		{
			gotoXY( laser[0].X, j );
			std::cout << (char)27;
		}
		PewPew = 0;
	}

	if ( PewPew == 2 )
	{
		for (unsigned int i = 0; i < laser.size(); i++ ) // when laser still moving lefts
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
		}
		laser.clear(); // removes laser
		PewPew = 0;
	}

}

void pianusLava1()
{
	gotoXY(65, 7);	std::cout << "                                        ";
	gotoXY(65, 8);	std::cout << "                      ~+?III====___     ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?II::==,     ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??II::,    ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?II:,    ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::::::    ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::::    ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,    ";
	gotoXY(65, 15);	std::cout << "    :I??++===~~~~::::::::=~=+++,:,,,,   ";
	gotoXY(65, 16);	std::cout << "    :=++++====~~?+=~::::,:::~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << "  ??IIII?~~==~~~:,~~~::::,,,:~=,,,,,,   ";
	gotoXY(65, 18);	std::cout << "  ====~~:+==~~~====~:::,:::~~==,,,,,,,  ";
	gotoXY(65, 19);	std::cout << "   ====~~:+==~~~====~:::,:::~~==,,,,,,, ";
	gotoXY(65, 20);	std::cout << "   =,:~~~~?:~~~~~~~~~~~,,~=:,,,,,,,,,,, ";
	gotoXY(65, 21);	std::cout << "  ========~~~~~~~~~~:~,,===+++?,,,,,,,, ";
}

void pianusLava2()
{
	gotoXY(65, 7);	std::cout << "                                        ";
	gotoXY(65, 8);	std::cout << "                      ~+?III====___     ";
	gotoXY(65, 9);	std::cout << "                 ,,=:~+=~++?III::==,    ";
	gotoXY(65, 10);	std::cout << "           7777I??+=~~~~==~=+??III::    ";
	gotoXY(65, 11);	std::cout << "        IIIIII??+~~::::::::~~=+?::::,   ";
	gotoXY(65, 12);	std::cout << "       7III?===~~:::::::::::::::::::,   ";
	gotoXY(65, 13);	std::cout << "       =+++==+=~~:::::::::::=,,,::,,,   ";
	gotoXY(65, 14);	std::cout << "      ++++++===~~:::::::::?+++,,,,,,,   ";
	gotoXY(65, 15);	std::cout << "    :I??++===~~~~::::::::=~=+++,:,,,,   ";
	gotoXY(65, 16);	std::cout << "    :=++++====~~?+=~::::,:::~==,,,,,,   ";
	gotoXY(65, 17);	std::cout << "  ??IIII?~~==~~~:,~~~::::,,,:~=,,,,,,   ";
	gotoXY(65, 18);	std::cout << "  ====~~:+==~~~====~:::,:::~~==,,,,,,,  ";
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

void pianusDead1()
{
	gotoXY(65, 7);	std::cout << "                                        ";
	gotoXY(65, 8);	std::cout << "                                        ";
	gotoXY(65, 9);	std::cout << "           ??=?+??++~                   ";
	gotoXY(65, 10);	std::cout << "         ????=+??+++++~                 ";
	gotoXY(65, 11);	std::cout << "       ?I+?????++==~~~~~~=              ";
	gotoXY(65, 12);	std::cout << "      ~I?+???++=~~:::::::~~=            ";
	gotoXY(65, 13);	std::cout << "     ????I??+=~~~::::::::~~~~           ";
	gotoXY(65, 14);	std::cout << "     ??II??+=~:::::::::::~~..+          ";
	gotoXY(65, 15);	std::cout << "    ???I??==~::~+~~~::~:,...+           ";
	gotoXY(65, 16);	std::cout << "   ?????++=~:~=::  ~::~....+:    ,      ";
	gotoXY(65, 17);	std::cout << "+++++++=::~:::,     =~~:..+:~   ~~    ~ ";
	gotoXY(65, 18);	std::cout << ".,:,....,:::::=     =~:~.,:~~~ +~~   +  ";
	gotoXY(65, 19);	std::cout << "??????=~ ,:::::~:~~~~::..,:,,,,,=~~.+=  ";
	gotoXY(65, 20);	std::cout << "  ,,,,,::= ::::::~::~~,.:~+:...:,, :~,~ ";
	gotoXY(65, 21);	std::cout << "    +++=~::,.~~~~~~~~,:..:+,...=,...:   ";
}

void pianusDead2()
{
	gotoXY(65, 7);	std::cout << "                                        ";
	gotoXY(65, 8);	std::cout << "                                        ";
	gotoXY(65, 9);	std::cout << "                                        ";
	gotoXY(65, 10);	std::cout << "                                        ";
	gotoXY(65, 11);	std::cout << "                                        ";
	gotoXY(65, 12);	std::cout << "         ????=+??+++++~                 ";
	gotoXY(65, 13);	std::cout << "       ?I+?????++==~~~~~~=              ";
	gotoXY(65, 14);	std::cout << "     ????I??+=~~~::::::::~~~~           ";
	gotoXY(65, 15);	std::cout << "     ??II??+=~:::::::::::~~..+          ";
	gotoXY(65, 16);	std::cout << "    ???I??==~::~+~~~::~:,...+           ";
	gotoXY(65, 17);	std::cout << "   ?????++=~:~=::  ~::~....+:    ,      ";
	gotoXY(65, 18);	std::cout << "+++++++=::~:::,     =~~:..+:~   ~~    ~ ";
	gotoXY(65, 19);	std::cout << ".,:,....,:::::=     =~:~.,:~~~ +~~   +  ";
	gotoXY(65, 20);	std::cout << "??????=~ ,:::::~:~~~~::..,:,,,,,=~~ +=  ";
	gotoXY(65, 21);	std::cout << "    +++=~::,.~~~~~~~~,:..:+,...=,...:   ";
}

void pianusDead3()
{
	gotoXY(65, 7);	std::cout << "                                        ";
	gotoXY(65, 8);	std::cout << "                                        ";
	gotoXY(65, 9);	std::cout << "                                        ";
	gotoXY(65, 10);	std::cout << "                                        ";
	gotoXY(65, 11);	std::cout << "                                        ";
	gotoXY(65, 12);	std::cout << "                                        ";
	gotoXY(65, 13);	std::cout << "                                        ";
	gotoXY(65, 14);	std::cout << "                                        ";
	gotoXY(65, 15);	std::cout << "         ????=+??+++++~                 ";
	gotoXY(65, 16);	std::cout << "       ?I+?????++==~~~~~~=              ";
	gotoXY(65, 17);	std::cout << "     ????I??+=~~~::::::::~~~            ";
	gotoXY(65, 18);	std::cout << "    ???I??==~::~+~~~::~:,...+           ";
	gotoXY(65, 19);	std::cout << "   ?????++=~:~=::  ~::~....+:    ,      ";
	gotoXY(65, 20);	std::cout << " ,:,....,:::::=     =~:~.,:~~~ +~~   +  ";
	gotoXY(65, 21);	std::cout << "??????=~.,:::::~:~~~~::..,:,,,,,=~~ +=  ";
}

void updateLava()
{
	if ( lava[0].Y > 17 )
	{
		for ( int i = 0; i < 41; i++)
		{
			SpewSpew = 1;
			lava[i].Y--;
		}
	}
	else // when lava reaches top platform
	{
		SpewSpew = 2;
	}
}

void renderLava()
{
	if ( SpewSpew == 1 )
	{
		for (unsigned int i = 0; i < lava.size(); i++ )
		{
			for (unsigned int j = 0; j < lava.size(); j++)
			{
				gotoXY( lava[j].X, lava[i].Y );
				std::cout << (char)30;
			}
		}
		SpewSpew = 0;
	}

	if ( SpewSpew == 2 )
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

void updateMeteor() // moves meteors and adjust coordinates
{
	
	for (unsigned int i = 0; i < meteor.size(); i++ ) // for all the meteors
	{
		if ( meteor[i].Y < 19 ) // when meteor is still falling ~
		{
			BoomBoom = 1;
			meteor[i].Y++;
		}
		else // when meteor hits the ground
		{
			BoomBoom = 2;
		}
	}
}

void renderMeteor() // cout meteors to console
{
	gotoXY(20, 3);
	std::cout << "        "; // clean up mess after spawning
	gotoXY(36, 3);
	std::cout << "         ";
	if ( BoomBoom == 1 )
	{
		for (unsigned int i = 0; i < meteor.size(); i++ ) // for all the meteors
		{
			for ( int j = meteor[i].Y -3; j < meteor[i].Y; j++) //clean up the path behind the meteor 
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
		}

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

		BoomBoom = 0;
	}

	if ( BoomBoom == 2 )
	{
		for (unsigned int i = 0; i < meteor.size(); i++ ) // for all the meteors
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
		meteor.clear(); // clear meteors when reached ground
		BoomBoom = 0;
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

void bossDead1()
{
	gotoXY(50, 4);	std::cout << "                                                     ";
	gotoXY(50, 5);	std::cout << "                                                     ";
	gotoXY(50, 6);	std::cout << "              =~,~~,,      ,==?~~~~                  ";
	gotoXY(50, 7);	std::cout << "              =~~7IIIIIIIII+~=~~,,~                  ";
	gotoXY(50, 8);	std::cout << "              =.7777IIIIIIII~~~::,~                  ";
	gotoXY(50, 9);	std::cout << "              I777777IIIIIIII?,:,,                   ";
	gotoXY(50, 10);	std::cout << "              II777IIIIIIIIIII?++=                   ";
	gotoXY(50, 11);	std::cout << "             IIIIIIIIIIIII7III?+++~                  ";
	gotoXY(50, 12);	std::cout << "             II+  IIIIIII?  III+?+=                  ";
	gotoXY(50, 13);	std::cout << "              I=  IIIIIII?  III?++=~                 ";
	gotoXY(50, 14);	std::cout << "              ++III~I:IIII7I++I?++=~                 ";
	gotoXY(50, 15);	std::cout << "             ?IIIIIIIIIIIIIIIII?++=~       717I      ";
	gotoXY(50, 16);	std::cout << "             +II          +I??7?++=~     =~~~~~      ";
	gotoXY(50, 17);	std::cout << "             ?77              7I++=~    I            ";
	gotoXY(50, 18);	std::cout << "            I777              7I?=~~   I             ";
	gotoXY(50, 19);	std::cout << "            +777            77II?===   =             ";
	gotoXY(50, 20);	std::cout << "            +I            77IIII======               ";
	gotoXY(50, 21);	std::cout << "           +IIIIII7777777IIIIIIII======              ";
}

void bossDead2()
{
	gotoXY(50, 4);	std::cout << "                                                     ";
	gotoXY(50, 5);	std::cout << "                                                     ";
	gotoXY(50, 6);	std::cout << "                                                     ";
	gotoXY(50, 7);	std::cout << "                                                     ";
	gotoXY(50, 8);	std::cout << "                                                     ";
	gotoXY(50, 9);	std::cout << "                                                     ";
	gotoXY(50, 10);	std::cout << "              =~~7IIIIIIIII+~=~~,,~                  ";
	gotoXY(50, 11);	std::cout << "              I777777IIIIIIII?,:,,                   ";
	gotoXY(50, 12);	std::cout << "              II777IIIIIIIIIII?++=                   ";
	gotoXY(50, 13);	std::cout << "             II+  IIIIIII?  III+?+=                  ";
	gotoXY(50, 14);	std::cout << "              I=  IIIIIII?  III?++=~                 ";
	gotoXY(50, 15);	std::cout << "              ++III~I:IIII7I++I?++=~                 ";
	gotoXY(50, 16);	std::cout << "             ?IIIIIIIIIIIIIIIII?++=~                 ";
	gotoXY(50, 17);	std::cout << "             +II          +I??7?++=~                 ";
	gotoXY(50, 18);	std::cout << "             ?77              7I++=~     ...,        ";
	gotoXY(50, 19);	std::cout << "            I777              7I?=~~    =~~~~        ";
	gotoXY(50, 20);	std::cout << "            +777            77II?===   =             ";
	gotoXY(50, 21);	std::cout << "           +IIIIII7777777IIIIIIIIIII===              ";
}

void bossDead3()
{
	gotoXY(50, 4);	std::cout << "                                                     ";
	gotoXY(50, 5);	std::cout << "                                                     ";
	gotoXY(50, 6);	std::cout << "                                                     ";
	gotoXY(50, 7);	std::cout << "                                                     ";
	gotoXY(50, 8);	std::cout << "                                                     ";
	gotoXY(50, 9);	std::cout << "                                                     ";
	gotoXY(50, 10);	std::cout << "                                                     ";
	gotoXY(50, 11);	std::cout << "                                                     ";
	gotoXY(50, 12);	std::cout << "                                                     ";
	gotoXY(50, 13);	std::cout << "              =~~7IIIIIIIII+~=~~,,~                  ";
	gotoXY(50, 14);	std::cout << "              I777777IIIIIIII?,:,,                   ";
	gotoXY(50, 15);	std::cout << "             II+  IIIIIII?  III+?+=                  ";
	gotoXY(50, 16);	std::cout << "              I=  IIIIIII?  III?++=~                 ";
	gotoXY(50, 17);	std::cout << "              ++III~I:IIII7I++I?++=~                 ";
	gotoXY(50, 18);	std::cout << "             ?IIIIIIIIIIIIIIIII?++=~                 ";
	gotoXY(50, 19);	std::cout << "             +II          +I??7?++=~                 ";
	gotoXY(50, 20);	std::cout << "            +777            77II?===                 ";
	gotoXY(50, 21);	std::cout << "           +IIIIII7777777IIIIIIIIIII=======~~~-      ";
}

void updateSplint()
{
	for (unsigned int i = 0; i < splint.size(); i++ ) // when spike still moving upwards
	{
		if ( splint[i].Y > 3 )
		{
			BlingBling = 1;
			splint[i].Y--;
		}
		else // when spike reaches the top
		{
			BlingBling = 2;
		}
	}
}

void renderSplint()
{
	if ( BlingBling == 1 )
	{
		for (unsigned int i = 0; i < splint.size(); i++ )
		{
			gotoXY( splint[i].X -3, splint[i].Y );
			std::cout << (char)24 << (char)24 << (char)24 << (char)24 << (char)24;
		}
		BlingBling = 0;
	}

	if ( BlingBling == 2 )
	{
		for (unsigned int i = 0; i < splint.size(); i++ )
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
		}
		splint.clear();
		BlingBling = 0;
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

void checkCollisionLaser()
{
	if ( laser.size() != 0 ) // confirming there is a splint
	{
		if ( charLocation.Y >= laser[0].Y -6 && charLocation.Y <= laser[0].Y +1 ) // if player standing within y coordinates of laser attack
		{
			if ( charLocation.X == laser[0].X ) // if player is within the splint
			{
				hasbeenDamaged = 1;
				if ( PlayerHealth > 0 )
					PlayerHealth--;
			}
		}
	}
}

void checkCollisionLava()
{
	if ( lava.size() != 0 ) // confirming there is lava
	{
		for (unsigned int i = 0; i < lava.size(); i++)
		{
			if ( charLocation.X == lava[i].X ) // if player standing within y coordinates of lava
			{
				if ( charLocation.Y >= lava[i].Y ) // if player is within lava
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
	if ( bosscurrentHP == 0 )
	{
		if ( bossFrameDelay > 1.0 ) // first frame
			{
				if ( bossFrameDelay > 2.0 && bossFrameDelay <= 3.0) // second frame
				{
					bossDead2();
				}
				else if ( bossFrameDelay > 3.0 ) // third frame
				{
					bossDead3();
					map[21][41] = (char)239;
					map[19][21] = (char)209;
					renderLevel();
					bossFrameDelay -= 3.0;
					isBossLevel = 0;
					bossStatus = 0;
					skillDelay = 0;
					// reset to standing animation ~
				}
				else
				{
					bossDead1();
				}
			}
	}
	else
	{
		if ( skillDelay > 5.0 )
		{
			bossStatus = ( rand() % 2 + 1 ); // Changes boss status to either 1 or 2 ( use either skill1 or skill2 ).
			skillDelay -= 5.0; // reset skillDelay;
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
					bossFrameDelay -= 2.0;
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
					bossFrameDelay -= 3.0;
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
					bossFrameDelay -= 3.0;
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
}

void checkPianusStatus()
{
	if ( pianuscurrentHP == 0 )
	{
		if ( bossFrameDelay > 1.0 ) // first frame
			{
				if ( bossFrameDelay > 2.0 && bossFrameDelay <= 3.0) // second frame
				{
					pianusDead2();
				}
				else if ( bossFrameDelay > 3.0 ) // third frame
				{
					pianusDead3();
					map[15][8] = (char)239;
					map[15][21] = (char)209;
					renderLevel();
					bossFrameDelay -= 3.0;
					isBossLevel = 0;
					bossStatus = 0;
					skillDelay = 0;
					// reset to standing animation ~
				}
				else
				{
					pianusDead1();
				}
			}
	}
	else
	{
		if ( skillDelay > 5.0 )
		{
			bossStatus = ( rand() % 2 + 1 ); // Changes boss status to either 1 or 2 ( use either skill1 or skill2 ).
			skillDelay -= 5.0; // reset skillDelay;
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
					bossFrameDelay -= 2.0;
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
					bossFrameDelay -= 3.0;
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
					bossFrameDelay -= 3.0;
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
}

void updateBossHitbox()
{
	if ( hitboxDelay > 5.0 )
	{
		hitboxDelay -= 5.0; // reset

		bossAttack spawnHitbox;

		Randomzxc = ( rand() % 9 ); // randomly spawn the hitbox on a platform

		if ( Randomzxc == 0 )
		{
			spawnHitbox.X = 14;
			spawnHitbox.Y = 5;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 1 )
		{
			spawnHitbox.X = 14;
			spawnHitbox.Y = 5;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 2 )
		{
			spawnHitbox.X = 28;
			spawnHitbox.Y = 5;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 3 )
		{
			spawnHitbox.X = 21;
			spawnHitbox.Y = 7;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 4 )
		{
			spawnHitbox.X = 14;
			spawnHitbox.Y = 9;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 5 )
		{
			spawnHitbox.X = 28;
			spawnHitbox.Y = 9;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 6 )
		{
			spawnHitbox.X = 21;
			spawnHitbox.Y = 11;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 7 )
		{
			spawnHitbox.X = 14;
			spawnHitbox.Y = 13;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 8 )
		{
			spawnHitbox.X = 28;
			spawnHitbox.Y = 13;

			BossHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 9 )
		{
			spawnHitbox.X = 21;
			spawnHitbox.Y = 15;

			BossHitbox.push_back(spawnHitbox);
		}
	}
}

void updatePianusHitbox()
{
	if ( hitboxDelay > 10.0 )
	{
		hitboxDelay -= 10.0; // reset

		Monster spawnHitbox;

		Randomzxc = ( rand() % 6 ); // randomly spawn the hitbox on a platform
		gotoXY(0, 0);
		std::cout << Randomzxc;
		if ( Randomzxc == 0 )
		{
			spawnHitbox.x = 21;
			spawnHitbox.y = 15;
			spawnHitbox.health = 3;

			PianusHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 1 )
		{
			spawnHitbox.x = 35;
			spawnHitbox.y = 15;
			spawnHitbox.health = 3;

			PianusHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 2 )
		{
			spawnHitbox.x = 15;
			spawnHitbox.y = 17;
			spawnHitbox.health = 3;

			PianusHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 3 )
		{
			spawnHitbox.x = 28;
			spawnHitbox.y = 17;
			spawnHitbox.health = 3;

			PianusHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 4 )
		{
			spawnHitbox.x = 14;
			spawnHitbox.y = 19;
			spawnHitbox.health = 3;

			PianusHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 5 )
		{
			spawnHitbox.x = 21;
			spawnHitbox.y = 19;
			spawnHitbox.health = 3;

			PianusHitbox.push_back(spawnHitbox);
		}
		else if ( Randomzxc == 6 )
		{
			spawnHitbox.x = 35;
			spawnHitbox.y = 19;
			spawnHitbox.health = 3;

			PianusHitbox.push_back(spawnHitbox);
		}
	}
	else if ( PianusHitbox.size() != 0 )
	{
		if ( rand() % 2 == 0 )
		{
			if ( map[PianusHitbox[0].y][PianusHitbox[0].x-1] != '#' && map[PianusHitbox[0].y+1][PianusHitbox[0].x-1] == '#' ) // If move left is possible
				PianusHitbox[0].x--;
		}
		else
		{
			if ( map[PianusHitbox[0].y][PianusHitbox[0].x+4] != '#' && map[PianusHitbox[0].y+1][PianusHitbox[0].x+4] == '#' ) // If move right is possible
				PianusHitbox[0].x++;
		}
	}
}

void renderBossHitbox()
{
	if ( bosscurrentHP != 0 )
	{
		if ( BossHitbox.size() == 1 )
		{
			gotoXY(BossHitbox[0].X, BossHitbox[0].Y );
			std::cout << (char)3;
		}
		if ( BossHitbox.size() > 1 )
		{
			gotoXY(BossHitbox[0].X, BossHitbox[0].Y );
			std::cout << " ";
			BossHitbox.erase(BossHitbox.begin()); // remove first hitbox
			gotoXY(BossHitbox[0].X, BossHitbox[0].Y );
			std::cout << (char)3;
		}
	}
}

void renderPianusHitbox()
{                 
	if ( PianusHitbox.size() != 0 )
	{
		if ( PianusHitbox.size() == 1 )
		{
			for ( int i = PianusHitbox[0].x-1; i < PianusHitbox[0].x+4; i++) //loop and renders map ( prevent flickering)
			{
				gotoXY(i, PianusHitbox[0].y); // go to coordinate selected
				if ( map[PianusHitbox[0].y][i] == '#' ) // and reprint
				{
					std::cout << (char)219; // the wall
				}
				else
				{
					 std::cout << map[PianusHitbox[0].y][i]; // print whatever is on the map
				}
			}

			gotoXY(PianusHitbox[0].x, PianusHitbox[0].y); // go to coordinates of hitbox in the vector 
			std::cout << "<><"; // print hitbox ( fish)
		}

		if ( PianusHitbox.size() > 1 )
		{
			for ( int i = PianusHitbox[0].x-1; i < PianusHitbox[0].x+4; i++) //loop and renders map ( prevent flickering)
			{
				gotoXY(i, PianusHitbox[0].y); // go to coordinate selected
				if ( map[PianusHitbox[0].y][i] == '#' ) // and reprint
				{
					std::cout << (char)219; // the wall
				}
				else
				{
					 std::cout << map[PianusHitbox[0].y][i]; // print whatever is on the map
				}
			}
			PianusHitbox.erase(PianusHitbox.begin()); // remove first hitbox
			gotoXY(PianusHitbox[0].x, PianusHitbox[0].y); // go to coordinates of hitbox in the vector 
			std::cout << "<><"; // print hitbox ( fish)
		}
	}
}

void removePianusHitbox()
{
	gotoXY(PianusHitbox[0].x-1, PianusHitbox[0].y);
	std::cout << "     ";
	PianusHitbox.erase(PianusHitbox.begin()); // remove both
	RemovePianusHitbox = 0;
}

void bossRenderHP()
{
	gotoXY(55, 3);
	if ( bosscurrentHP != 0 )
	{
		std::cout << "Boss HP: ";
		for ( int i = 0; i < bosscurrentHP; i++ )
		{
			std::cout << (char)178;
		}
		for ( int i = 0; i < bossHP - bosscurrentHP; i++)
		{
			std::cout << (char)176;
		}
	}
	else
	{
		std::cout << "                                  ";
	}
}

void pianusRenderHP()
{
	gotoXY(55, 3);
	if ( pianuscurrentHP != 0 )
	{
		std::cout << "Boss HP: ";
		for ( int i = 0; i < pianuscurrentHP; i++ )
		{
			std::cout << (char)178;
		}
		for ( int i = 0; i < pianusHP - pianuscurrentHP; i++)
		{
			std::cout << (char)176;
		}
	}
	else
	{
		std::cout << "                                  ";
	}
}

void checkCollisionHitbox()
{
	if ( BossHitbox.size() != 0 )
	{
		for ( unsigned int i = 0; i < FireOrb.size(); i++ ) // if bullet hit hitbox
		{
			if ( FireOrb[i].x == BossHitbox[0].X && FireOrb[i].y == BossHitbox[0].Y ) // if hit
			{
				if ( bosscurrentHP - 1 != 0 )
				{
					bosscurrentHP--;
					FireOrb[i].isRENDERED = false;
					BossHitbox.erase(BossHitbox.begin()); // remove both
					break; // no need to continue checking
				}
				else
				{
					bossFrameDelay = 0.0;
					bosscurrentHP--;
					FireOrb[i].isRENDERED = false;
					BossHitbox.erase(BossHitbox.begin()); // remove both
					break; // no need to continue checking
				}
			}
		}
	}
	if ( PianusHitbox.size() != 0 )
	{
		if ( charLocation.X >= PianusHitbox[0].x && charLocation.X <= PianusHitbox[0].x+2 && charLocation.Y == PianusHitbox[0].y) // if player is touching hitbox ( fishy )
		{
			hasbeenDamaged = 1; // damage player by 1
			if ( PlayerHealth > 0 ) // if player health is more than zero
				PlayerHealth--; // damage player
		}

		for ( unsigned int i = 0; i < FireOrb.size(); i++ ) // if bullet hit hitbox
		{
			if ( FireOrb[i].x == PianusHitbox[0].x && FireOrb[i].y == PianusHitbox[0].y || FireOrb[i].x-1 == PianusHitbox[0].x && FireOrb[i].y == PianusHitbox[0].y ) // if hit
			{
				if ( PianusHitbox[0].health > 0 )
				{
					FireOrb[i].isRENDERED = false;
					PianusHitbox[0].health--;
				}
				else
				{
					if ( pianuscurrentHP - 1 != 0 )
					{
						RemovePianusHitbox = 1;
						pianuscurrentHP--;
						FireOrb[i].isRENDERED = false;
						break; // no need to continue checking
					}
					else
					{
						bossFrameDelay = 0.0;
						pianuscurrentHP--;
						FireOrb[i].isRENDERED = false;
						PianusHitbox.erase(PianusHitbox.begin()); // remove both
						break; // no need to continue checking
					}
				}
			}
		}
	}
}

