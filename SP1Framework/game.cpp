// This is the main file for the game logic and functions
// YAY :D
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

extern std::vector<bossAttack> meteor;
extern std::vector<bossAttack> splint;
extern std::vector<bossAttack> laser;
extern std::vector<bossAttack> lava;
extern std::vector<bossAttack> BossHitbox;
extern std::vector<Monster> PianusHitbox;
extern char bossHPbar;
extern char pianusHPbar;
extern const int bossHP;
extern int bosscurrentHP;
extern int pianuscurrentHP;
extern int RemovePianusHitbox;

extern double hitboxDelay;
extern double bossDifficulty;

extern std::vector<Monster> MonsterSnail;
extern std::vector<Monster> Floater;
extern std::vector<Monster> InnerFear;
extern std::vector<Monster> Rat;
extern std::vector<Monster> Wengyew;
extern std::vector<Monster> CatFish;
extern std::vector<Monster> DeadFish;
extern std::vector<Monster> LiveFish;
extern std::vector<Monster> Villager;

extern std::vector<Skill_Properties> CKey;
extern std::vector<Skill_Properties> EKey;

extern int hasbeenStabbed;
extern int weaponDAMAGE;       
extern int weaponSPEED;         
extern int weaponHITCOUNT;   
extern std::string beforeATTACK,afterATTACK;
extern std::string weaponHITBOX; 
extern std::string weaponSTATE;  

std::string leveltoload;
std::string signtoload;

extern double jumpDelay;
extern double fallDelay;
extern double canJump;

double elapsedTime;
double deltaTime;
bool keyPressed[K_COUNT];
int gamestate = 0;
COORD charLocation;
COORD consoleSize;

int NUMBEROFSIGNS = 43;

unsigned char map[MAPHEIGHT][MAPWIDTH]; // stores the level map
unsigned char Signprint[SIGNHEIGHT][SIGNWIDTH]; // stores the sign
unsigned int Savedata[DATAHEIGHT][DATAWIDTH]; //stores values of savedata
unsigned int outputData[DATAHEIGHT][DATAWIDTH]; //stores values to save to the save file
int checkLevel = 0; // Check current level
int checkPrevLevel = 0; // Check previous level
int hasLevelRendered = 0; // Check if level has been rendered. 0 = Not loaded, 1 = Loaded
int signNumber = 0;
int isBossLevel = 0; //Check if it is a boss level. 0 = No, 1 = Boss, 2 = Fishy
int isonSign = 0;//rerender sign
int hasStoryRendered = 0; // check if story has been render. 0 = nope, 1 = yep.
int hasMoved = 0; // check if player moved.
int playerFacing = 0; // 0 = left, 1 = right
int MoneyCount; //The amount of money you have
int MoneyInv; //The money you collected in current level
int NewGame = 1; //If first time play

int Snailcounter = 0; // count number of snails
int Floatercounter = 0; // count number of floaters
int InnerFearcounter = 0; // count number of InnerFears
int Ratcounter = 0; // count number of rats
int Wengyewcounter = 0; // count number of wengyews
int CatFishcounter = 0; // count number of CatFishes
int DeadFishcounter = 0; // count number of DeadFishes
int LiveFishcounter = 0; // count number of LiveFishes
int Villagercounter = 0; // count number of Villagers

double snailMoveDelay = 0; // delay between each snail movement :D
double floaterMoveDelay = 0; // delay between each floater movement
double InnerFearMoveDelay = 0; // delay between each InnerFear movement
double RatMoveDelay = 0; // delay between each Rat movement
double WengyewMoveDelay = 0; // delay between each wy movement
double CatFishMoveDelay = 0; // delay between each CatFish movement
double DeadFishMoveDelay = 0; // delay between each DeadFish movement
double LiveFishMoveDelay = 0; // delay between each LiveFish movement
double VillagerMoveDelay = 0; // delay between each Villager movement
double PlayerSkillDelay = 0; //delay between skills

int PlayerHealth = 3; // Player's HP. Default = 3.

//Weapons
extern void Attack(std::vector<Skill_Properties>& Skill);
extern void updateSkill(std::vector<Skill_Properties>& Skill);
extern void spawnSkill(std::vector<Skill_Properties>& Skill);
extern void initSkill();
extern void nextSkill();
extern void previousSkill();
extern Skill_Properties AddCKey;
extern Skill_Properties AddFire;
extern Skill_Properties AddSpark;
extern Skill_Properties AddWater;


std::string StoryPage1[7] = {"Quen has been addicted to the game Maplestory since recently when his friend introduced it to him.",
							 "Trying to surpass his friend, he would sacrifice his sleep and play throughout the night, sleeping",
						     "for less than 2 hours everyday. Being sleep deprived, he would doze off during lessons, usually   ",
						     "getting him into trouble. However, this didn't stop him from playing. Eventually, Quen decided to ",
						     "stay awake throughout the night, and catch some sleep during school. But this sleep wasn't enough,",
					         "and one night, he was so tired that his brain forced him to fall asleep. But he was still thinking",
						     "of Maplestory, and so he started dreaming...."};

std::string StoryPage2[4] = {"Quen was mentally awake when he entered his dream. He recognised his surroundings to be that of   ",
							 "Maplestory's. He figured that his wish to be able to play Maplestory forever has been granted, and",
							 "he's now living within the Maple World. Quen makes up his mind to become stronger in order to",
							 "explore the world. But first, he must learn how to move around in this world..."};

std::string StoryPage3[5] = {"Quen notices something moving further ahead. Upon moving closer, he sees that its a snail. Its    ",
							 "just like when he was just starting out in Maplestory. Now that he wasn't just using a keyboard    ",
							 "to control his character on a screen, he wondered if he could fight in this world too.            ",
							 "",
							 "And so, his journey continues..."};

