#include <curses.h> // general curses stuff
#include <locale.h> // for setlocale() in main()

#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <thread>

#define printerr(err) fprintf(stderr, err);

int main(int argc, char * argv[] ){
	WINDOW * directory= NULL;
	WINDOW * secondWindow = NULL;
	WINDOW * thirdWindow = NULL;
	int y,x = 0;
	/** Window initialization **/

	// This ensures our prefered locale settings are used (like character sets)
	setlocale(LC_ALL,"");
	// recommended function sequence for curses to work in a terminal
	directory = initscr();
	cbreak();
	noecho();
	// Some optional calls that most programs use according to 'man ncurses'
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr,TRUE);

	/** Setting Hotkeys **/

	
	/** END Setting Hotkeys **/
	getmaxyx(directory, y,x);
	printf("y:%d x:%d", y, x);
//	return endwin();

	secondWindow = subwin(directory, y-1,x/2-1,0,0);
	
	thirdWindow = subwin(directory, y-1, x/2-1,
				0, x+1/2);

	/** Main loop where things will actually happen **/
	while(1){
		waddstr(secondWindow, "FFFFFFFF");
		waddstr(thirdWindow, "GGGGGG");
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		wrefresh(secondWindow);
		wrefresh(thirdWindow);
	}
	
	return endwin();
}
