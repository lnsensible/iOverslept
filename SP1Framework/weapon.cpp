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
extern std::vector<Monster> LiveFish;
extern std::vector<Monster> PianusHitbox;
extern void checkMonsterDead();
Skill_Properties AddSpark;
Skill_Properties AddFire;
Skill_Properties AddWater;
Skill_Properties AddCKey;
std::vector<Skill_Properties> FireOrb;
std::vector<Skill_Properties> LightningOrb;
std::vector<Skill_Properties> WaterOrb;
std::vector<Skill_Properties> CKey;

void initSkill()
{
	//If you want to make a shop where you can upgrade the Skills. 
	//Then just AddFire.Damage = 2 + shopUpgrade; Add the shopUpgrade variable or whatever in.

	//Initialize FireOrb Skill
	AddFire.Damage = 2 + AddFire.dmgUpgrade;
	AddFire.Range = 10 + AddFire.rangeUpgrade;
	AddFire.Speed = 1.0;
	AddFire.index = 1;
	FireOrb.push_back(AddFire);

	//Initialize LightningOrb Skill
	AddSpark.Damage = 5 + AddSpark.dmgUpgrade;
	AddSpark.Range = 3 + AddSpark.rangeUpgrade;
	AddSpark.Speed = 0.5;
	AddSpark.index = 2;
	LightningOrb.push_back(AddSpark);

	//Initialize WaterOrb Skill
	AddWater.Damage = 100 + AddWater.dmgUpgrade;
	AddWater.Range = 100 + AddWater.rangeUpgrade;
	AddWater.Speed = 1.0;
	AddWater.index = 3;
	WaterOrb.push_back(AddWater);

	//Initializes Player Equipped Skill to Fire
	AddCKey = AddFire;
	CKey.push_back(AddCKey);
}

void nextSkill()
{
		if (AddCKey.index == 1)
		{
			AddCKey = AddSpark;
			CKey.push_back(AddCKey);
		}
		else if (AddCKey.index == 2)
		{
			AddCKey = AddWater;
			CKey.push_back(AddCKey);
		}
}

void previousSkill()
{
	if (AddCKey.index == 3)
	{
			AddCKey = AddSpark;
			CKey.push_back(AddCKey);
	}
	else if (AddCKey.index == 2)
	{
			AddCKey = AddFire;
			CKey.push_back(AddCKey);
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
				MonsterSnail[i].health -= AddCKey.Damage;
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
				Floater[i].health -= AddCKey.Damage;
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
				Rat[i].health -= AddCKey.Damage;
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
				InnerFear[i].health -= AddCKey.Damage;
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
				Wengyew[i].health -= AddCKey.Damage;
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
				CatFish[i].health -= AddCKey.Damage;
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
				DeadFish[i].health -= AddCKey.Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < LiveFish.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == LiveFish[i].x && Skill[j].y == LiveFish[i].y)
			{
				LiveFish[i].health -= AddCKey.Damage;
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
		Skill_Properties addSkill;
		addSkill.x = charLocation.X-1;
		addSkill.y = charLocation.Y;
		addSkill.faceWhere = false;
		addSkill.isRENDERED = true;
		Skill.push_back(addSkill);
	}
	else if ( playerFacing == 1 ) // if facing right
	{
		Skill_Properties addSkill;
		addSkill.x = charLocation.X+1;
		addSkill.y = charLocation.Y;
		addSkill.faceWhere = true;
		addSkill.isRENDERED = true;
		Skill.push_back(addSkill);
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
		Skill[h].bulletTravelDistance +=1;
		if (Skill[h].bulletTravelDistance == AddCKey.Range)
		{
			Skill.erase(Skill.begin() + h);
		}
		checkCollisionWithMonster(CKey);
		checkCollisionWithWall(CKey);
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