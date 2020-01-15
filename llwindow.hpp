#ifndef LLWINDOW
#define LLWINDOW

#include <ncurses.h>
#include "llwindowNode.hpp"


// Linked list of WNODE's descriptor
class WHead {
public:
	// methods
	WHead();
	~WHead();
	void appendNode(WNode *window);

	// attributes
	WNode *first;
	WNode *last;
	int size;

};

#endif
