#ifndef LLWINDOW
#define LLWINDOW

#include <ncurses.h>
#include "llwindowNode.hpp"


// Linked list of WNODE's descriptor
class WHEAD {
public:
	// methods
	WHEAD();
	~WHEAD();
	void appendNode(WNODE *window);

	// attributes
	WNODE *first;
	WNODE *last;
	int size;

};

#endif
