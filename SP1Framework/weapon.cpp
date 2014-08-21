// This is file for the weapon stuff
//
//
#include "game.h"
#include "Framework\console.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

//WEAPON VARIABLES
int weaponDAMAGE;                         //Tweak for Damage Of Attacks                              -DO ALL TWEAKING IN WEAPON_PROPERTIES function!-
int weaponSPEED;                         //Tweak for Time Betweek Attacks                            -DO ALL TWEAKING IN WEAPON_PROPERTIES function!-
int weaponHITCOUNT;                     //Tweak for Hit Count of Attack                              -DO ALL TWEAKING IN WEAPON_PROPERTIES function!-
bool rangeORmelee = true;              //Tweak for Default Weapon, Melee = true && Range = false     -DO ALL TWEAKING IN WEAPON_PROPERTIES function!-
std::string beforeATTACK,afterATTACK; //Tweak for Attack/Standstill ASCII                            -DO ALL TWEAKING IN WEAPON_PROPERTIES function!-
std::string weaponHITBOX;            //Tweak for Hitbox ASCII. HITBOX Collide With OBJECT = EVENT    -DO ALL TWEAKING IN WEAPON_PROPERTIES function!-
std::string weaponSTATE;            //NO Tweaking, Finalizes String to Render
bool rightORleft = true;           //Tweak for Default Player Direction, Right = true && Left = false
COORD WEAPON;

void WEAPON_PROPERTIES(){ //TWEAK FOR WEAPON CHARACTERISTICS
        if (rangeORmelee == true)//Melee Equipped
        {weaponDAMAGE = 5;
        weaponSPEED = 20;
        beforeATTACK = "|";
        afterATTACK = "---";
        weaponHITBOX= "-";}
 
        else if (rangeORmelee == false)//Range Equipped
        {weaponDAMAGE = 2;
        weaponHITCOUNT = 1;
        weaponSPEED= 100;
        beforeATTACK = "y==-";
        afterATTACK ="y==-<";
        weaponHITBOX = "o";
 
        if (rightORleft == false){//If Player Facing Left, ASCII for Range Weapon will Change
                beforeATTACK = "-==y";
                afterATTACK = ">-==y";}
 
        }
        weaponSTATE = beforeATTACK;      //While Player Has Not Pressed Attack Button, beforeATTACK will be shown as the ASCII
}
  
void Atk(){
        weaponSTATE = afterATTACK;
        //Melee Attack, NIC just run an If Statement whether your Monster is in a Coordinate where weaponHITBOX resides.
        //Range Attack
        /*if (rangeORmelee == false)
        {
                UPDATE_BULLET();
                SPAWN_BULLET();
        }*/
}