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
	AddFire.skillUnlocked = true;
	AddFire.orbASCII = (char)15;

	//Initialize LightningOrb Skill
	AddSpark.Damage = 5 + AddSpark.dmgUpgrade;
	AddSpark.Range = 3 + AddSpark.rangeUpgrade;
	AddSpark.Speed = 0.5;
	AddSpark.index = 2;
	AddSpark.orbASCII = (char)177;

	//Initialize WaterOrb Skill
	AddWater.Damage = 1 + AddWater.dmgUpgrade;
	AddWater.Range = 100 + AddWater.rangeUpgrade;
	AddWater.Speed = 1.0;
	AddSpark.index = 3;
	AddWater.orbASCII = (char)247;

	//Initializes Player Equipped Skill to Fire
	AddCKey = AddFire;
}

void Attack()
{
	if ( playerFacing == 0 ) // if facing left
	{
		AddCKey.x = charLocation.X-1;
		AddCKey.y = charLocation.Y;
		AddCKey.faceWhere = false;
		AddCKey.isRENDERED = true;
	}
	else if ( playerFacing == 1 ) // if facing right
	{
		AddCKey.x = charLocation.X+1;
		AddCKey.y = charLocation.Y;
		AddCKey.faceWhere = true;
		AddCKey.isRENDERED = true;
	}
	CKey.push_back(AddCKey);
}

void nextSkill()
{
	if (AddCKey.index == 1 )
	{
		AddCKey = AddSpark;
	}
	else if (AddCKey.index == 2 )
	{
		AddCKey = AddWater;
	}
}

void previousSkill()
{
	if (AddCKey.index == 3 )
	{
		AddCKey = AddSpark;
	}
	else if (AddCKey.index == 2 )
	{
		AddCKey = AddFire;
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
		checkCollisionWithMonster(Skill);
		checkCollisionWithWall(Skill);
	}
}

void clearSkills()
{
	for(unsigned int x = 0; x < CKey.size(); ++x)
	{
		gotoXY(CKey[x].x-1, CKey[x].y);
			if ( map[CKey[x].y][CKey[x].x-1] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[CKey[x].y][CKey[x].x-1] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[CKey[x].y][CKey[x].x-1] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[CKey[x].y][CKey[x].x-1];
			}

			gotoXY(CKey[x].x, CKey[x].y);
			if ( map[CKey[x].y][CKey[x].x] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[CKey[x].y][CKey[x].x] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[CKey[x].y][CKey[x].x] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[CKey[x].y][CKey[x].x];
			}

			gotoXY(CKey[x].x+1, CKey[x].y);
			if ( map[CKey[x].y][CKey[x].x+1] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[CKey[x].y][CKey[x].x+1] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[CKey[x].y][CKey[x].x+1] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[CKey[x].y][CKey[x].x+1];
			}
	}
}

void spawnSkill(){
	for(unsigned int x = 0; x < CKey.size(); ++x)
	{
		if (CKey[x].isRENDERED == false)
		{
		gotoXY(CKey[x].x-1, CKey[x].y);
			if ( map[CKey[x].y][CKey[x].x-1] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[CKey[x].y][CKey[x].x-1] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[CKey[x].y][CKey[x].x-1] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[CKey[x].y][CKey[x].x-1];
			}

			gotoXY(CKey[x].x, CKey[x].y);
			if ( map[CKey[x].y][CKey[x].x] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[CKey[x].y][CKey[x].x] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[CKey[x].y][CKey[x].x] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[CKey[x].y][CKey[x].x];
			}

			gotoXY(CKey[x].x+1, CKey[x].y);
			if ( map[CKey[x].y][CKey[x].x+1] == '#' ) // if wall
			{
				std::cout << (char)219;
			}
			else if ( map[CKey[x].y][CKey[x].x+1] == 234 )
			{
				colour(0x0A);
				std::cout << (char)234;
				colour(0x0F);
			}
			else if ( map[CKey[x].y][CKey[x].x+1] == 239 )
			{
				colour(0x0A);
				std::cout << (char)239;
				colour(0x0F);
			}
			else
			{
				std::cout<< map[CKey[x].y][CKey[x].x+1];
			}
		CKey.erase(CKey.begin() + x);
		}
		else
		if ( CKey[x].faceWhere == false )
		{
			clearSkills();
			gotoXY(CKey[x].x, CKey[x].y);
			if (CKey[x].index == 1)
			{
				colour(0x04);
			}
			else if (CKey[x].index == 2)
			{
				colour(0x8);
			}
			else if (CKey[x].index == 3)
			{
				colour(0x03);
			}
			if (CKey[x].bulletTravelDistance == AddCKey.Range)
			{
				CKey.erase(CKey.begin() + x);
			}
			else if (CKey[x].isRENDERED == true)
			{
				std::cout<<CKey[x].orbASCII;
			}
			colour(0x0F);
		}
		else if ( CKey[x].faceWhere == true )
		{
			clearSkills();
			gotoXY(CKey[x].x, CKey[x].y);
			if (CKey[x].index == 1)
			{
				colour(0x04);
			}
			else if (CKey[x].index == 2)
			{
				colour(0x8);
			}
			else if (CKey[x].index == 3)
			{
				colour(0x03);
			}
			if (CKey[x].bulletTravelDistance == AddCKey.Range)
			{
				CKey.erase(CKey.begin() + x);
			}
			else if (CKey[x].isRENDERED == true)
			{
				std::cout<<CKey[x].orbASCII;
			}
			colour(0x0F);
		}
	}
}