void initmainmenu()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"Main Menu");

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	charLocation.X = 55;
	charLocation.Y = 20;
}
void updatemainmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_UP])
	{
		if (charLocation.Y == 20 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 20;
		}

		else if (charLocation.Y == 22)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 20;
		}

		else if (charLocation.Y == 24)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 22;
		}
	}

	if(keyPressed[K_DOWN])
	{
		if (charLocation.Y == 20 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 22;
		}

		else if (charLocation.Y == 22)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 24;
		}

		else if (charLocation.Y == 24)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y = 24;
		}
	}


	if(keyPressed[K_ENTER])
	{
		if(charLocation.Y == 20)
		{
			gamestate = LEVELMENU;
		}

		if(charLocation.Y == 22)
		{
			gamestate = SHOP;
		}

		if(charLocation.Y == 24)
		{
			g_quitGame = true;
		}
	}
	
	if(keyPressed[K_ESCAPE])
	{
		g_quitGame = true;
	}
}
void rendermainmenu()
{
	std::string linemenuthing;
	for(int i = 0; i < 20; i++)
	{
		linemenuthing += (char)196;
	}
	gotoXY(48, 18);
	std::cout << (char)218 << linemenuthing << (char)191;
	gotoXY(57, 20);
	std::cout << "Play!";
	gotoXY(57, 22);
	std::cout << "Shop";
	gotoXY(57, 24);
	std::cout << "Quit";

	gotoXY(charLocation);
	colour(0x0C);
	std::cout << (char)16;
	colour(0x0F);
}

void initlevelmenu()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"Level Menu");

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	charLocation.X = 46; //default cursor position
	charLocation.Y = 15;
}
void updatelevelmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_DOWN])
	{
		if(charLocation.Y != 17)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y += 2;
		}
	}

	if(keyPressed[K_UP])
	{
		if(charLocation.Y != 15)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y -= 2;
		}
	}

	if(keyPressed[K_ENTER])
	{
		if(charLocation.Y == 15)
		{
			hasLevelRendered = 0;
			loadGame();
			if(NewGame == 0)
			{
				loadGameUpdate();
			}

			else
			{
				AddSpark.skillUnlocked = false;
				AddWater.skillUnlocked = false;
				AddFire.skillUnlocked = true;
				checkLevel = 1;

			}

			gamestate = GAME;
		}

		else if(charLocation.Y == 17)
		{
			saveGame();
		}
	}//keypress enter

	if(keyPressed[K_ESCAPE])
	{
		gamestate = MENU;
	}
}
void renderlevelmenu()
{
	colour(0x0F);

	gotoXY(48, 15);
	std::cout << "Continue / New game";
	gotoXY(53, 17);
	std::cout << "Save game";

	gotoXY(charLocation);
	colour(0x0C);
	std::cout << (char)94;
	colour(0x0F);
}

void initdeathmenu()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"Death Menu");

	resetElements();

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	charLocation.X = 50;
	charLocation.Y = 22;
}
void updatedeathmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_LEFT])
	{
		if (charLocation.X == 60 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 50;
		}

		else if(charLocation.X == 50)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 50;
		}
	}

	if(keyPressed[K_RIGHT])
	{
		if (charLocation.X == 60 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 60;
		}

		else if(charLocation.X == 50)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 60;
		}
	}

	if(keyPressed[K_ENTER])
	{
		PlayerHealth = 3;
		if(charLocation.X == 60)
		{
			gamestate = LEVELMENU;
		}

		if(charLocation.X == 50)
		{
			gamestate = GAME;
		}
	}

	if(keyPressed[K_ESCAPE])
	{
		gamestate = LEVELMENU;
	}
}
void renderdeathmenu()
{
	colour(0x0F);

	gotoXY(55, 20);
	colour(0x0C);
	std::cout << "YOU DIED :C";
	gotoXY(52, 22);
	colour(0x0F);
	std::cout << "Respawn";
	gotoXY(62, 22);
	std::cout << "SCREW IT I'M OUTTA HERE";

	colour(0x0C);
	gotoXY(charLocation);
	std::cout << (char)16;
	colour(0x0F);
}

void initendmenu()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"You Win!");

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	

	charLocation.X = 47;
	charLocation.Y = 22;
}
void updateendmenu(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_LEFT])
	{
		if (charLocation.X == 63 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 47;
		}

		else if(charLocation.X == 47)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 47;
		}
	}

	if(keyPressed[K_RIGHT])
	{
		if (charLocation.X == 63 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 63;
		}

		else if(charLocation.X == 47)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 63;
		}
	}

	if(keyPressed[K_ENTER])
	{
		if(charLocation.X == 63)
		{
			if(checkLevel != NUMBEROFLEVELS)
			{
				checkLevel++;
			}
			gamestate = GAME;
		}

		if(charLocation.X == 47)
		{
			gamestate = LEVELMENU;
		}
	}
}
void renderendmenu()
{
	colour(0x0F);

	gotoXY(45, 20);
	colour(0x0A);
	std::cout << "Level completed, Congratulations!";
	gotoXY(49, 22);
	colour(0x0F);
	std::cout << "Return menu";
	gotoXY(65, 22);
	std::cout << "Next level";

	colour(0x0C);
	gotoXY(charLocation);
	std::cout << (char)16;
	colour(0x0F);
}

