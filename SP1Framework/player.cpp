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

double canJump = 0; // Check if you have jumped in the past 0.8 ms
double jumpDelay = 0; // delay between y coordinate change while jumping
double fallDelay = 0; // delay between falling (no delay for initial fall)

extern COORD charLocation;
extern COORD consoleSize;
extern int gamestate;

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

void checkforDeath()
{
	if ( PlayerHealth <= 0 )
	{
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