#ifndef CURSOR
#define CURSORStream Avatar

#include <ncurses.h>
#include "llwindow.hpp"

class Cursor{

public:
	Cursor(WINDOW *x, int y, WINDOW *startWin);
	~Cursor();
	void goUp();
	void goDown();
	void goRight();
	void goLeft();

private:
	int y;
	WINDOW *curwin; // basically the cursor's 'x' value in the cartesian plane
};
#endif
