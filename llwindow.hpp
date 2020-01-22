#ifndef LLWINDOW
#define LLWINDOW

#define BUFFLEN 100

#include <ncurses.h>
#include <string.h>
#include <cstdlib>

typedef struct node {
	node *prev;
	node *next;
	WINDOW *curwin;
} node;
// Linked list of node's descriptor

class WHead {
public:
	// methods
	WHead();
	~WHead();
	void appendNode(node *window);
	void deleteLList(int i);
	void delnode(int i);

private:
	// attributes
	char *prettyFormatStrings(char ** strings, int numstrs, int ncols);
	node *makeNode(WINDOW * window);
	node *first;
	node *last;
	int size;
};

#endif
