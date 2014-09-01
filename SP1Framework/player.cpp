// File containing stuff related to player

#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector> 

int isJumping = 0; // Check if character is jumping. 0 = Not jumping, 1 = Jumping
int hasbeenStabbed = 0; // Check if character has been stabbed by a needle/spike to determine if spikes need to be re rendered
int hasbeenDamaged = 0; // Check if character was damaged. If yes, need to re-render HP. All to prevent flickering ); 0 = No change, 1 = Changed
int playerLevel = 0; // Level of player
int playerExperience = 0; // EXP of player
int exptolevelup = 0;

double canJump = 0; // Check if you have jumped in the past 0.8 ms
double jumpDelay = 0; // delay between y coordinate change while jumping
double fallDelay = 0; // delay between falling (no delay for initial fall)

bool spawnwhere = false; // false = spawn at C, true = spawn at c
bool fromSPortal = false;

extern COORD charLocation;
extern COORD consoleSize;
extern int gamestate;
extern int hasMoved;
extern bool outsideShop;


extern int MoneyCount;
extern int MoneyInv;



void LevelUp()
{
	exptolevelup = playerLevel * 500;
	if ( playerExperience >= exptolevelup )
	{
		playerExperience -= exptolevelup;
		playerLevel++;
		if ( PlayerHealth < 5 )
			PlayerHealth++;
		renderHP();
	}
}

void renderXPLevel()
{
	gotoXY(6, 28);
	std::cout << "Level: " << playerLevel;
	gotoXY(6, 30);
	std::cout << "EXP: " << playerExperience << " / " << exptolevelup; 
}

void jump()
{
	if ( map[charLocation.Y+1][charLocation.X] == '#' && map[charLocation.Y-1][charLocation.X] != '#' && canJump > 0.800 ) // You're standing on the ground, and there's no ceiling above you, and you haven't jumped in the last 0.8 seconds
	{
		playGameSound(S_JUMP);
		isJumping = 1;
		canJump = 0.0;
		hasMoved = 1;
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
			hasMoved = 1;
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
				hasMoved = 1;
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
			hasMoved = 1;
			charLocation.Y++; // Fall!
			fallDelay = 0;
		}
	}
}

void checkforDeath()
{
	if ( PlayerHealth <= 0 )
	{

		MoneyCount = MoneyCount - MoneyInv;
		MoneyInv = 0;
		if(MoneyCount > 4)
		{
			MoneyCount = MoneyCount - 5;
		}
		playerExperience = 0;

		saveGame();
		gamestate = DEATH;
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


/*
void checkforShop()
{
if (map[charLocation.Y][charLocation.X] == '+')
{
isSHOP = true; //If true, then you can enter.
}
}

void renderShop()
{

}
*/
void spawnWhere()
{
	if (outsideShop == false)// If travel through shop
	{
		for ( int i = 0; i < MAPHEIGHT; i++ )
		{
			for ( int j = 0; j < MAPWIDTH; j++ )
			{
				if (map[i][j] == '+')
				{
					charLocation.X = j+1;
					charLocation.Y = i;
				}
				if ( map[i][j] == 'c' )
				{
					map[i][j] = ' '; //replace c with space.
				}
				if ( map[i][j] == 'C' )
				{
					map[i][j] = ' '; //remove C.
				}
				if ( map[i][j] == 'f' )
				{
					map[i][j] = ' '; //replace f with space.
				}

				outsideShop = true;
			}
		}
	}
	else
		if(fromSPortal == true)//if travel through special portal
		{
			for ( int i = 0; i < MAPHEIGHT; i++ )
			{
				for ( int j = 0; j < MAPWIDTH; j++ )
				{
					if ( map[i][j] == 'f' )
					{
						charLocation.X = j;
						charLocation.Y = i;
						map[i][j] = ' '; //replace f with space.
						fromSPortal = false;
					}

					if ( map[i][j] == 'c' )
					{
						map[i][j] = ' '; //replace c with space.
					}
					if ( map[i][j] == 'C' )
					{
						map[i][j] = ' '; //remove C.
					}
				}
			}
		}

		else if (spawnwhere == true && fromSPortal == false) // came from next map
		{
			for ( int i = 0; i < MAPHEIGHT; i++ )
			{
				for ( int j = 0; j < MAPWIDTH; j++ )
				{
					if ( map[i][j] == 'c' )
					{
						charLocation.X = j;
						charLocation.Y = i;
						map[i][j] = ' '; //replace c with space.
					}
					if ( map[i][j] == 'C' )
					{
						map[i][j] = ' '; //remove C.
					}
					if ( map[i][j] == 'f' )
					{
						map[i][j] = ' '; //replace f with space.
					}
				}
			}
		}
		else if (spawnwhere == false && fromSPortal == false) //came from previous map
		{
			for ( int i = 0; i < MAPHEIGHT; i++ )
			{
				for ( int j = 0; j < MAPWIDTH; j++ )
				{
					if ( map[i][j] == 'c' )
					{
						map[i][j] = ' '; //remove c.
					}
					if ( map[i][j] == 'C' )
					{
						charLocation.X = j;
						charLocation.Y = i;
						map[i][j] = ' '; //replace C with space.
					}
					if ( map[i][j] == 'f' )
					{
						map[i][j] = ' '; //replace f with space.
					}
				}
			}
		}
}