#include <curses.h> // general curses stuff
#include <locale.h> // for setlocale() in main()


#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <thread>

#include "cursor.h"
#include "media_info_storage.h"

/* TODO:
 * A) resize subwindows and contents
*/
/* NOTES:
 * A) DONT use refresh, use wrefresh. If you want to know why read specifics on what "initscr" 
 * returns to super and what "refresh()" does (It doesn't refresh super, exactly, it's like 
 * "stdscrn"
 * B) Note that the way refresh works is odd.
 *
 */
#define printerr(err) fprintf(stderr, err);

int main(int argc, char * argv[] ){
	WINDOW * super = NULL;
	WINDOW * media = NULL;
	char * mediaTypes [] = NULL;
	int nlines, ncols = 0;
	/** Window initialization **/

	// This ensures our prefered locale settings are used (like character sets)
	setlocale(LC_ALL,"");
	// recommended function sequence for curses to work in a terminal
	super = initscr();
	cbreak();
	noecho();
	// Some optional calls that most programs use according to 'man ncurses'
	nonl();
	intrflush(stdscr, FALSE);
	keypad(stdscr,TRUE);

	/** Setting Hotkeys **/

	/** END Setting Hotkeys **/
	// Gets the current terminal size and stores it in nlines and ncols, because it is a macro
	// nlines and ncols can be changed directly without pointers.
	getmaxyx(super, nlines,ncols);
//	return endwin();

	// Get contents of media directory because that will decide the size of media window
	 getFileNames(mediaTypes, DIRECTORY);
	/* Make initial window to display current working directory */

	currentDirWindow = subwin(directory, nlines-1,ncols/2,0,0);
	
	
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
		if(i > 20 && i < 25){
			printf("%d\n", wmove(thirdWindow, 0,0));
			printf("OK%d ERR%d\n", OK,ERR);
			wrefresh(thirdWindow);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));

		}
		
		if(i > 25 && i < 30){
			wrefresh(secondWindow);
			wmove(secondWindow, 22,12);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			wrefresh(secondWindow);
		}
		if(i > 30){
			wrefresh(thirdWindow);
			wmove(thirdWindow, 22,32);
			waddstr(thirdWindow, "GGGGGGGG");
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			wrefresh(secondWindow);
			waddstr(thirdWindow, "GGGGGGG");
			wrefresh(secondWindow);
			waddstr(secondWindow, "FFFFFFF");
		}

		//wrefresh(secondWindow);
		//wrefresh(directory);
		//wrefresh(thirdWindow);
		//refresh(); // Right now, refreshing the window when moving the cursor into the 
		//third window causes the cursor to move relative to WINDOW *directory
	}
	
	return endwin();
}
