// File containing stuff related to monsters

#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

std::vector<Monster> MonsterSnail;
std::vector<Monster> Floater;
std::vector<Monster> InnerFear;
std::vector<Monster> Rat;
std::vector<Monster> Wengyew;
std::vector<Monster> CatFish;

extern COORD charLocation;
extern COORD consoleSize;
extern int gamestate;

extern int Snailcounter;
extern int Floatercounter;
extern int InnerFearcounter;
extern int Ratcounter;
extern int Wengyewcounter;
extern int CatFishcounter;

void renderMonster() // render mobs
{                    
	for (unsigned int i = 0; i < MonsterSnail.size(); i++ ) // for all the snails
	{
		for ( int j = MonsterSnail[i].x-1; j < MonsterSnail[i].x+4; j++) //loop for checking left and right of snail when it moves
		{
			gotoXY(j, MonsterSnail[i].y); // go to coordinate selected
			if ( map[MonsterSnail[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[MonsterSnail[i].y][j]; // print whatever is on the map
			}
		}

		gotoXY(MonsterSnail[i].x, MonsterSnail[i].y); // go to coordinates of snail in the vector 
		std::cout << "@/'"; // print snail
	}

	for (unsigned int i = 0; i < Floater.size(); i++ ) // for all the floaters
	{
		for ( int j = Floater[i].x-1; j < Floater[i].x+2; j++) // loop for checking left and right of floater when it moves
		{
			gotoXY(j, Floater[i].y); // go to coordinate selected
			if ( map[Floater[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[Floater[i].y][j]; // print whatever is on the map
			}
		}

		gotoXY(Floater[i].x, Floater[i].y); // go to coordinates of floater in the vector
		std::cout << (char)235; // print floater
	}

	for (unsigned int i = 0; i < InnerFear.size(); i++ ) // for all the InnerFears
	{
		for ( int j = InnerFear[i].x-1; j < InnerFear[i].x+2; j++) // loop for checking left and right of InnerFear when it moves
		{
			gotoXY(j, InnerFear[i].y); // go to coordinate selected
			if ( map[InnerFear[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[InnerFear[i].y][j]; // print whatever is on the map
			}
		}

		gotoXY(InnerFear[i].x, InnerFear[i].y); // go to coordinates of InnerFear in the vector
		std::cout << (char)12; // print InnerFear
	}
		
	for (unsigned int i = 0; i < Rat.size(); i++ ) // for all the Rats
	{
		for ( int j = Rat[i].x-1; j < Rat[i].x+8; j++) // loop for checking left and right of Rat when it moves
		{
			gotoXY(j, Rat[i].y); // go to coordinate selected
			if ( map[Rat[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[Rat[i].y][j]; // print whatever is on the map
			}
		}

		gotoXY(Rat[i].x, Rat[i].y); // go to coordinates of Rat in the vector
		std::cout << "~~(_^" << (char)249 << ">"; // print Rat
	}

	for (unsigned int i = 0; i < Wengyew.size(); i++ ) // for all the wengyews
	{
		for ( int j = Wengyew[i].x-2; j < Wengyew[i].x+7; j++) // loop for checking left and right of wengyews when it moves
		{
			gotoXY(j, Wengyew[i].y); // go to coordinate selected
			if ( map[Wengyew[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[Wengyew[i].y][j]; // print whatever is on the map
			}
		}

		gotoXY(Wengyew[i].x, Wengyew[i].y); // go to coordinates of wengyew in the vector
		std::cout << (char)244 << (char)229 << (char)247 << (char)229 << (char)245; // print wengyew
	}
	

	for (unsigned int i = 0; i < CatFish.size(); i++ ) // for all the CatFishes
	{
		for ( int j = CatFish[i].x-1; j < CatFish[i].x+8; j++) // loop for checking left and right of CatFish when it moves
		{
			gotoXY(j, CatFish[i].y); // go to coordinate selected
			if ( map[CatFish[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[CatFish[i].y][j]; // print whatever is on the map
			}
		}

		gotoXY(CatFish[i].x, CatFish[i].y); // go to coordinates of CatFish in the vector
		std::cout << ">)))^" << (char)249 << ">"; // print CatFish
	}
}

void checkCollisionSnail()
{
	for ( unsigned int i = 0; i < MonsterSnail.size(); i++) // for all the Snails
	{
		if ( charLocation.X >= MonsterSnail[i].x && charLocation.X <= MonsterSnail[i].x+2 && charLocation.Y == MonsterSnail[i].y) // if player is touching the Snail
		{
			hasbeenDamaged = 1; // damage player by 1
			if ( PlayerHealth > 0 ) // if player health is more than zero
				PlayerHealth--; // damage player
		}
	}
}

void checkCollisionFloater()
{
	for ( unsigned int i = 0; i < Floater.size(); i++) // for all the Floaters
	{
		if ( charLocation.X ==Floater[i].x && charLocation.Y == Floater[i].y) // if player is touching the Floater
		{
			hasbeenDamaged = 1; // damage player by 1
			if ( PlayerHealth > 0 ) // if player health is more than zero
				PlayerHealth--; // damage player
		}
	}
}

void checkCollisionInnerFear()
{
	for ( unsigned int i = 0; i < InnerFear.size(); i++) // for all the InnerFears
	{
		if ( charLocation.X ==InnerFear[i].x && charLocation.Y == InnerFear[i].y) // if player is touching the InnerFear
		{
			hasbeenDamaged = 1; // damage player by 1
			if ( PlayerHealth > 0 ) // if player health is more than zero
				PlayerHealth--; // damage player
		}
	}
}

void checkCollisionRat()
	{
	for ( unsigned int i = 0; i < Rat.size(); i++) // for all the Rats
	{
		if ( charLocation.X >= Rat[i].x && charLocation.X <= Rat[i].x+7 && charLocation.Y == Rat[i].y) // if player is touching the Rat
		{
			hasbeenDamaged = 1; // damage player by 1
			if ( PlayerHealth > 0 ) // if player health is more than zero
				PlayerHealth--; // damage player
		}
	}
}

void checkCollisionWengyew()
	{
	for ( unsigned int i = 0; i < Wengyew.size(); i++) // for all the Wengyews
	{
		if ( charLocation.X >= Wengyew[i].x && charLocation.X <= Wengyew[i].x+4 && charLocation.Y == Wengyew[i].y) // if player is touching the Wengyew
		{
			hasbeenDamaged = 1; // damage player by 1
			if ( PlayerHealth > 0 ) // if player health is more than zero
				PlayerHealth--; // damage player
		}
	}
}

void checkCollisionCatFish()
	{
	for ( unsigned int i = 0; i < CatFish.size(); i++) // for all the CatFishes
	{
		if ( charLocation.X >= CatFish[i].x && charLocation.X <= CatFish[i].x+6 && charLocation.Y == CatFish[i].y) // if player is touching the CatFish
		{
			hasbeenDamaged = 1; // damage player by 1
			if ( PlayerHealth > 0 ) // if player health is more than zero
				PlayerHealth--; // damage player
		}
	}
}

void updateSnails() // snail movement update
{
	for (unsigned int i = 0; i < MonsterSnail.size(); i++ ) // for all Snails
	{
		if ( rand() % 2 == 0 )
		{
			if ( map[MonsterSnail[i].y][MonsterSnail[i].x-1] != '#' && map[MonsterSnail[i].y+1][MonsterSnail[i].x-1] == '#' ) // If move left is possible
				MonsterSnail[i].x--;
		}
		else
		{
			if ( map[MonsterSnail[i].y][MonsterSnail[i].x+3] != '#' && map[MonsterSnail[i].y+1][MonsterSnail[i].x+3] == '#' ) // If move right is possible
				MonsterSnail[i].x++;
		}
	}
}

void updateFloater() // floater movement update
{
	for (unsigned int i = 0; i < Floater.size(); i++ ) // for all Floaters
	{
		if ( rand() % 2 == 0 )
		{
			if ( map[Floater[i].y][Floater[i].x-1] != '#' && map[Floater[i].y+1][Floater[i].x-1] == '#' ) // If move left is possible
				Floater[i].x--;
		}
		else
		{
			if ( map[Floater[i].y][Floater[i].x+1] != '#' && map[Floater[i].y+1][Floater[i].x+1] == '#' ) // If move right is possible
				Floater[i].x++;
		}
	}
}

void updateInnerFear() // InnerFear movement update
{
	for (unsigned int i = 0; i < InnerFear.size(); i++ ) // for all InnerFears
	{
		if ( rand() % 2 == 0 )
		{
			if ( map[InnerFear[i].y][InnerFear[i].x-1] != '#' && map[InnerFear[i].y+1][InnerFear[i].x-1] == '#' ) // If move left is possible
				InnerFear[i].x--;
		}
		else
		{
			if ( map[InnerFear[i].y][InnerFear[i].x+1] != '#' && map[InnerFear[i].y+1][InnerFear[i].x+1] == '#' ) // If move right is possible
				InnerFear[i].x++;
		}
	}
}

void updateRat() // Rat movement update
{
	for (unsigned int i = 0; i < Rat.size(); i++ ) // for all Rats
	{
		if ( rand() % 2 == 0 )
		{
			if ( map[Rat[i].y][Rat[i].x-1] != '#' && map[Rat[i].y+1][Rat[i].x-1] == '#' ) // If move left is possible
				Rat[i].x--;
		}
		else
		{
			if ( map[Rat[i].y][Rat[i].x+3] != '#' && map[Rat[i].y+1][Rat[i].x+7] == '#' ) // If move right is possible
				Rat[i].x++;
		}
	}
}

void updateWengyew() // Wengyew movement update
{
	for (unsigned int i = 0; i < Wengyew.size(); i++ ) // for all Wengyews
	{
		if ( charLocation.Y == Wengyew[i].y ) // if character same Y coordinate as Wengyew
		{
			if ( charLocation.X <= Wengyew[i].x ) // if character on wengyew's left
			{
				if ( map[Wengyew[i].y][Wengyew[i].x-1] != '#' && map[Wengyew[i].y+1][Wengyew[i].x-1] == '#' ) // If move left is possible
					Wengyew[i].x--;
			}
			else // if character on wengyews' right
			{
				if ( map[Wengyew[i].y][Wengyew[i].x+3] != '#' && map[Wengyew[i].y+1][Wengyew[i].x+7] == '#' ) // If move right is possible
					Wengyew[i].x++;
			}
		}
		if ( rand() % 2 == 0 )
		{
			if ( map[Wengyew[i].y][Wengyew[i].x-1] != '#' && map[Wengyew[i].y+1][Wengyew[i].x-1] == '#' ) // If move left is possible
				Wengyew[i].x--;
		}
		else
		{
			if ( map[Wengyew[i].y][Wengyew[i].x+3] != '#' && map[Wengyew[i].y+1][Wengyew[i].x+7] == '#' ) // If move right is possible
				Wengyew[i].x++;
		}
	}
}

void updateCatFish() // CatFish movement update
{
	for (unsigned int i = 0; i < CatFish.size(); i++ ) // for all CatFishes
	{
		if ( rand() % 2 == 0 )
		{
			if ( map[CatFish[i].y][CatFish[i].x-1] != '#' && map[CatFish[i].y+1][CatFish[i].x-1] == '#' ) // If move left is possible
				CatFish[i].x--;
		}
		else
		{
			if ( map[CatFish[i].y][CatFish[i].x+3] != '#' && map[CatFish[i].y+1][CatFish[i].x+7] == '#' ) // If move right is possible
				CatFish[i].x++;
		}
	}
}

void checkMonsterDead()
{
	for (unsigned int i = 0; i < MonsterSnail.size(); i++)
	{
		if ( MonsterSnail[i].health <= 0 )
		{
			gotoXY(MonsterSnail[i].x, MonsterSnail[i].y);
			std::cout << "   ";
			map[MonsterSnail[i].y][MonsterSnail[i].x] = ' ';

			MonsterSnail.erase(MonsterSnail.begin() + i);// remove snail from map, nt sure if it works
		}
	}

	for (unsigned int i = 0; i < Floater.size(); i++)
	{
		if ( Floater[i].health <= 0 )
		{
			gotoXY(Floater[i].x, Floater[i].y);
			std::cout << " ";
			map[Floater[i].y][Floater[i].x] = ' ';

			Floater.erase(Floater.begin() + i);// remove floater from map
		}
	}

	for (unsigned int i = 0; i < InnerFear.size(); i++)
	{
		if ( InnerFear[i].health <= 0 )
		{
			gotoXY(InnerFear[i].x, InnerFear[i].y);
			std::cout << " ";
			map[InnerFear[i].y][InnerFear[i].x] = ' ';

			InnerFear.erase(InnerFear.begin() + i);// remove InnerFear from map
		}
	}

	for (unsigned int i = 0; i < Rat.size(); i++)
	{
		if ( Rat[i].health <= 0 )
		{
			gotoXY(Rat[i].x, Rat[i].y);
			std::cout << "       ";
			map[Rat[i].y][Rat[i].x] = ' ';

			Rat.erase(Rat.begin() + i);// remove Rat from map
		}
	}

	for (unsigned int i = 0; i < Wengyew.size(); i++)
	{
		if ( Wengyew[i].health <= 0 )
		{
			gotoXY(Wengyew[i].x, Wengyew[i].y);
			std::cout << "     ";
			map[Wengyew[i].y][Wengyew[i].x] = ' ';

			Wengyew.erase(Wengyew.begin() + i);// remove Wengyew from map
		}
	}

	for (unsigned int i = 0; i < CatFish.size(); i++)
	{
		if ( CatFish[i].health <= 0 )
		{
			gotoXY(CatFish[i].x, CatFish[i].y);
			std::cout << "       ";
			map[CatFish[i].y][CatFish[i].x] = ' ';

			CatFish.erase(CatFish.begin() + i);// remove CatFish from map
		}
	}
}