void initSHOP()
{
	// Set precision for floating point output
	std::cout << std::fixed << std::setprecision(3);

	SetConsoleTitle(L"SHOP");

	// Get console width and height
	CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

	/* get the number of character cells in the current buffer */ 
	GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
	consoleSize.X = csbi.srWindow.Right + 1;
	consoleSize.Y = csbi.srWindow.Bottom + 1;

	

	charLocation.X = 59;
	charLocation.Y = 10;
}
void updateSHOP(double dt)
{
	elapsedTime += dt;
	deltaTime = dt;

	if(keyPressed[K_LEFT])
	{
		if (charLocation.X == 59 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 39;
		}

		else if(charLocation.X == 39)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 39;
		}
	}

	if(keyPressed[K_RIGHT])
	{
		if (charLocation.X == 59 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 59;
		}

		else if(charLocation.X == 39)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.X = 59;
		}
	}

	if(keyPressed[K_UP])
	{
		if (charLocation.Y != 10 )
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y -= 2;
		}
	}

	if(keyPressed[K_DOWN])
	{
		if(charLocation.Y != 20)
		{
			gotoXY(charLocation);
			std::cout << " ";
			charLocation.Y += 2;
		}
	}

	if(keyPressed[K_ENTER])
	{
		if(charLocation.Y == 10)
		{
			if(charLocation.X == 39)
			{
				if(MoneyCount >= 50)
				{
					MoneyCount = MoneyCount = 50;
					AddFire.dmgUpgrade = AddFire.dmgUpgrade + 1;
					gotoXY(54, 5);
					std::cout << "Upgrade successful!";
					gotoXY(20, 10);
					std::cout << "Damage: ";
					std::cout << AddFire.Damage;
				}
				else
				{
					gotoXY(54, 5);
					std::cout << "Not enough Money!      ";
				}
			}
			else
			{
				if(AddFire.skillUnlocked == true)
				{
					gotoXY(54, 5);
					std::cout << "Already owned!         ";
				}
				else
				{
					if(MoneyCount >= 20)
					{
						gotoXY(54, 5);
						MoneyCount = MoneyCount - 20;
						AddFire.skillUnlocked = true;
						std::cout << "Purchase succesful";
					}
				}
			}
		}

		if(charLocation.Y == 12)
		{
			if(charLocation.X == 39)
			{
				if(MoneyCount >= 50)
				{
					MoneyCount = MoneyCount = 50;
					AddFire.rangeUpgrade = AddFire.rangeUpgrade + 1;
					gotoXY(54, 5);
					std::cout << "Upgrade successful!";
					gotoXY(20, 12);
					std::cout << "Range: ";
					std::cout << AddFire.Range;
				}
				else
				{
					gotoXY(54, 5);
					std::cout << "Not enough Money!      ";
				}
			}
		}

		if(charLocation.Y == 14)
		{
			if(charLocation.X == 39)
			{
				if(MoneyCount >= 100)
				{
					MoneyCount = MoneyCount = 100;
					AddSpark.dmgUpgrade = AddSpark.dmgUpgrade + 1;
					gotoXY(54, 5);
					std::cout << "Upgrade successful!";
					gotoXY(20, 14);
					std::cout << "Damage: ";
					std::cout << AddSpark.Damage;
				}
				else
				{
					gotoXY(54, 5);
					std::cout << "Not enough Money!      ";
				}
			}
			else
			{
				if(AddSpark.skillUnlocked == true)
				{
					gotoXY(54, 5);
					std::cout << "Already owned!         ";
				}
				else
				{
					if(MoneyCount >= 300)
					{
						gotoXY(54, 5);
						MoneyCount = MoneyCount - 300;
						AddSpark.skillUnlocked = true;
						std::cout << "Purchase succesful";
					}
				}
			}
		}

		if(charLocation.Y == 16)
		{
			if(charLocation.X == 39)
			{
				if(MoneyCount >= 50)
				{
					MoneyCount = MoneyCount = 50;
					AddFire.rangeUpgrade = AddFire.rangeUpgrade + 1;
					gotoXY(54, 5);
					std::cout << "Upgrade successful!";
					gotoXY(20, 16);
					std::cout << "Range: ";
					std::cout << AddSpark.Range;
				}
				else
				{
					gotoXY(54, 5);
					std::cout << "Not enough Money!      ";
				}
			}
		}
	}
	if(keyPressed[K_ESCAPE])
	{
		gamestate = GAME;
	}
}
void renderSHOP()
{
	colour(0x0F);

	gotoXY(56, 2);
	colour(0x0A);
	std::cout << "SHOP";

	gotoXY(1, 3);
	std::cout << (char)201;
	for(int i = 0; i < 116; i++)
	{
		std::cout << (char)205;
	}
	std::cout << (char)187;

	colour(0x0F);
	if(AddFire.skillUnlocked == true)
	{
		gotoXY(60, 10);
		std::cout << "Owned!";
	}

	else
	{
		gotoXY(60, 10);
		std::cout << "Buy $20";
	}
	gotoXY(10, 10);
	std::cout << "Fire";
	gotoXY(20, 10);
	std::cout << "Damage: ";
	std::cout << AddFire.Damage;
	gotoXY(20, 12);
	std::cout << "Range: ";
	std::cout << AddFire.Range;
	gotoXY(40, 10);
	std::cout << "Upgrade Damage";
	gotoXY(40, 12);
	std::cout << "Upgrade Range";

	colour(0x0F);
	if(AddSpark.skillUnlocked == true)
	{
		gotoXY(60, 14);
		std::cout << "Owned!";
	}

	else
	{
		gotoXY(60, 14);
		std::cout << "Buy $300";
	}
	gotoXY(10, 14);
	std::cout << "Sparks";
	gotoXY(20, 14);
	std::cout << "Damage: ";
	std::cout << AddSpark.Damage;
	gotoXY(20, 16);
	std::cout << "Range: ";
	std::cout << AddSpark.Range;
	gotoXY(40, 14);
	std::cout << "Upgrade Damage";
	gotoXY(40, 16);
	std::cout << "Upgrade Range";

	colour(0x0F);
	if(AddWater.skillUnlocked == true)
	{
		gotoXY(60, 18);
		std::cout << "Owned!";
	}

	else
	{
		gotoXY(60, 18);
		std::cout << "Buy $222";
	}
	gotoXY(10, 18);
	std::cout << "Water";
	gotoXY(20, 18);
	std::cout << "Damage: ";
	std::cout << AddWater.Damage;
	gotoXY(20, 20);
	std::cout << "Range: ";
	std::cout << AddWater.Range;
	gotoXY(40, 18);
	std::cout << "Upgrade Damage";
	gotoXY(40, 20);
	std::cout << "Upgrade Range";

	colour(0x0F);
	gotoXY(110, 34);
	std::cout << "Exit";

	colour(0x0C);
	gotoXY(charLocation);
	std::cout << (char)16;
	colour(0x0F);
}

