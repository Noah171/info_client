#ifndef LLNODE
#define LLNODE

#define ADDITIONAL_COL_SPACE 4

#include <ncurses.h>
#include "media_info.hpp"

class LLNode{
	public:
		LLNode(WINDOW * super, const char * dir);
		~LLNode();
		void prettyPrintColumn(char * contents);
		char *prettyFormatStrings(char ** strings, int numstrs, int ncols);	
		LLNode * prev;
		LLNode * next;
	private:
		WINDOW * curwin;
		const char * cwd;
		int nlines;
		int ncols;
};

#endif
