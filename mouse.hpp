#ifndef MOUSE
#define MOUSE

#include <curses.h>

class Mouse{
public:
	Mouse(WINDOW *x, int y, WINDOW *startWin);
	~Mouse();
private:
	int y;
	WINDOW *curwin; // basically the mouse's 'x' value in the cartesian plane
	const WINDOW *start;
};
#endif
