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
extern std::vector<Monster> Villager;
extern std::vector<Monster> Shielded;
extern std::vector<Monster> PianusHitbox;
extern void checkMonsterDead();
extern bool FireUnlocked;
extern bool SparkUnlocked;
extern bool WaterUnlocked;
Skill_Properties AddSpark;
Skill_Properties AddFire;
Skill_Properties AddWater;
Skill_Properties AddCKey;
Skill_Properties AddFart;
std::vector<Skill_Properties> XKey;
std::vector<Skill_Properties> CKey;
bool cannotAttack = false;

void initSkill()
{
	//If you want to make a shop where you can upgrade the Skills. 
	//Then just AddFire.Damage = 2 + shopUpgrade; Add the shopUpgrade variable or whatever in.

	//Initialize FireOrb Skill
	AddFire.Damage = 2 + AddFire.dmgUpgrade;
	AddFire.Range = 10 + AddFire.rangeUpgrade;
	AddFire.Speed = 1.0;
	AddFire.index = 1;
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
	AddWater.Speed = 1.5;
	AddSpark.index = 3;
	AddWater.orbASCII = (char)247;

	//Init AddFart Skill
	AddFart.Damage = 0;
	AddFart.Range = 1;
	AddFart.Speed = 0; //AddFart's Cooldown is based on how long the Player holds X
	AddFart.index = 4;
	AddFart.orbASCII = 'O';

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
	if (AddCKey.index == 1)
	{
		playGameSound(S_FIREBALL);
	}

	if (AddCKey.index == 2)
	{
		playGameSound(S_SPARK);
	}

	if (AddCKey.index == 3)
	{
		playGameSound(S_WATER);
	}

	CKey.push_back(AddCKey);
}

void nextSkill()
{
	if (AddCKey.index == 1 && SparkUnlocked == true)
	{
		AddCKey = AddSpark;
		AddCKey.index = 2;
	}
	else if (AddCKey.index == 2 && WaterUnlocked == true)
	{
		AddCKey = AddWater;
		AddCKey.index = 3;
	}
}

void previousSkill()
{
	if (AddCKey.index == 3)
	{
		AddCKey = AddSpark;
		AddCKey.index = 2;
	}
	else if (AddCKey.index == 2)
	{
		AddCKey = AddFire;
		AddCKey.index = 1;
	}
}