bool fileExists(std::string fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}
void loadGame() // loads game from file.
{
	std::fstream Savefile;
	Savefile.open("playersave.txt");

	int tf = fileExists("playersave.txt");

	if(tf == true)
	{
		for (int i = 0; i < DATAHEIGHT; i++)
		{
			for (int j = 0; j < DATAWIDTH; j++)
			{
				Savefile >> Savedata[i][j];
			}
		}
		NewGame = 0;
	}
	else
	{
		NewGame = 1;
		createSave();
	}

	Savefile.close();
}
void loadGameUpdate()
{
	MoneyCount = Savedata[0][0];
	PlayerHealth = Savedata[0][1];
	checkLevel = Savedata[0][2];	
	AddSpark.skillUnlocked = Savedata[0][3];
	AddWater.skillUnlocked = Savedata[0][4];
	AddFire.skillUnlocked = Savedata[0][5];

	AddSpark.dmgUpgrade = Savedata[1][3];
	AddSpark.rangeUpgrade = Savedata[2][3];
	AddWater.dmgUpgrade = Savedata[1][4];
	AddWater.rangeUpgrade = Savedata[2][4];
	AddFire.dmgUpgrade = Savedata[1][5];
	AddFire.rangeUpgrade = Savedata[2][5];
}
void createSave()
{
	std::fstream filecreate;
	filecreate.open("playersave.txt",std::fstream::out);
	filecreate.close();
	saveGame();
}
void saveGame()
{
	std::fstream Savefile;
	Savefile.open("playersave.txt");

	int tf = fileExists("playersave.txt");

	if(tf == true)
	{
		outputData[0][0] = MoneyCount;
		if(PlayerHealth != 0)
		{
			outputData[0][1] = PlayerHealth;
		}
		else
		{
			outputData[0][1] = 3;
		}
		if(checkLevel!=0)
		{
			outputData[0][2] = checkLevel;
		}

		else
		{
			outputData[0][2] = 1;
		}

		if(AddSpark.skillUnlocked == true)
		{
			outputData[0][3] = 1;
			outputData[1][3] = AddSpark.dmgUpgrade;
			outputData[2][3] = AddSpark.rangeUpgrade;
		}

		else
		{
			outputData[0][3] = 0;
		}


		if(AddWater.skillUnlocked == true)
		{
			outputData[0][4] = 1;
			outputData[1][4] = AddWater.dmgUpgrade;
			outputData[2][4] = AddWater.rangeUpgrade;
		}

		else
		{
			outputData[0][4] = 0;
		}

		if(AddFire.skillUnlocked == true)
		{
			outputData[0][5] = 1;
			outputData[1][5] = AddFire.dmgUpgrade;
			outputData[2][5] = AddFire.rangeUpgrade;
		}

		else
		{
			outputData[0][5] = 0;
		}

		for (int i = 0; i < DATAHEIGHT; i++)
		{
			for (int j = 0; j < DATAWIDTH; j++)
			{
				Savefile << outputData[i][j];
				Savefile << " ";
			}
		}
	}
	else
	{
		createSave();
	}

	Savefile.close();
}

void loadLevel(std::string filename) // loads level map from file.
{
	std::fstream LevelMap;
	LevelMap.open(filename);

	for (int i = 0; i < MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAPWIDTH; j++)
		{
			LevelMap >> map[i][j];
		}
	}

	LevelMap.close();
} 

void loadSign(std::string filename) // loads sign from file.
{
	std::fstream Signload;
	Signload.open(filename);


	for (int i = 0; i < SIGNHEIGHT; i++)
	{
		for (int j = 0; j < SIGNWIDTH; j++)
		{
			Signload >> Signprint[i][j];
		}
	}

	Signload.close();
} 
void updateSigns()
{
	if (map[charLocation.Y][charLocation.X] == 209)//sign
	{
		isonSign = 1;
		for(int i = 0; i < NUMBEROFSIGNS + 1; i++)
		{
			signtoload = "sign";

			if (signNumber == i)
			{
				std::string s = std::to_string(static_cast<unsigned long long>(i));
				signtoload += s;
			}
			signtoload += ".txt";
			loadSign(signtoload);
		}

	}
}
void renderSigns()
{
	if ( isonSign == 1 )
	{
		for( int i = 0; i < SIGNHEIGHT; i++ )
		{
			for( int j = 0; j < SIGNWIDTH; j++ )
			{
				gotoXY(j+80, i+26);
				if ( Signprint[i][j] == '`')
				{
					Signprint[i][j] = ' ';// replace \ with space
				}
					std::cout << Signprint[i][j];
			}
		}
		isonSign = 2;
	}
	else if ( isonSign == 2 )
	{
		for( int i = 0; i < SIGNHEIGHT; i++ )
		{
			for( int j = 0; j < SIGNWIDTH; j++ )
			{
				gotoXY(j+80, i+26);
				std::cout << ' ';
			}
		}
		isonSign = 0;
	}
}

