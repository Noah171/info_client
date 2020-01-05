#ifndef MOUSE
#define MOUSE

#include <curses.h>

class Mouse{
public:
	Mouse();
	~Mouse();
private:
	int x;
	int y;
	WINDOW *curwin;
};
#endif
