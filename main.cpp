#include "cursor.hpp"
#include "media_info.hpp"

#include <curses.h> // general curses stuff
#include <locale.h> // for setlocale() in main()
#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <errno.h>

#define ADDITIONAL_COL_SPACE 4

/* TODO:
 * A) resize subwindows and contents
 * B) Make windows into linked lists so that moving right with cursor is easier.
 * C) Bind keys properly so that hjkl do what they do in vim ie move left,up,down,righto
 * D) Mke a "freeWindows" function which calls delwin() on each window in the linked list
 * E) make a pretty print column function into the linked list window
 * 	
*/

/* NOTES:
 * A) DONT use refresh, use wrefresh. If you want to know why read specifics on what "initscr" returns to super and what "refresh()" does (It doesn't refresh super, exactly, it's like "stdscrn"
 * B) Note that the way refresh works is odd.
 */

int getLongestStr(char ** strs, int numStrsn);

int main(int argc, char * argv[] ){
	WINDOW * super = NULL;
	WINDOW * media = NULL;
	char ** mediaTypes = NULL;
	int nlines = 0, ncols = 0, nnames = 0;
	Cursor cursor(media,0,media);

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
	// Sets ncols to the longest string's length
	int longestIndex = getLongestStr(mediaTypes, nnames);
	
	/* Make initial window to display current working directory */
	ncols = strlen(mediaTypes[longestIndex]) + ADDITIONAL_COL_SPACE;
	media = subwin(super, nlines-1,ncols,0,0);

	/** Main loop where things will actually happen **/
	for(int i = 0; 1; ++i){
		//prettyPrintColumn(media, mediaTypes, nnames, ncols);
		if(is_term_resized(nlines, ncols)){
			getmaxyx(super,nlines,ncols);
			/* A) RESIZE SUBWINDOWS AND CONTENTS */
		}
		printf("%d\n", wmove(media, 0,0));
		printf("OK%d ERR%d\n", OK,ERR);
		wrefresh(media);
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		wrefresh(media);
		break;
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(50000));
	
	freeFileNames(&mediaTypes, nnames);
	return endwin();
}

int getLongestStr(char ** strings, int numStrs)
// Gets the longest string in an array of strings
{
	int index = 0;
	int longest = 0;
	for(int i = 0; i < numStrs; ++i){
		int strl = strlen(strings[i]);
		if(strl > longest){
			index = i;
			longest = strl;
		}
	}
	return index;
}

