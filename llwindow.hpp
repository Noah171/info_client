#ifndef LLWINDOW
#define LLWINDOW

#include <ncurses.h>
#include <string.h>

typedef struct node {
	node *prev;
	node *nxt;
	WINDOW *curwin;
} node;
// Linked list of node's descriptor

class WHead {
public:
	// methods
	WHead();
	~WHead();
	void appendNode( WINDOW *window);
	void delWindows();

private:
	// attributes
	char *prettyFormatStrings(char ** strings, int numstrs, int ncols);
	node *makeNode(WINDOW * window);
	node *first;
	node *last;
	int size;
};

#endif