void prepareLevel() // Prepares level map for cout.
{
	resetElements();
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAPWIDTH; j++)
		{
			if ( map[i][j] == '.' ) // Whitespace placeholder
			{
				map[i][j] = ' ';
			}

			spawnWhere(); //determine where character will spawn

			if ( map[i][j] == 'x' ) // Floor trap placeholder
			{
				map[i][j] = 30;
			}
			if ( map[i][j] == 'X' ) // Ceiling trap placeholder
			{
				map[i][j] = 31;
			}
			if ( map[i][j] == 'n' ) // Wall trap placeholder ( a spike facing left )
			{
				map[i][j] = 17;
			}
			if ( map[i][j] == 'N' ) // Wall trap placeholder ( a spike facing right )
			{
				map[i][j] = 16;
			}
			if ( map[i][j] == 'S' ) // Snail Monster placeholder ( a @/' )
			{
				Monster Monstersnail;

				Monstersnail.x = j; // location of X-coordinates of snail
				Monstersnail.y = i; // location of Y-coordinates of snail
				Monstersnail.health = 2; // health of snail

				MonsterSnail.push_back(Monstersnail); // stores coordinates in vector

				map[i][j] = ' '; // replace with a space
			}

			if ( map[i][j] == 'M' ) // Floater Monster placeholder ( a ascii 235 )
			{
				Monster floater;

				floater.x = j; // location of X-coordinates of floater
				floater.y = i; // location of Y-coordinates of floater
				floater.health = 1; // health of floater

				Floater.push_back(floater); // stores coordinates in a vector

				map[i][j] = ' '; // replace with a space
			}

			if ( map[i][j] == 'F' ) // InnerFear Monster placeholder 
			{
				Monster innerfear;

				innerfear.x = j; // location of X-coordinates of InnerFear
				innerfear.y = i; // location of Y-coordinates of InnerFear
				innerfear.health = 1; // health of InnerFear

				InnerFear.push_back(innerfear); // stores coordinates in a vector

				map[i][j] = ' '; // replace with a space
			}

			if ( map[i][j] == 'R' ) // Rat Monster placeholder 
			{
				Monster rat;

				rat.x = j; // location of X-coordinates of Rat
				rat.y = i; // location of Y-coordinates of Rat
				rat.health = 1; // health of Rat

				Rat.push_back(rat); // stores coordinates in a vector

				map[i][j] = ' '; // replace with a space
			}

			if ( map[i][j] == 'W' ) // Wengyew Monster placeholder 
			{
				Monster wengyew;

				wengyew.x = j; // location of X-coordinates of wengyew
				wengyew.y = i; // location of Y-coordinates of wengyew
				wengyew.health = 10; // health of wengyew

				Wengyew.push_back(wengyew); // stores coordinates in a vector

				map[i][j] = ' '; // replace with a space
			}

			if ( map[i][j] == 'Y' ) // CatFish Monster placeholder 
			{
				Monster catFish;

				catFish.x = j; // location of X-coordinates of CatFish
				catFish.y = i; // location of Y-coordinates of CatFish
				catFish.health = 5; // health of CatFish

				CatFish.push_back(catFish); // stores coordinates in a vector

				map[i][j] = ' '; // replace with a space
			}

			if( map[i][j] == 'D' ) // DeadFish Monster placeholder
			{
				Monster deadFish;

				deadFish.x = j; // location of X-coordinates of DeadFish
				deadFish.y = i; // location of Y-coordinates of DeadFish
				deadFish.health = 4; // health of DeadFish

				DeadFish.push_back(deadFish); // stores coordinates in a vector

				map[i][j] = ' '; // replace with a space
			}

			if( map[i][j] == 'L' ) // LiveFish Monster placeholder
			{
				Monster liveFish;

				liveFish.x = j; // location of X-coordinates of LiveFish
				liveFish.y = i; // location of Y-coordinates of LiveFish
				liveFish.health = 2; // health of LiveFish

				LiveFish.push_back(liveFish); // stores coordinates in a vector

				map[i][j] = ' '; // replace with a space
			}

			if( map[i][j] == 'V' ) // DeadFish Monster placeholder
			{
				Monster villager;

				villager.x = j; // location of X-coordinates of LiveFish
				villager.y = i; // location of Y-coordinates of LiveFish

				Villager.push_back(villager); // stores coordinates in a vector

				map[i][j] = ' '; // replace with a space
			}

			if ( map[i][j] == 'T') // TREASURE HORRYY SHEET $$$
			{
				map[i][j] = 15;
			}


			if ( map[i][j] == 'P' ) // Portal to next
			{
				map[i][j] = 239;
			}

			if ( map[i][j] == 'p' ) // Portal to back
			{
				map[i][j] = 234;
			}

			if ( map[i][j] == 's' ) // Portal special
			{
				map[i][j] = 21;
			}

			if ( map[i][j] == '~' ) // Sign
			{
				map[i][j] = 209;
			}

			if ( map[i][j] == '+' ) // Shop
			{
				map[i][j] = 227;
			}
		}
	}
}
void renderLevel() // Renders map into console
{
	for (int i = 0; i < MAPHEIGHT; i++)
	{
		for (int j = 0; j < MAPWIDTH; j++)
		{
			gotoXY(j, i); // go to XY coords respectively,
			if ( map[i][j] == '#')
			{
				std::cout << (char)219; // and print block to replace walls
			}

			if ( map[i][j] == 239)
			{
				colour(0x0A);
				std::cout << (char)239; // Portal next
				colour(0x0F);
			}

			if ( map[i][j] == 234)
			{
				colour(0x0A);
				std::cout << (char)234; // Portal back
				colour(0x0F);
			}

			if ( map[i][j] == 21)
			{
				colour(0x0A);
				std::cout << (char)21; // Portal special
				colour(0x0F);
			}

			if ( map[i][j] == 227)
			{
				colour(0x0B);
				std::cout << (char)227; // Shop
				colour(0x0F);
			}

			if ( map[i][j] == 209)
			{
				colour(0x07);
				std::cout << (char)209; // Sign
				colour(0x0F);
			}

			else
			{
				std::cout << map[i][j]; // else print what's in the array
			}
		}
	}
}

