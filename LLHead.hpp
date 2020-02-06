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
	void appendNode(LLNode * node);
	void deleteLList();
	void delnode(int i);
	void print(); 
	LLNode *getNode(int i);

private:
	// attributes
	LLNode *first;
	LLNode *last;
	int size;
};
#endif
