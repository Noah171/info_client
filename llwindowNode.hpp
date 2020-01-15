#ifndef LLWIN_NODE
#define LLWIN_NODE

#include <ncurses.h>

// Node in doubly linked list
class WNode {
public:
	WNode(WINDOW * win);
	~WNode();
	WINDOW *getWindow();
	WNode *next;
	WNode *prev;

private:
	WINDOW * window;
};

#endif
