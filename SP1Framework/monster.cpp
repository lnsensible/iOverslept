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

extern COORD charLocation;
extern COORD consoleSize;
extern int gamestate;

void checkCollisionSnail() // checks if player collies with snail
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

void checkCollisionFloater() // checks if player collides with floater
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

void checkCollisionInnerFear() // checks if player collides with innerfear
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

void checkCollisionRat() // checks if player collides with rat
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
						std::cout << "   "; // space for snails
						map[i][j] = ' ';
						map[i][j-1] = 'S';
					}
				}
				else // movement right
				{
					if ( map[i][j+3] != '#' && map[i+1][j+1] == '#' )
					{
						gotoXY(j, i);
						std::cout << "   "; // space for snails
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
						std::cout << "       "; // space for rats
						map[i][j] = ' ';
						map[i][j-1] = 'R';
					}
				}
				else // movement right
				{
					if ( map[i][j+7] != '#' && map[i+1][j+7] == '#' )
					{
						gotoXY(j, i);
						std::cout << "       "; // space for rats
						map[i][j] = ' ';
						map[i][j+1] = 'R';
					}
				}
			}
		}
	}
}