#include "llwindow.hpp"

WHead::WHead(){
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}

void WHead::appendNode(WINDOW *window){
	node *temp = this->last;
	this->last = window;
	this->last->prev = temp;
	this->last->next = NULL;
	temp->next = this->last;
}

node *WHeadmakeNode(WINDOW *window){
	node * n = (node *) malloc(sizeof(node));
	n->curwin = window;
	return n;
}

void WHead::delWindows(){
	for(int i = 0; i < this->size; ++i){
		// write getnode btw
		delwin(getNode(i));
	}
}

char *WHEAD::prettyFormatStrings( char ** strings, int numstrs, int ncols)
/* Pretty prints the strings into window. */
{
	/* update the windows so far just the media window */
	int curlen = 0;
	int whitespace = 0;
	char buffer[BUFFLEN] = {};
	const int symbolspace = 2; // Space for "|\n"
	for(int j = numstrs-1; j >= 0; j--){
		curlen = strlen(strings[j]);
		whitespace = ncols - curlen - symbolspace;
		strcat(window,strings[j]);

		for(int k = 0; k < whitespace; ++k)
			waddstr(window, " ");
		// Adding in the symbols, which is why the symbol space is 2
		waddstr(window,"|\n");
	}
}
