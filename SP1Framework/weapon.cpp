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

int BULLETS_SHOT = 0;
int BULLETS_LIMIT = 1;
struct Bullets_Properties{
	int x,y;
	bool isRENDERED;
	int health;

	Bullets_Properties(){
		isRENDERED = false;
		health = 2;
	}
}Bullets[20];

void updateBullets(){
	for (int x = 0; x< 20; ++x)
	{
		if (Bullets[x].isRENDERED== true)
		{
			Bullets[x].x += 1;
		}
	}
}

void spawnBullets(){
	for(int x= 0; x<20; ++x)
	{
		if (Bullets[x].isRENDERED == true)
		{
			gotoXY(Bullets[x].x-1, Bullets[x].y);
			std::cout<<" ";
			gotoXY(Bullets[x].x, Bullets[x].y);
			std::cout<<"o";
		}
	}
}
void Attack(){
	while (BULLETS_SHOT < BULLETS_LIMIT)
	{
		Bullets[BULLETS_SHOT].isRENDERED = true;
		Bullets[BULLETS_SHOT].x =charLocation.X + 1;
		Bullets[BULLETS_SHOT].y =charLocation.Y;
		BULLETS_SHOT +=1;
	}
	BULLETS_LIMIT +=1;
}