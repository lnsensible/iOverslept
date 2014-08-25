// This is file for the weapon stuff
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

extern COORD charLocation;
extern int playerFacing; // 0 = left, 1 = right

extern std::vector<Monster> MonsterSnail;
extern std::vector<Monster> Floater;
extern std::vector<Monster> InnerFear;
extern std::vector<Monster> Rat;
extern std::vector<Monster> Wengyew;
extern std::vector<Monster> CatFish;

std::vector<Bullets_Properties> Bullets;

void Attack()
{
	if ( playerFacing == 0 ) // if facing left,
	{
		Bullets_Properties addBullet;
		addBullet.x = charLocation.X-1;
		addBullet.y = charLocation.Y;
		addBullet.faceWhere = false;
		addBullet.isRENDERED = true;
		addBullet.Damage = 1;

		Bullets.push_back(addBullet);
	}
	else if ( playerFacing == 1 ) // if facing right
	{
		Bullets_Properties addBullet;
		addBullet.x = charLocation.X+1;
		addBullet.y = charLocation.Y;
		addBullet.faceWhere = true;
		addBullet.isRENDERED = true;
		addBullet.Damage = 1;

		Bullets.push_back(addBullet);
	}
}

void checkCollisionWithMonster()
{
	for ( unsigned int i = 0; i < MonsterSnail.size(); i++)
	{
		for ( unsigned int j = 0; j < Bullets.size(); j++)
		{
			if (Bullets[j].x == MonsterSnail[i].x && Bullets[j].y == MonsterSnail[i].y)
			{
				MonsterSnail[i].health -= Bullets[j].Damage;
				Bullets.erase(Bullets.begin() + j); // remove bullets
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}
		/*//there is a way to make the cursor invisible when rendering. go google pls.
		for ( unsigned int j = 0; j<Floater.size(); j ++)
		{
			if (Bullets[i].x == Floater[j].x && Bullets[i].y == Floater[j].y)
			{
				Floater[j].health -= Bullets[i].Damage;
				Bullets.erase(Bullets.begin() + i);
				//checkMonsterDead();
				if (Floater[j].health <= 0)
				{
					Floater.erase(Floater.begin() + j);
				}
			}
		}

		for (unsigned int j = 0; j<InnerFear.size(); j ++)
		{
			if (Bullets[i].x == InnerFear[j].x && Bullets[i].y == InnerFear[j].y)
			{
				InnerFear[j].health -= Bullets[i].Damage;
				Bullets.erase(Bullets.begin() + i);
				checkMonsterDead();
				if (InnerFear[j].health <= 0)
				{
					InnerFear.erase(InnerFear.begin() + j);
				}
			}
		}

		for ( unsigned int j = 0; j<Wengyew.size(); j ++)
		{
			if (Bullets[i].x == Wengyew[j].x && Bullets[i].y == Wengyew[j].y)
			{
				Wengyew[j].health -= Bullets[i].Damage;
				Bullets.erase(Bullets.begin() + i);
				checkMonsterDead();
				if (Wengyew[j].health <= 0)
				{
					Wengyew.erase(Wengyew.begin() + j);
				}
			}
		}

		for ( unsigned int j = 0; j < Rat.size(); j ++)
		{
			if (Bullets[i].x == Rat[j].x && Bullets[i].y == Rat[j].y)
			{
				Rat[j].health -= Bullets[i].Damage;
				Bullets.erase(Bullets.begin() + i);
				checkMonsterDead();
				if (Rat[j].health <= 0)
				{
					Rat.erase(Rat.begin() + j);
				}
			}
		}

		for ( unsigned int j = 0; j < CatFish.size(); j ++)
		{
			if (Bullets[i].x == CatFish[j].x && Bullets[i].y == CatFish[j].y)
			{
				CatFish[j].health -= Bullets[i].Damage;
				Bullets.erase(Bullets.begin() + i);
				checkMonsterDead();
				if (CatFish[j].health <= 0)
				{
					CatFish.erase(CatFish.begin() + j);
				}
			}
		}*/
}

void checkCollisionWithWall()
{
	for ( unsigned int i = 0; i < Bullets.size(); ++i )
	{
		if ( map[Bullets[i].y][Bullets[i].x] == '#' ) 
		{
			Bullets[i].isRENDERED = false;
		}
	}
}


void updateBullets()
{
	for (unsigned int h = 0; h < Bullets.size(); ++h)
	{
		if (Bullets[h].faceWhere == false)
		{
			Bullets[h].x -= 1;
		}
		else if (Bullets[h].faceWhere == true)
		{
			Bullets[h].x += 1;
		}
		checkCollisionWithMonster();
		checkCollisionWithWall();
	}
}

void spawnBullets(){
	for(unsigned int x = 0; x < Bullets.size(); ++x)
	{
		if ( Bullets[x].isRENDERED == false ) // need to remove bullet
		{

			gotoXY(Bullets[x].x-1, Bullets[x].y);
			if ( map[Bullets[x].y][Bullets[x].x-1] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[Bullets[x].y][Bullets[x].x-1] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[Bullets[x].y][Bullets[x].x-1] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
			std::cout<< map[Bullets[x].y][Bullets[x].x-1];
			}

			gotoXY(Bullets[x].x, Bullets[x].y);
			if ( map[Bullets[x].y][Bullets[x].x] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[Bullets[x].y][Bullets[x].x] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[Bullets[x].y][Bullets[x].x] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
			std::cout<< map[Bullets[x].y][Bullets[x].x];
			}

			gotoXY(Bullets[x].x+1, Bullets[x].y);
			if ( map[Bullets[x].y][Bullets[x].x+1] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[Bullets[x].y][Bullets[x].x+1] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[Bullets[x].y][Bullets[x].x+1] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
			std::cout<< map[Bullets[x].y][Bullets[x].x+1];
			}

			Bullets.erase(Bullets.begin() + x);
		}
		else
		{
			if ( Bullets[x].faceWhere == false )
			{
				gotoXY(Bullets[x].x+1, Bullets[x].y);
				std::cout<< map[Bullets[x].y][Bullets[x].x+1];
				gotoXY(Bullets[x].x, Bullets[x].y);
				std::cout<<"o";
			}
			else if ( Bullets[x].faceWhere == true )
			{
				gotoXY(Bullets[x].x-1, Bullets[x].y);
				std::cout<< map[Bullets[x].y][Bullets[x].x-1];
				gotoXY(Bullets[x].x, Bullets[x].y);
				std::cout<<"o";
			}
		}
	}
}