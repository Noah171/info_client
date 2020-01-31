#ifndef LLNODE
#define LLNODE

#define ADDITIONAL_COL_SPACE 4
#define EMPTY_DIR 2 // The number of files in the directory if it is empty (. and .. are there    )
#define BUFFLEN 100

#include <ncurses.h>
#include <sys/stat.h> // For mkdir in getFileNames
#include <dirent.h> // for DIR and struct dir_ent in getFileNames
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>

class LLNode{
	public:
		LLNode(WINDOW * super, const char * dir);
		~LLNode();
		void updateNodeContents();
		void printColumn();

		const char *getCwd();
		LLNode * prev;
		LLNode * next;

	private:
		int getContent(char *** content, const char * directory);
		short freeContent(char *** content, int contentCount);
		int getLongestStr(char ** strs, int numStrs);
		char *prettyFormatStrings(char ** strings, int numstrs, int ncols);

		WINDOW * curwin;
		const char * cwd;
		int nlines;
		int ncols;
};

#endif
