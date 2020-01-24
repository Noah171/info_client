#ifndef LLWINDOW
#define LLWINDOW

#define BUFFLEN 100

#include "LLNode.hpp"

#include <ncurses.h>
#include <string.h>
#include <cstdlib>

// Linked list of node's descriptor
class LLHead {
public:
	// methods
	LLHead();
	~LLHead();
	void appendNode(WINDOW *super, const char *dirName);
	void deleteLList();
	void delnode(int i);
	LLNode getNode(int i);

private:
	// attributes

	LLNode *first;
	LLNode *last;
	int size;
};
#endif