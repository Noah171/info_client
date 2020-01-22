#include "llwindow.hpp"

WHead::WHead(){
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}

void WHead::appendNode(node *window){
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

void WHead::deleteLList(int i){
	for(int i = 0; i < this->size; ++i){
		// write getnode btw
		delnode(i);
	}
}

char *WHead::prettyFormatStrings( char ** strings, int numstrs, int ncols)
/* Pretty prints the strings into window. */
{
	/* update the windows so far just the media window */
	int curlen = 0;
	int whitespace = 0;
	int total_len = 0; //buffer's current length
	char buffer[BUFFLEN] = {};
	char * pretty_string = NULL;
	const int symbol_space = 2; // Space for "|\n"

	// Adding the strings to buffer in a "pretty" way. numstrs j is decremented for formatting reasons (order of file names looks better this way)
	for(int j = numstrs-1; j >= 0; j--){
		curlen = strnlen(strings[j], BUFFLEN);
		total_len += curlen;
		whitespace = ncols - curlen - symbol_space;

		strncat(buffer ,strings[j], BUFFLEN);

		for(int k = 0; k < whitespace; ++k){
			strncat(buffer, " ", BUFFLEN-1);
			total_len++;
		}
		// Adding in the symbols. notice the symbol, "|\n" is of length 2
		strncat(buffer ,"|\n", BUFFLEN-1);
		total_len += symbol_space;
	}
	// Add one to amount to be malloced to account for NULL byte
	pretty_string = (char *) malloc(total_len + 1);
	bzero(pretty_string, total_len+1);
	strncpy(pretty_string,buffer,total_len+1);

	return pretty_string;
}
