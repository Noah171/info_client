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
		LLNode(WINDOW * super, const char * dir, int xpos, int ypos);
		~LLNode();
		void updateNodeContents();
		void printColumnToWindow();

		const char *getCwd();
		LLNode * prev;
		LLNode * next;

	private:
		static int getContent(char *** content, const char * directory);
		static short freeContent(char *** content, int contentCount);
		static int getLongestStrIndex(char ** strs, int numStrs);
		const int symbolLen = 3; // symbol space for "|\n\r"
		const char * symbol = "|\n\r"; // What will be printed at the end of each line
		char *prettyFormatStrings(char ** strings, int numstrs);

		WINDOW * curwin;
		const char * cwd;
		char ** contents; // Array of strings which the column will contain
		// coordinates in the terminal window
		int x;
		int y;
		int nlines; // Describes the length of contents first dimension (number of lines)
		int ncols;
};

#endif
