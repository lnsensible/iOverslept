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
extern int playerFacing; //0 = left, 1 = right

extern std::vector<Monster> MonsterSnail;
extern std::vector<Monster> Floater;
extern std::vector<Monster> InnerFear;
extern std::vector<Monster> Rat;
extern std::vector<Monster> Wengyew;
extern std::vector<Monster> CatFish;
extern std::vector<Monster> DeadFish;
extern std::vector<Monster> PianusHitbox;
extern void checkMonsterDead();



std::vector<Skill_Properties> FireOrb,LightningOrb,WaterOrb;
std::vector<Skill_Properties> CKey = FireOrb;

void initSkill()
{
	for (unsigned int x =0; x<FireOrb.size(); ++x)
	{
		FireOrb[x].Damage = 100;
		FireOrb[x].Range = 50;
	}
}


void checkCollisionWithMonster(std::vector<Skill_Properties>& Skill)
{
	for ( unsigned int i = 0; i < MonsterSnail.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == MonsterSnail[i].x && Skill[j].y == MonsterSnail[i].y)
			{
				MonsterSnail[i].health -= Skill[j].Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < Floater.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Floater[i].x && Skill[j].y == Floater[i].y)
			{
				Floater[i].health -= Skill[j].Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < Rat.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Rat[i].x && Skill[j].y == Rat[i].y)
			{
				Rat[i].health -= Skill[j].Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	/*
	for ( unsigned int i = 0; i < PianusHitbox.size(); i++)//PIanus thingy
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == PianusHitbox[i].x && Skill[j].y == PianusHitbox[i].y)
			{
				PianusHitbox[i].health -= Skill[j].Damage;
				Skill.erase(FireOrb.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}
	*/


	for ( unsigned int i = 0; i < InnerFear.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == InnerFear[i].x && Skill[j].y == InnerFear[i].y)
			{
				InnerFear[i].health -= Skill[j].Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < Wengyew.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Wengyew[i].x && Skill[j].y == Wengyew[i].y)
			{
				Wengyew[i].health -= Skill[j].Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < CatFish.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == CatFish[i].x && Skill[j].y == CatFish[i].y)
			{
				CatFish[i].health -= Skill[j].Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < DeadFish.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == DeadFish[i].x && Skill[j].y == DeadFish[i].y)
			{
				DeadFish[i].health -= Skill[j].Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}


}

void checkCollisionWithWall(std::vector<Skill_Properties>& Skill)
{
	for ( unsigned int i = 0; i < Skill.size(); ++i )
	{
		if ( map[Skill[i].y][Skill[i].x] == '#' ) 
		{
			Skill[i].isRENDERED = false;
		}
	}
}

void Attack(std::vector<Skill_Properties>& Skill)
{
	if ( playerFacing == 0 ) // if facing left,
	{
		Skill_Properties addBullet;
		addBullet.x = charLocation.X-1;
		addBullet.y = charLocation.Y;
		addBullet.faceWhere = false;
		addBullet.isRENDERED = true;

		Skill.push_back(addBullet);
	}
	else if ( playerFacing == 1 ) // if facing right
	{
		Skill_Properties addBullet;
		addBullet.x = charLocation.X+1;
		addBullet.y = charLocation.Y;
		addBullet.faceWhere = true;
		addBullet.isRENDERED = true;
		Skill.push_back(addBullet);
	}
}

void updateSkill(std::vector<Skill_Properties>& Skill)
{
	for (unsigned int h = 0; h < Skill.size(); ++h)
	{
		if (Skill[h].faceWhere == false)
		{
			Skill[h].x -= 1;
		}
		else if (Skill[h].faceWhere == true)
		{
			Skill[h].x += 1;
		}
		checkCollisionWithMonster(Skill);
		checkCollisionWithWall(Skill);

	}
}

void spawnSkill(std::vector<Skill_Properties>& Skill){
	for(unsigned int x = 0; x < Skill.size(); ++x)
	{
		if ( Skill[x].isRENDERED == false ) // need to remove bullet
		{

			gotoXY(Skill[x].x-1, Skill[x].y);
			if ( map[Skill[x].y][Skill[x].x-1] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[Skill[x].y][Skill[x].x-1] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[Skill[x].y][Skill[x].x-1] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[Skill[x].y][Skill[x].x-1];
			}

			gotoXY(Skill[x].x, Skill[x].y);
			if ( map[Skill[x].y][Skill[x].x] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[Skill[x].y][Skill[x].x] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[Skill[x].y][Skill[x].x] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[Skill[x].y][Skill[x].x];
			}

			gotoXY(Skill[x].x+1, Skill[x].y);
			if ( map[Skill[x].y][Skill[x].x+1] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[Skill[x].y][Skill[x].x+1] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[Skill[x].y][Skill[x].x+1] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[Skill[x].y][Skill[x].x+1];
			}

			Skill.erase(Skill.begin() + x);
		}
		else
		{
			if ( Skill[x].faceWhere == false )
			{
				gotoXY(Skill[x].x+1, Skill[x].y);
				std::cout<< map[Skill[x].y][Skill[x].x+1];
				gotoXY(Skill[x].x, Skill[x].y);
				colour(0x04);
				std::cout<<(char)15;
				colour(0x0F);
				/*if (Skill[x].Range <= 5) //Melee Attack
		    {
		       Skill[]
		
		    }*/
			}
			else if ( Skill[x].faceWhere == true )
			{
				gotoXY(Skill[x].x-1, Skill[x].y);
				std::cout<< map[Skill[x].y][Skill[x].x-1];
				gotoXY(Skill[x].x, Skill[x].y);
				colour(0x04);
				std::cout<<(char)15;
				colour(0x0F);

			}
		}
	}
}