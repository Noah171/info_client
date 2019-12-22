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
	
	secondWindow = derwin(directory, 5,5,5,5);
	/** Main loop where things will actually happen **/
	while(1){
		addstr("dafkjdas;fasfj;askf");
		waddstr(secondWindow, "asdfdafa");
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		wrefresh(secondWindow);
		refresh();
	}
	
	return endwin();
}
