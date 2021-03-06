// This is the main file to hold everything together

#include "Framework\timer.h"
#include "game.h"


StopWatch g_timer;            // Timer function to keep track of time and the frame rate
bool g_quitGame = false;      // Set to true if you want to quit the game
const unsigned char FPS = 10; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
int initialisedornot = 0;

void mainLoop();

// TODO:
// Bug in waitUnitil. it waits for the time from getElapsedTime to waitUntil, but should be insignificant.

void SetWindow(int Width, int Height)  //Sets size of console... taken from 3dbuzz.com
   { 
    _COORD coord; 
    coord.X = Width; 
    coord.Y = Height; 

    _SMALL_RECT Rect; 
    Rect.Top = 0; 
    Rect.Left = 0; 
    Rect.Bottom = Height - 1; 
    Rect.Right = Width - 1; 

    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
    } 

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
}

int main()
{
	hidecursor();
	SetWindow(120, 40); // sets size of window to 120 width 40 height
    mainLoop();  // main loop
    shutdown();  // do clean up, if any. free memory.
	
	return 0;
}
// This main loop calls functions to get input, update and render the game
// at a specific frame rate
void mainLoop()
{
	while (g_quitGame == false)      // run this loop until user wants to quit 
	{  
		g_timer.startTimer();
		while ( gamestate == GAME ) 
		{
			if ( initialisedornot != 1 )
			{
				init();
				initialisedornot = 1;
			}

			getInput();
			update(g_timer.getElapsedTime());
			render();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
			{
				break;
			}
		}
		system("cls");
		initialisedornot = 0;

		while ( gamestate == MENU )//MAIN MENU :3
		{
			if ( initialisedornot != 1 )
			{
				playGameSound(S_MENU);
				initmainmenu();
				initialisedornot = 1;
			}

			getInput();
			updatemainmenu(g_timer.getElapsedTime());
			rendermainmenu();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		system("cls");
		initialisedornot = 0;

		while ( gamestate == LEVELMENU )//LEVEL MENU :DDDD
		{
			if ( initialisedornot != 1 )
			{
				initlevelmenu();
				initialisedornot = 1;
			}

			getInput();
			updatelevelmenu(g_timer.getElapsedTime());
			renderlevelmenu();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		system("cls");
		initialisedornot = 0;

		while ( gamestate == SHOP )//SHOP MENU
		{
			if ( initialisedornot != 1 )
			{
				initSHOP();
				initialisedornot = 1;
			}

			getInput();
			updateSHOP(g_timer.getElapsedTime());
			renderSHOP();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		system("cls");
		initialisedornot = 0;

		while ( gamestate == DEATH )//DEATH MENU :C
		{
			if ( initialisedornot != 1 )
			{
				initdeathmenu();
				initialisedornot = 1;
			}

			getInput();
			updatedeathmenu(g_timer.getElapsedTime());
			renderdeathmenu();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		system("cls");
		initialisedornot = 0;

		while ( gamestate == ENDGAME )//YOU WIN :DDD
		{
			if ( initialisedornot != 1 )
			{
				initendmenu();
				initialisedornot = 1;
			}

			getInput();
			updateendmenu(g_timer.getElapsedTime());
			renderendmenu();
			g_timer.waitUntil(frameTime);

			if ( g_quitGame == true )
				break;
		}
		system("cls");
		initialisedornot = 0;


	}
}
