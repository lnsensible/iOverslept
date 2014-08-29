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
<<<<<<< b902f142b4abfa35c3840e2d8b81af32b7f16158
extern std::vector<Monster> Villager;
=======
extern std::vector<Monster> Shielded;
extern std::vector<Monster> PianusHitbox;
>>>>>>> cf3d4221aa0744640efa4a3753dca785f21ae1d3
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
		AddCKey.index = 2;
	}
	else if (AddCKey.index == 2 )
	{
		AddCKey = AddWater;
		AddCKey.index = 3;
	}
}

void previousSkill()
{
	if (AddCKey.index == 3 )
	{
		AddCKey = AddSpark;
		AddCKey.index = 2;
	}
	else if (AddCKey.index == 2 )
	{
		AddCKey = AddFire;
		AddCKey.index = 1;
	}
}

void checkCollisionWithMonster(std::vector<Skill_Properties>& Skill)
{
	for ( unsigned int i = 0; i < MonsterSnail.size(); i++) // for all snails
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == MonsterSnail[i].x && Skill[j].y == MonsterSnail[i].y) // if skill touches mob
			{
				MonsterSnail[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

<<<<<<< b902f142b4abfa35c3840e2d8b81af32b7f16158
	for ( unsigned int i = 0; i < Villager.size(); i++)
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Villager[i].x && Skill[j].y == Villager[i].y)
			{
				Villager[i].health -= Skill[j].Damage;
				Skill.erase(Skill.begin() + j); // remove Skill
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < Floater.size(); i++)
=======
	for ( unsigned int i = 0; i < Floater.size(); i++) // for all floaters
>>>>>>> cf3d4221aa0744640efa4a3753dca785f21ae1d3
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Floater[i].x && Skill[j].y == Floater[i].y) // if skill touches mob
			{
				Floater[i].health -= AddCKey.Damage; // health from mob is deducted by skill damage
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < Rat.size(); i++) // for all rats
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Rat[i].x && Skill[j].y == Rat[i].y) // if skill touches mob
			{
				Rat[i].health -= AddCKey.Damage; // health from mob is deducted by skill damage
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


	for ( unsigned int i = 0; i < InnerFear.size(); i++) // for all innerfears
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == InnerFear[i].x && Skill[j].y == InnerFear[i].y) // if skill touches mob
			{
				InnerFear[i].health -= AddCKey.Damage; // health from mob is deducted by skill damage
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < Wengyew.size(); i++) // for all wengyews
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Wengyew[i].x && Skill[j].y == Wengyew[i].y) // if skill touches mob
			{
				Wengyew[i].health -= AddCKey.Damage; // health from mob is deducted by skill damage
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < CatFish.size(); i++) // for all catfishes
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == CatFish[i].x && Skill[j].y == CatFish[i].y) // if skill touches mob
			{
				CatFish[i].health -= AddCKey.Damage; // health from mob is deducted by skill damage
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < DeadFish.size(); i++) // for all deadfishes
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == DeadFish[i].x && Skill[j].y == DeadFish[i].y) // if skill touches mob
			{
				DeadFish[i].health -= AddCKey.Damage; // health from mob is deducted by skill damage
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < LiveFish.size(); i++) // for all livefishes
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == LiveFish[i].x && Skill[j].y == LiveFish[i].y) // if skill touches mob
			{
				LiveFish[i].health -= AddCKey.Damage; // health from mob is deducted by skill damage
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < Shielded.size(); i++) // for all Shieldeds
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Shielded[i].x && Skill[j].y == Shielded[i].y) // if skill touches mob
			{
				Shielded[i].health -= AddCKey.Damage; // health from mob is deducted by skill damage
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

void spawnSkill(){
	for(unsigned int x = 0; x < CKey.size(); ++x)
	{
		if (CKey[x].isRENDERED == false)//If hit something other than monster, then rendered = false and this happens.
		{
			gotoXY(CKey[x].x-1, CKey[x].y);
			if ( map[CKey[x].y][CKey[x].x-1] == '#' ) 
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
				for ( unsigned int y = 0; y< CKey.size(); ++y)
				{
					gotoXY(CKey[y].x+1, CKey[y].y);
					std::cout<<" ";
				}
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
				for ( unsigned int y = 0; y< CKey.size(); ++y)
				{
					if (map[CKey[y].y][CKey[y].x+1] != '#' || map[CKey[y].y][CKey[y].x-1] != '.')
					{
						gotoXY(CKey[y].x+1, CKey[y].y);
						std::cout<<map[CKey[y].y][CKey[y].x+1];
					}
				}
			}
			else if ( CKey[x].faceWhere == true )
			{
				for ( unsigned int y = 0; y< CKey.size(); ++y)
				{
					gotoXY(CKey[y].x-1, CKey[y].y);
					std::cout<<" ";
				}
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
				for ( unsigned int y = 0; y< CKey.size(); ++y)
				{
					if (map[CKey[y].y][CKey[y].x-1] != '#' || map[CKey[y].y][CKey[y].x-1] != '.')
					{
						gotoXY(CKey[y].x-1, CKey[y].y);
						std::cout<<map[CKey[y].y][CKey[y].x-1];
					}
				}
			}
	}
	AddCKey.isRENDERED = false;
}