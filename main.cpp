#include "media_info.hpp"
#include "LLHead.hpp"

#include <curses.h> // general curses stuff
#include <locale.h> // for setlocale() in main()
#include <cstdlib>
#include <stdio.h>
#include <chrono>
#include <thread>
#include <errno.h>
#include <unistd.h>
/* TODO:
 * 
 */

/* NOTES:
 * A) DONT use refresh, use wrefresh. If you want to know why read specifics on what "initscr" returns to super and what "refresh()" does (It doesn't refresh super, exactly, it's like "stdscrn"
 * B) Note that the way refresh works is odd.
 */

int getLongestStr(char ** strs, int numStrsn);

int main(int argc, char * argv[] ){
  WINDOW * super = NULL;
  int nlines = 0;
  int ncols = 0;
  LLHead windowll;

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
  curs_set(0); // sets the cursor to invisible
  // Gets the current terminal size and stores it in nlines and ncols, because it is a macro
  // nlines and ncols can be changed directly without pointers.
  getmaxyx(super, nlines,ncols);
  LLNode * firstWindow = new LLNode(super, (char*)DIRECTORY, 0,0);
  windowll.appendNode(firstWindow);
  // Get contents of media directory because that will decide the size of media window
  /** Main loop where things will actually happen **/
  for(int i = 0; 1; ++i){
    char inp = 0;
    if(is_term_resized(nlines, ncols)){
      getmaxyx(super,nlines,ncols);
      /* A) RESIZE SUBWINDOWS AND CONTENTS */
    }
    windowll.update();
    windowll.print();
    inp = getch();
    // adjust cursor position based on input
    switch(inp){
    case 'h':
      windowll.getCursor()->goLeft();
      break;
    case 'l':
      windowll.getCursor()->goRight();
      break;
    case 'j':
      windowll.getCursor()->goDown();
      break;
    case 'k':
      windowll.getCursor()->goUp();
      break;
    }
  }
  return endwin();
} // end main