void renderUIborders()
{
	gotoXY(0, 24);
	std::cout << (char)201;
	for(int i = 0; i < 118; i++)
	{
		std::cout << (char)205;
	}
	std::cout << (char)187;

	gotoXY(0, 38);
	std::cout << (char)200;
	for(int i = 0; i < 118; i++)
	{
		std::cout << (char)205;
	}
	std::cout << (char)188;

	gotoXY(79, 25);
	std::cout << (char)218;
	
	for ( int i = 26; i < 37; i++)
	{
		gotoXY(79, i);
		std::cout << (char)179;
	}

	gotoXY(79, 37);
	std::cout << (char)192;

	gotoXY(MAPWIDTH-2, 25);
	std::cout << (char)191;
	
	for ( int i = 26; i < 37; i++)
	{
		gotoXY(MAPWIDTH-2, i);
		std::cout << (char)179;
	}

	gotoXY(MAPWIDTH-2, 37);
	std::cout << (char)217;

	
	for ( int i = 26; i < 37; i++)
	{
		gotoXY(MAPWIDTH-2, i);
		std::cout << (char)179;
	}

	gotoXY(MAPWIDTH-2, 37);
	std::cout << (char)217;
}
void renderHP() // displays amount of HP player still has.
{
	gotoXY(14, 26); // Clear HP section for render again
	std::cout << "        ";
	colour(0x0F);
	gotoXY(6, 26);
	std::cout << "Health: ";
	gotoXY(14, 26);
	colour(0x0C);
	for ( int i = 0; i < PlayerHealth; i++ )
	{
		std::cout << (char)3 << " ";
	}
	colour(0x0F);
	gotoXY(25, 26); // Clear HP section for render again
	std::cout << "          ";

	gotoXY(0, 24);
}
void renderMoney()
{
	gotoXY(50, 26);
	{
		std::cout << "        ";
	}
	gotoXY(40, 26);
	std::cout << "Quennies: ";
	gotoXY(50, 26);
	std::cout << MoneyCount;
}