void checkPlayerFront()
{
	if (playerFacing == 1 && map[charLocation.Y][charLocation.X+2] == '#' || map[charLocation.Y][charLocation.X+2] == 227 || map[charLocation.Y][charLocation.X+2] == 239 || map[charLocation.Y][charLocation.X+2] == 234 || map[charLocation.Y][charLocation.X+2] == 21 || map[charLocation.Y][charLocation.X+2] == 16 || map[charLocation.Y][charLocation.X+2] == 17 || map[charLocation.Y][charLocation.X+2] == 16 || map[charLocation.Y][charLocation.X+2] == 17  || map[charLocation.Y][charLocation.X+2] == 15)
	{
		cannotAttack = true;
	}
	else if (playerFacing == 0 && map[charLocation.Y][charLocation.X-2] == '#' || map[charLocation.Y][charLocation.X-2] == 227 || map[charLocation.Y][charLocation.X-2] == 239 || map[charLocation.Y][charLocation.X-2] == 234 || map[charLocation.Y][charLocation.X-2] == 21 || map[charLocation.Y][charLocation.X-2] == 16 || map[charLocation.Y][charLocation.X-2] == 17 || map[charLocation.Y][charLocation.X+2] == 16 || map[charLocation.Y][charLocation.X+2] == 17 || map[charLocation.Y][charLocation.X+2] == 15 )
	{
		cannotAttack = true;
	}
	else
		cannotAttack = false;
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

	for ( unsigned int i = 0; i < Floater.size(); i++) // for all floaters
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == Floater[i].x && Skill[j].y == Floater[i].y) // if skill touches mob
			{
				Floater[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
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
				Rat[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
				Skill.erase(Skill.begin() + j); // remove Skill
				checkMonsterDead();
				i = 0;
				j = 0;
			}
		}
	}

	for ( unsigned int i = 0; i < InnerFear.size(); i++) // for all innerfears
	{
		for ( unsigned int j = 0; j < Skill.size(); j++)
		{
			if (Skill[j].x == InnerFear[i].x && Skill[j].y == InnerFear[i].y) // if skill touches mob
			{
				InnerFear[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
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
				Wengyew[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
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
				CatFish[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
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
				DeadFish[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
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
				LiveFish[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
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
				Shielded[i].health -= Skill[j].Damage; // health from mob is deducted by skill damage
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
		if (Skill[i].faceWhere == true)//Skill Moving RIght
		{
			if ( map[Skill[i].y][Skill[i].x+1] == '#' || map[Skill[i].y][Skill[i].x+1] == 227 || map[Skill[i].y][Skill[i].x+1] == 239 || map[Skill[i].y][Skill[i].x+1] == 234 || map[Skill[i].y][Skill[i].x+1] == 21 || map[Skill[i].y][Skill[i].x+1] == 16 || map[Skill[i].y][Skill[i].x+1] == 17 || map[Skill[i].y][Skill[i].x+1] == 15) 
			{
				Skill[i].isRENDERED = false;
			}

		}
		else if (Skill[i].faceWhere == false)//Skill Moving Left
		{
			if ( map[Skill[i].y][Skill[i].x-1] == '#' || map[Skill[i].y][Skill[i].x-1] == 227 || map[Skill[i].y][Skill[i].x-1] == 239 || map[Skill[i].y][Skill[i].x-1] == 234 || map[Skill[i].y][Skill[i].x-1] == 21 || map[Skill[i].y][Skill[i].x-1] == 16 || map[Skill[i].y][Skill[i].x-1] == 17 || map[Skill[i].y][Skill[i].x-1] == 15) 
			{
				Skill[i].isRENDERED = false;
			}
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

void spawnSkill(std::vector<Skill_Properties>& Skill)
{
	for (unsigned int x = 0; x< Skill.size(); ++x)
	{
		if (Skill[x].isRENDERED == false)
		{
			if (Skill[x].faceWhere == true)
			{
				gotoXY(Skill[x].x-1,Skill[x].y);
				std::cout<<map[Skill[x].y][Skill[x].x];
			}
			else if (Skill[x].faceWhere == false)
			{
				gotoXY(Skill[x].x+1,Skill[x].y);
				std::cout<<map[Skill[x].y][Skill[x].x];
			}
			Skill.erase(Skill.begin() + x);
		}
		else
		{
			if (Skill[x].faceWhere == false )
			{
				for ( unsigned int y = 0; y< Skill.size(); ++y)//Clears Shot
				{
					gotoXY(Skill[y].x+1, Skill[y].y);
					std::cout<<map[Skill[y].y][Skill[y].x+1];
				}
				gotoXY(Skill[x].x, Skill[x].y);
				if (Skill[x].index == 1)
				{
					colour(0x04);
				}
				else if (Skill[x].index == 2)
				{
					colour(0x8);
				}
				else if (Skill[x].index == 3)
				{
					colour(0x03);
				}
				else if (Skill[x].index == 4)
				{
					colour(0x02);
				}
				if (Skill[x].bulletTravelDistance == Skill[x].Range)
				{
					Skill.erase(Skill.begin() + x);
				}
				else if (Skill[x].isRENDERED == true)
				{
					std::cout<<Skill[x].orbASCII;
				}
				colour(0x0F);

			}
			else if (Skill[x].faceWhere == true )
			{
				for ( unsigned int y = 0; y< Skill.size(); ++y)//Clears Shot
				{
					gotoXY(Skill[y].x-1, Skill[y].y);
					std::cout<<map[Skill[y].y][Skill[y].x-1];
				}
				gotoXY(Skill[x].x, Skill[x].y);//Prints Shot
				if (Skill[x].index == 1)
				{
					colour(0x04);
				}
				else if (Skill[x].index == 2)
				{
					colour(0x8);
				}
				else if (Skill[x].index == 3)
				{
					colour(0x03);
				}
				else if (Skill[x].index == 4)
				{
					colour(0x02);
				}
				if (Skill[x].bulletTravelDistance == Skill[x].Range)
				{
					Skill.erase(Skill.begin() + x);
				}
				else if (Skill[x].isRENDERED == true)
				{
					std::cout<<Skill[x].orbASCII;
				}
				colour(0x0F);
			}
		}
		for ( unsigned int y = 0; y< Skill.size(); ++y)
		{
			if ( map[Skill[y].y][Skill[y].x-1] == ' ')
			{
				gotoXY(Skill[y].x-1, Skill[y].y);
				std::cout<<map[Skill[y].y][Skill[y].x-1];
			}
		}
	}
}

void UltAttack()
{
	playGameSound(S_FART); //POOP
	AddFart.Speed = (double)AddFart.dmgUpgrade;
	if ( playerFacing == 0 ) // if facing left
	{
		AddFart.x = charLocation.X-1;
		AddFart.y = charLocation.Y;
		AddFart.faceWhere = false;
		AddFart.isRENDERED = true;
	}
	else if ( playerFacing == 1 ) // if facing right
	{
		AddFart.x = charLocation.X+1;
		AddFart.y = charLocation.Y;
		AddFart.faceWhere = true;
		AddFart.isRENDERED = true;
	}
	XKey.push_back(AddFart);
}