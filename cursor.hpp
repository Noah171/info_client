#ifndef CURSOR
#define CURSOR

#include <ncurses.h>

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
	const WINDOW *start;
};
#endif
