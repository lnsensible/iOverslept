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
std::vector<Monster> DeadFish;
std::vector<Monster> LiveFish;
std::vector<Monster> Villager;

extern COORD charLocation;
extern COORD consoleSize;
extern int gamestate;

extern int Snailcounter;
extern int Floatercounter;
extern int InnerFearcounter;
extern int Ratcounter;
extern int Wengyewcounter;
extern int CatFishcounter;
extern int DeadFishcounter;
extern int LiveFishcounter;
extern int Villagercounter;

extern int MoneyCount;

void renderMonster() // render mobs
{                    
	for (unsigned int i = 0; i < MonsterSnail.size(); i++ ) // for all the snails
	{
		for ( int j = MonsterSnail[i].x-1; j < MonsterSnail[i].x+5; j++) //loop for checking left and right of snail when it moves
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
		for ( int j = Rat[i].x-1; j < Rat[i].x+9; j++) // loop for checking left and right of Rat when it moves
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
		for ( int j = Wengyew[i].x-1; j < Wengyew[i].x+7; j++) // loop for checking left and right of wengyews when it moves
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
		for ( int j = CatFish[i].x-1; j < CatFish[i].x+9; j++) // loop for checking left and right of CatFish when it moves
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

	for (unsigned int i = 0; i < DeadFish.size(); i++ ) // for all the DeadFishes
	{
		for ( int j = DeadFish[i].x-1; j < DeadFish[i].x+7; j++) // loop for checking left and right of DeadFish when it moves
		{
			gotoXY(j, DeadFish[i].y); // go to coordinate selected
			if ( map[DeadFish[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[DeadFish[i].y][j]; // print whatever is on the map
			}
		}

		gotoXY(DeadFish[i].x, DeadFish[i].y); // go to coordinates of DeadFish in the vector
		std::cout << ">++*>"; // print DeadFish
	}

	for (unsigned int i = 0; i < LiveFish.size(); i++ ) // for all the LiveFishes
	{
		for ( int j = LiveFish[i].x-2; j < LiveFish[i].x+6; j++) // loop for checking left and right of LiveFish when it moves
		{
			gotoXY(j, LiveFish[i].y); // go to coordinate selected
			if ( map[LiveFish[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[LiveFish[i].y][j]; // print whatever is on the map
			}
		}

		gotoXY(LiveFish[i].x, LiveFish[i].y); // go to coordinates of LiveFish in the vector
		std::cout << ">((" << (char)248 << ">"; // print LiveFish
	}

	for (unsigned int i = 0; i < Villager.size(); i++ ) // for all the Villagers
	{
		for ( int j = Villager[i].x-1; j < Villager[i].x+2; j++) //loop for checking left and right of Villager when it moves
		{
			gotoXY(j, Villager[i].y); // go to coordinate selected
			if ( map[Villager[i].y][j] == '#' ) // and reprint
			{
				std::cout << (char)219; // the wall
			}
			else
			{
				 std::cout << map[Villager[i].y][j]; // print whatever is on the map
			}
		}
		gotoXY(Villager[i].x, Villager[i].y); // go to coordinates of Villager in the vector
		std::cout << (char)1; // print Villager
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

void checkCollisionDeadFish()
	{
	for ( unsigned int i = 0; i < DeadFish.size(); i++) // for all the DeadFishes
	{
		if ( charLocation.X >= DeadFish[i].x && charLocation.X <= DeadFish[i].x+4 && charLocation.Y == DeadFish[i].y) // if player is touching the DeadFish
		{
			hasbeenDamaged = 1; // damage player by 1
			if ( PlayerHealth > 0 ) // if player health is more than zero
				PlayerHealth--; // damage player
		}
	}
}

void checkCollisionLiveFish()
	{
	for ( unsigned int i = 0; i < LiveFish.size(); i++) // for all the LiveFishes
	{
		if ( charLocation.X >= LiveFish[i].x && charLocation.X <= LiveFish[i].x+4 && charLocation.Y == LiveFish[i].y) // if player is touching the LiveFish
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
			if ( map[Rat[i].y][Rat[i].x+8] != '#' && map[Rat[i].y+1][Rat[i].x+7] == '#' ) // If move right is possible
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
					Wengyew[i].x--; // chase player
			}
			else // if character on wengyews' right
			{
				if ( map[Wengyew[i].y][Wengyew[i].x+3] != '#' && map[Wengyew[i].y+1][Wengyew[i].x+7] == '#' ) // If move right is possible
					Wengyew[i].x++; // chase player
			}
		}
		if ( rand() % 2 == 0 )
		{
			if ( map[Wengyew[i].y][Wengyew[i].x-1] != '#' && map[Wengyew[i].y+1][Wengyew[i].x-1] == '#' ) // If move left is possible
				Wengyew[i].x--;
		}
		else
		{
			if ( map[Wengyew[i].y][Wengyew[i].x+5] != '#' && map[Wengyew[i].y+1][Wengyew[i].x+7] == '#' ) // If move right is possible
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

void updateDeadFish() // DeadFish movement update
{
	for (unsigned int i = 0; i < DeadFish.size(); i++ ) // for all DeadFishes
	{
		if ( charLocation.Y == DeadFish[i].y ) // if character same Y coordinate as DeadFish
		{
			if ( charLocation.X <= DeadFish[i].x ) // if character on DeadFish's left
			{
				if ( map[DeadFish[i].y][DeadFish[i].x-1] != '#' && map[DeadFish[i].y+1][DeadFish[i].x-1] == '#' ) // If move left is possible
					DeadFish[i].x--; // chase player
			}
			else // if character on DeadFish's right
			{
				if ( map[DeadFish[i].y][DeadFish[i].x+3] != '#' && map[DeadFish[i].y+1][DeadFish[i].x+7] == '#' ) // If move right is possible
					DeadFish[i].x++; // chase player
			}
		}
		if ( rand() % 2 == 0 )
		{
			if ( map[DeadFish[i].y][DeadFish[i].x-1] != '#' && map[DeadFish[i].y+1][DeadFish[i].x-1] == '#' ) // If move left is possible
				DeadFish[i].x--;
		}
		else
		{
			if ( map[DeadFish[i].y][DeadFish[i].x+5] != '#' && map[DeadFish[i].y+1][DeadFish[i].x+7] == '#' ) // If move right is possible
				DeadFish[i].x++;
		}
	}
}


void updateLiveFish() // LiveFish movement update
{
	for (unsigned int i = 0; i < LiveFish.size(); i++ ) // for all LiveFishes
	{
		if ( charLocation.Y == LiveFish[i].y ) // if character same Y coordinate as LiveFish
		{
			if ( charLocation.X <= LiveFish[i].x ) // if character on LiveFish's left
			{
				if ( map[LiveFish[i].y][LiveFish[i].x+6] != '#' && map[LiveFish[i].y+1][LiveFish[i].x+6] == '#' ) // If move right is possible
					LiveFish[i].x++;  // run away
			}
			else // if character on LiveFish's right
			{
				if ( map[LiveFish[i].y][LiveFish[i].x-1] != '#' && map[LiveFish[i].y+1][LiveFish[i].x-1] == '#' ) // If move left is possible
					LiveFish[i].x--; // run away
			}
		}
		if ( rand() % 2 == 0 )
		{
			if ( map[LiveFish[i].y][LiveFish[i].x-1] != '#' && map[LiveFish[i].y+1][LiveFish[i].x-1] == '#' ) // If move left is possible
				LiveFish[i].x--;
		}
		else
		{
			if ( map[LiveFish[i].y][LiveFish[i].x+6] != '#' && map[LiveFish[i].y+1][LiveFish[i].x+6] == '#' ) // If move right is possible
				LiveFish[i].x++;
		}
	}
}

void updateVillager() // Villager movement update
{
	for (unsigned int i = 0; i < Villager.size(); i++ ) // for all Villagers
	{
		if ( rand() % 2 == 0 )
		{
			if ( map[Villager[i].y][Villager[i].x-1] != '#' && map[Villager[i].y+1][Villager[i].x-1] == '#' ) // If move left is possible
				Villager[i].x--;
		}
		else
		{
			if ( map[Villager[i].y][Villager[i].x+1] != '#' && map[Villager[i].y+1][Villager[i].x+1] == '#' ) // If move right is possible
				Villager[i].x++;
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

			MonsterSnail.erase(MonsterSnail.begin() + i);// remove snail from map
			MoneyCount = MoneyCount + 1; // adds Quennies
			renderMoney(); // updates Quennies in U.I.
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
			MoneyCount = MoneyCount + 1; // adds Quennies
			renderMoney(); // updates Quennies in U.I.
		}
	}

	for (unsigned int i = 0; i < InnerFear.size(); i++)
	{
		if ( InnerFear[i].health <= 0 )
		{
			gotoXY(InnerFear[i].x, InnerFear[i].y);
			std::cout << " ";
			map[InnerFear[i].y][InnerFear[i].x] = ' ';

			InnerFear.erase(InnerFear.begin() + i);// remove innerfear from map
			MoneyCount = MoneyCount + 2; // adds Quennies
			renderMoney(); // updates Quennies in U.I.
		}
	}

	for (unsigned int i = 0; i < Rat.size(); i++)
	{
		if ( Rat[i].health <= 0 )
		{
			gotoXY(Rat[i].x, Rat[i].y);
			std::cout << "       ";
			map[Rat[i].y][Rat[i].x] = ' ';

			Rat.erase(Rat.begin() + i);// remove rat from map
			MoneyCount = MoneyCount + 4; // adds Quennies
			renderMoney(); // updates Quennies in U.I.
		}
	}

	for (unsigned int i = 0; i < Wengyew.size(); i++)
	{
		if ( Wengyew[i].health <= 0 )
		{
			gotoXY(Wengyew[i].x, Wengyew[i].y);
			std::cout << "     ";
			map[Wengyew[i].y][Wengyew[i].x] = ' ';

			Wengyew.erase(Wengyew.begin() + i);// remove wengyew from map
			MoneyCount = MoneyCount + 15; // adds Quennies
			renderMoney(); // updates Quennies in U.I.
		}
	}

	for (unsigned int i = 0; i < CatFish.size(); i++)
	{
		if ( CatFish[i].health <= 0 )
		{
			gotoXY(CatFish[i].x, CatFish[i].y);
			std::cout << "       ";
			map[CatFish[i].y][CatFish[i].x] = ' ';

			CatFish.erase(CatFish.begin() + i);// remove catfish from map
			MoneyCount = MoneyCount + 3; // adds Quennies
			renderMoney(); // updates Quennies in U.I.
		}
	}

	for (unsigned int i = 0; i < DeadFish.size(); i++)
	{
		if ( DeadFish[i].health <= 0 )
		{
			gotoXY(DeadFish[i].x, DeadFish[i].y);
			std::cout << "     ";
			map[DeadFish[i].y][DeadFish[i].x] = ' ';

			DeadFish.erase(DeadFish.begin() + i);// remove deadfish from map
			MoneyCount = MoneyCount + 6; // adds Quennies
			renderMoney(); // updates Quennies in U.I.
		}
	}

	for (unsigned int i = 0; i < LiveFish.size(); i++)
	{
		if ( LiveFish[i].health <= 0 )
		{
			gotoXY(LiveFish[i].x, LiveFish[i].y);
			std::cout << "     ";
			map[LiveFish[i].y][LiveFish[i].x] = ' ';

			Monster respawn; // function for respawning
			respawn.x = LiveFish[i].x; // respawns at last x-coordinate of LiveFish 
			respawn.y = LiveFish[i].y; // respawns at last y-coordinate of LiveFish
			respawn.health = 4; // respawn with specified health

			DeadFish.push_back(respawn); // pushes into DeadFish vector

			LiveFish.erase(LiveFish.begin() + i);// remove livefish from map
			// no Quennies for you for killing a fish!
		}
	}
}
