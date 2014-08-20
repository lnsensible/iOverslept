#include "console.h"
#include <cstdio>

void gotoXY(int x,int y)
{
	COORD c={x,y};
    gotoXY(c);
}

void gotoXY(COORD c)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}

void colour(WORD attrib)
{	
	HANDLE hstdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hstdout, attrib );
		
}

/* Standard error macro for reporting API errors */ 
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \
    on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

void cls( HANDLE hConsole )
{
    if (!hConsole)
        hConsole = GetStdHandle( STD_OUTPUT_HANDLE );

    COORD coordScreen = { 0, 0 };    /* here's where we'll home the
                                        cursor */ 
    BOOL bSuccess;
    DWORD cCharsWritten;
    CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */ 
    DWORD dwConSize;                 /* number of character cells in
                                        the current buffer */ 

    /* get the number of character cells in the current buffer */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "GetConsoleScreenBufferInfo" );
    dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

    /* fill the entire screen with blanks */ 

    bSuccess = FillConsoleOutputCharacter( hConsole, (TCHAR) ' ',
        dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputCharacter" );

    /* get the current text attribute */ 

    bSuccess = GetConsoleScreenBufferInfo( hConsole, &csbi );
    PERR( bSuccess, "ConsoleScreenBufferInfo" );

    /* now set the buffer's attributes accordingly */ 

    bSuccess = FillConsoleOutputAttribute( hConsole, csbi.wAttributes,
        dwConSize, coordScreen, &cCharsWritten );
    PERR( bSuccess, "FillConsoleOutputAttribute" );

    /* put the cursor at (0, 0) */ 

    bSuccess = SetConsoleCursorPosition( hConsole, coordScreen );
    PERR( bSuccess, "SetConsoleCursorPosition" );
    return;
}
	
void ClearRows(int row1, int row2) // clear screen between row1 and row2
{
	//Get the handle to the current output buffer...
	 HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	 //This is used to reset the carat/cursor to the top left.
	 COORD coord = {0, row1};
	 //A return value... indicating how many chars were written
	 //   not used but we need to capture this since it will be
	 //   written anyway (passing NULL causes an access violation).
	 DWORD count;
	 //This is a structure containing all of the console info
	 // it is used here to find the size of the console.
	 CONSOLE_SCREEN_BUFFER_INFO csbi;
	 //Here we will set the current color
	 if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
	 {
		  //This fills the buffer with a given character (in this case 32=space).
		  FillConsoleOutputCharacter(hStdOut, (TCHAR) 32, csbi.dwSize.X * (row2-row1), coord, &count);
		  //This sets the forground/background color
		  FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * (row2-row1), coord, &count );
		  //This will set our cursor position for the next print statement.
		  SetConsoleCursorPosition(hStdOut, coord);
	 }
	 return;
}
	
bool isKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}