void checkForElement()
{
	if (map[charLocation.Y][charLocation.X] == 239)//Portal to next
	{
		if(checkLevel != NUMBEROFLEVELS)
		{
			checkLevel++;
		}
		init();
	}

	if (map[charLocation.Y][charLocation.X] == 234)//Portal back
	{
		if(checkLevel != 1)
		{
			checkLevel--;
		}
		init();
	}

	if (map[charLocation.Y][charLocation.X] == 21)//Portal special
	{
		if(checkLevel == 10)
		{
			checkLevel = 18;
		}

		else if(checkLevel == 18)
		{
			checkLevel = 10;
		}

		else if(checkLevel == 9)
		{
			checkLevel = 27;
		}

		else if(checkLevel == 27)
		{
			checkLevel = 9;
		}
		fromSPortal = true;
		init();
	}

	if (map[charLocation.Y][charLocation.X] == 15)//treasure
	{
		map[charLocation.Y][charLocation.X] = 32; //clear treasure
		MoneyCount = MoneyCount + 10;
		MoneyInv = MoneyInv + 10;
		renderMoney();
	}

	if (map[charLocation.Y][charLocation.X] == 227)//Shop
	{
		saveGame();
		gamestate = SHOP;
	}
}
void renderStory()
{
		if ( checkLevel == 1 ) // render story
	{
		if ( hasStoryRendered == 0 )
		{
			for ( unsigned int i = 0; i < 7; i++) 
			{	
				gotoXY(6+6, i+5);
				std::cout << StoryPage1[i];
			}
			hasStoryRendered = 1;
		}
	}

	if ( checkLevel == 2 ) // render story
	{
		if ( hasStoryRendered == 0 )
		{
			for ( unsigned int i = 0; i < 4; i++)
			{	
				gotoXY(6+6, i+5);
				std::cout << StoryPage2[i];
			}
			hasStoryRendered = 1;
		}
	}
	
	if ( checkLevel == 3 ) // render story
	{
		if ( hasStoryRendered == 0 )
		{
			for ( unsigned int i = 0; i < 5; i++)
			{	
				gotoXY(6+6, i+5);
				std::cout << StoryPage3[i];
			}
			hasStoryRendered = 1;
		}
	}
}
void resetElements() // removes monsters and effects on the map
{
	MonsterSnail.clear();
	Floater.clear();
	InnerFear.clear();
	Rat.clear();
	Wengyew.clear();
	CatFish.clear();
	DeadFish.clear();
	LiveFish.clear();
	Villager.clear();
	meteor.clear();
	splint.clear();
	laser.clear();
	lava.clear();
	BossHitbox.clear();
	PianusHitbox.clear();
}
void init()
{
    // Set precision for floating point output
    std::cout << std::fixed << std::setprecision(3);

    // Get console width and height
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */     

    /* get the number of character cells in the current buffer */ 
    GetConsoleScreenBufferInfo( GetStdHandle( STD_OUTPUT_HANDLE ), &csbi );
    consoleSize.X = csbi.srWindow.Right + 1;
    consoleSize.Y = csbi.srWindow.Bottom + 1;

    // set the character to be in the center of the screen.

    elapsedTime = 0.0;
	hasLevelRendered = 0;
	skillDelay = 0.0;
	fallDelay = 0.0;
	jumpDelay = 0.0;
	snailMoveDelay = 0.0;
	floaterMoveDelay = 0.0;
	InnerFearMoveDelay = 0.0;
	RatMoveDelay = 0.0;
	WengyewMoveDelay = 0.0;
	CatFishMoveDelay = 0.0;
	DeadFishMoveDelay = 0.0;
	VillagerMoveDelay - 0.0;

	hasbeenStabbed = 0;
	hasbeenDamaged = 0;
	bossStatus = 0;
	isBossLevel = 0;
	hasStoryRendered = 0;
	MoneyInv = 0;

	for(int i = 0; i < NUMBEROFLEVELS + 1; i++)
	{
		leveltoload = "level";
		
		if (checkLevel == 43)
		{
			isBossLevel = 1;
			bosscurrentHP = bossHP;
		}

		if (checkLevel == 17)
		{
			isBossLevel = 2;
			pianuscurrentHP = pianusHP;
		}

		if (checkLevel == i)
		{
			std::string L = std::to_string(static_cast<unsigned long long>(i));
			leveltoload += L;
			signNumber = i;
		}
		leveltoload += ".txt";
		loadLevel(leveltoload);
	}

	if (fromSPortal == true)
	{
		fromSPortal = true;
	}
	//check if character came from next or prev map
	else if ( checkPrevLevel > checkLevel ) //came from next map
	{
		spawnwhere = true; // spawn at c
		fromSPortal = false;
	}
	else
	{
		spawnwhere = false; // spawn at C
		fromSPortal = false;
	}

	checkPrevLevel = checkLevel;

	// prepares map for rendering
	prepareLevel();
	
	//Prepare Skills
	initSkill();
	//Add Shop Function here. Shop Function should Modify the Values inside initskill
	//Create an int Variable called damageUpgrade = 0; This variable is added to the Damage(Even if no Value yet).
	//Once it has a value. you know what happens.
}
void shutdown()
{
	saveGame();
	// Reset to white text on black background
	colour(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
}
void getInput()
{    
    keyPressed[K_UP] = isKeyPressed(VK_UP);
    keyPressed[K_DOWN] = isKeyPressed(VK_DOWN);
    keyPressed[K_LEFT] = isKeyPressed(VK_LEFT);
    keyPressed[K_RIGHT] = isKeyPressed(VK_RIGHT);
    keyPressed[K_ESCAPE] = isKeyPressed(VK_ESCAPE);
	keyPressed[K_SPACE] = isKeyPressed(VK_SPACE);
	keyPressed[K_ENTER] = isKeyPressed(VK_RETURN);
	keyPressed[K_Q] = isKeyPressed(0x51);
    keyPressed[K_E] = isKeyPressed(0x45);
    keyPressed[K_C] = isKeyPressed(0x43);
}
void update(double dt)
{
    // get the delta time
    elapsedTime += dt;
	jumpDelay += dt;
	fallDelay += dt;
	skillDelay += dt;
	bossFrameDelay += dt;
	snailMoveDelay += dt;
	floaterMoveDelay += dt;
	InnerFearMoveDelay += dt;
	RatMoveDelay += dt;
	WengyewMoveDelay += dt;
	CatFishMoveDelay += dt;
	DeadFishMoveDelay += dt;
	LiveFishMoveDelay += dt;
	VillagerMoveDelay += dt;
	hitboxDelay += dt;
	canJump += dt;
	PlayerSkillDelay += dt;
    deltaTime = dt;
	gravity();
	checkforSpike();
	checkForElement();
	updateSigns();

	if ( hasbeenStabbed == 1 ) 
	{
		colour(0x0F);

		hasbeenStabbed = 0;
		gotoXY(14, 8);
	}

	if ( isBossLevel == 1 )
	{
		if ( bosscurrentHP != 0 )
		{
			updateBossHitbox();
			checkCollisionHitbox();
			bossDifficulty = (bossHP - bosscurrentHP) * 0.3;
			if ( meteor.size() != 0 ) // If there are meteors
			{
				updateMeteor();
				checkCollisionMeteor();
			}

			if ( splint.size() != 0 ) // If boss used splint
			{
				updateSplint();
				checkCollisionSplint();
			}
		}
		else
			resetElements();
	}

	if ( isBossLevel == 2 )
	{
		if ( pianuscurrentHP != 0 )
		{
			updatePianusHitbox();
			checkCollisionHitbox();
			if ( laser.size() != 0 ) // If there's laser
			{
				updateLaser();
				checkCollisionLaser();
			}

			if ( lava.size() != 0 ) // If there's lava
			{
				updateLava();
				checkCollisionLava();
			}
		}
		else
			resetElements();
	}

	if ( MonsterSnail.size() != 0 ) // When there are snails
	{
		if ( snailMoveDelay > 1.000 ) // Snails move every 1000ms
		{
			updateSnails();
			snailMoveDelay = 0; // reset movement timer
		}
		checkCollisionSnail();
	}

	if ( Floater.size() != 0 ) // When there are floaters
	{
		if ( floaterMoveDelay > 0.750 ) // floaters move every 750ms
		{
			updateFloater();
			floaterMoveDelay = 0; // reset movement timer
		}
		checkCollisionFloater();
	}

	if ( Rat.size() != 0 ) // When there are Rats
	{
		if ( RatMoveDelay > 0.250 ) // Rats move every 250ms
		{
			updateRat();
			RatMoveDelay = 0; // reset movement timer
		}
		checkCollisionRat();
	}

	if ( InnerFear.size() != 0 ) // When there are InnerFears
	{
		if ( InnerFearMoveDelay > 0.400 ) // InnerFears move every 400ms
		{
			updateInnerFear();
			InnerFearMoveDelay = 0; // reset movement timer
		}
		checkCollisionInnerFear();
	}

		if ( Wengyew.size() != 0 ) // When there are wengyews
	{
		if ( WengyewMoveDelay > 0.100 ) // wengyews move every 100ms
		{
			updateWengyew();
			WengyewMoveDelay = 0; // reset movement timer
		}
		checkCollisionWengyew();
	}

		if ( CatFish.size() != 0 ) // When there are CatFishes
	{
		if ( CatFishMoveDelay > 0.450 ) // CatFishes move every 450ms
		{
			updateCatFish();
			CatFishMoveDelay = 0; // reset movement timer
		}
		checkCollisionCatFish();
	}

		if ( DeadFish.size() != 0 ) // When there are DeadFishes
	{
		if ( DeadFishMoveDelay > 0.250 ) // DeadFishes move every 250ms
		{
			updateDeadFish();
			DeadFishMoveDelay = 0; // reset movement timer
		}
		checkCollisionDeadFish();
	}

		if ( LiveFish.size() != 0 ) // When there are LiveFishes
	{
		if ( LiveFishMoveDelay > 0.250 ) // LiveFishes move every 250ms
		{
			updateLiveFish();
			LiveFishMoveDelay = 0; // reset movement timer
		}
		checkCollisionLiveFish();
	}

		if ( Villager.size() != 0 ) // When there are Villagers
	{
		if ( VillagerMoveDelay > 0.800 ) // Villagers move every 800ms
		{
			updateVillager();
			VillagerMoveDelay = 0; // reset movement timer
		}
	}

	if ( CKey.size() != 0 )
	{
		updateSkill(CKey);
	}

    // Updating the location of the character based on the key press
    if (keyPressed[K_LEFT])
    {
       if (map[charLocation.Y][charLocation.X-1] != '#') // There is no wall on the left.
		{
			Beep(1440, 30);
			gotoXY(charLocation.X, charLocation.Y); // Preventing screen flickering.
			hasMoved = 1;
			charLocation.X--; // Move left.
			playerFacing = 0;
		}
    }

    if (keyPressed[K_RIGHT])
    {
		if (map[charLocation.Y][charLocation.X+1] != '#') // There is no wall on the right.
		{
			Beep(1440, 30);
			gotoXY(charLocation.X, charLocation.Y); // Preventing screen flickering.
			hasMoved = 1;
			charLocation.X++;
			playerFacing = 1;
		}
    }

	if (keyPressed[K_Q])
	{
		previousSkill();
	}

	if (keyPressed[K_E])
	{
		nextSkill();
	}

	if (keyPressed[K_C])
	{
		if(PlayerSkillDelay >= AddCKey.Speed)
		{
		Attack(CKey);
		PlayerSkillDelay = 0;
		}
	}

	if (keyPressed[K_SPACE])
	{
		jump();
	}

    // quits the game if player hits the escape key
    if (keyPressed[K_ESCAPE])
	{
		saveGame();
        gamestate = LEVELMENU;
	}

	if ( PlayerHealth <= 0 )
	{
		MoneyCount = MoneyCount - MoneyInv;
		MoneyInv = 0;
		if(MoneyCount > 4)
		{
			MoneyCount = MoneyCount - 5;
		}

		saveGame();
	}
	checkforDeath();
}
void render()
{
    // clear previous screen if need to re render
	if ( hasLevelRendered == 0 )
	{
		cls();
		colour(0x0F);
		renderLevel();
		renderUIborders();
		renderHP();
		renderMoney();
		hasLevelRendered = 1;
	}

	//clear only area around character. prevent flickering~
	if ( hasMoved == 1 )
	{
		for ( int i = charLocation.X-1; i <= charLocation.X+1; i++)
		{
			for ( int j = charLocation.Y-1; j <= charLocation.Y+1; j++)
			{
				gotoXY(i, j);
				if ( map[j][i] == '#' )
					std::cout << (char)219;
				else if ( map[j][i] == 234 )
				{
					colour(0x0A);
					std::cout << (char)234;
					colour(0x0F);
				}
				else if ( map[j][i] == 239 )
				{
					colour(0x0A);
					std::cout << (char)239;
					colour(0x0F);
				}
				else
					std::cout << map[j][i];
			}
		}
		hasMoved = 0;
	}

	//render Skill
	if ( CKey.size() != 0 )
	{
		spawnSkill(CKey);
	}


	// render character
    gotoXY(charLocation);
    colour(0x0C);
    std::cout << (char)1;
	colour(0x0F);

	renderSigns();  
	renderStory();

	if ( hasbeenDamaged == 1 )
	{
		renderHP();
		hasbeenDamaged = 0;
	}
	
	if ( isBossLevel == 1 ) // These renders only occur when it's a boss level
	{
		bossRenderHP();
		renderBossHitbox();
		if ( meteor.size() != 0 ) // If boss spawned meteors
		{
			renderMeteor();
		}

		if ( splint.size() != 0 ) // If boss used splint
		{
			renderSplint();
		}

		checkBossStatus();
	}

	if ( isBossLevel == 2 )
	{
		if ( RemovePianusHitbox == 1 )
			removePianusHitbox();
		pianusRenderHP();
		renderPianusHitbox();
		if ( laser.size() != 0 ) // If laz0r
		{
			renderLaser();
		}

		if ( lava.size() != 0 ) // If there's lavarh
		{
			renderLava();
			// check collision
		}

		checkPianusStatus();
	}


	renderMonster();

	//gotoXY(6, 3);
	//std::cout << "X: " << charLocation.X << " Y: " << charLocation.Y;

    colour(0x0F);

    //render the game

    // render time taken to calculate this frame
    //gotoXY(70, 0);
    //colour(0x1A);
    //std::cout << 1.0 / deltaTime << "fps" << std::endl;
  
    //gotoXY(0, 0);
    //colour(0x59);
    //std::cout << elapsedTime << "secs" << std::endl;
	
}