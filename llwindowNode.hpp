#ifndef LLWIN_NODE
#define LLWIN_NODE

#include <ncurses.h>

// Node in doubly linked list
class WNODE {
public:
	WNODE();
	~WNODE();

	WINDOW * window;
	WNODE *next;
	WNODE *prev;
};

#endif
