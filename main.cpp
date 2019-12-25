#include <curses.h> // general curses stuff
#include <locale.h> // for setlocale() in main()


#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <thread>

/* TODO:
 * A) resize subwindows and contents
 *
 * */

#define printerr(err) fprintf(stderr, err);

int main(int argc, char * argv[] ){
	WINDOW * directory= NULL;
	WINDOW * secondWindow = NULL;
	WINDOW * thirdWindow = NULL;
	int nlines, ncols = 0;
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
	getmaxyx(directory, nlines,ncols);
//	return endwin();
	secondWindow = subwin(directory, nlines-1,ncols/2,0,0);
	
	thirdWindow = subwin(directory, nlines-1, (ncols+1)/2,
				0, (ncols)/2);
	/** Main loop where things will actually happen **/
	for(int i = 0; 1; ++i){
		if( i  < 20){
			waddstr(secondWindow, "FFFFFFFF");
			waddstr(thirdWindow, "GGGGGGGG");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		if(is_term_resized(nlines, ncols)){
			getmaxyx(directory,nlines,ncols);
			/* A) RESIZE SUBWINDOWS AND CONTENTS */
		}
		if(i > 20){
			wmove(thirdWindow, 10,10);
			wmove(secondWindow, 10,10);
		}
		wrefresh(secondWindow);
		wrefresh(thirdWindow);
	}
	
	return endwin();
}
