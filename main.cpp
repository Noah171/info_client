#include <curses.h> // general curses stuff
#include <locale.h> // for setlocale() in main()


#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <thread>

#include "cursor.h"

/* TODO:
 * A) resize subwindows and contents
 * B) DONT use refresh, use wrefresh. If you want to know why read specifics on what "initscr" 
 * returns to directory and what "refresh()" does (It doesn't refresh directory, exactly, it's like 
 * "stdscrn"
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
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if(is_term_resized(nlines, ncols)){
			getmaxyx(directory,nlines,ncols);
			/* A) RESIZE SUBWINDOWS AND CONTENTS */
		}
		if(i > 20){
			printf("%d\n", wmove(thirdWindow, 10,10));
			printf("OK%d ERR%d\n", OK,ERR);
			std::this_thread::sleep_for(std::chrono::milliseconds(5000));
			break;
		}
		
		//if(i > 25)
		//	wmove(secondWindow, 12,12);

		wrefresh(secondWindow);
		wrefresh(directory);
		wrefresh(thirdWindow);
		//refresh(); // Right now, refreshing the window when moving the cursor into the 
		//third window causes the cursor to move relative to WINDOW *directory
	}
	
	return endwin();
}
