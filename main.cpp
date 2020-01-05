#include "mouse.hpp"
#include "media_info.hpp"

#include <curses.h> // general curses stuff
#include <locale.h> // for setlocale() in main()


#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <errno.h>


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

int main(int argc, char * argv[] ){
	WINDOW * super = NULL;
	WINDOW * media = NULL;
	char ** mediaTypes = NULL;
	int nlines = 0, ncols = 0, nnames = 0;
	Mouse mouse;

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

	// Get contents of media directory because that will decide the size of media window
	nnames = getFileNames(&mediaTypes, DIRECTORY);
	ncols = nnames;
	/* Make initial window to display current working directory */
	media = subwin(super, nlines-1,ncols+3,0,0);
	
	/** Main loop where things will actually happen **/
	for(int i = 0; 1; ++i){
		/* update the windows so far just the media window */
		// count down for print formatting purposes
		for(int j = 0; j < ncols; j++){
			waddstr(media,mediaTypes[j]);
			waddstr(media,"\n");
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
		if(is_term_resized(nlines, ncols)){
			getmaxyx(super,nlines,ncols);
			/* A) RESIZE SUBWINDOWS AND CONTENTS */
		}
		if(i > 20 && i < 25){
			printf("%d\n", wmove(media, 0,0));
			printf("OK%d ERR%d\n", OK,ERR);
			wrefresh(media);
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
		wrefresh(media);
		break;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(50000));
    freeFileNames(&mediaTypes, nnames);
	return endwin();
}
