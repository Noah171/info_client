#ifndef LLNODE_H
#define LLNODE_H

#define ADDITIONAL_COL_SPACE 4
#define EMPTY_DIR 2 // The number of files in the directory if it is empty (. and .. are there    )
#define LLNODE_BUFFLEN 128

#include <ncurses.h>
#include <sys/stat.h> // For mkdir in getFileNames
#include <dirent.h> // for DIR and struct dir_ent in getFileNames
#include <stdio.h>
#include <cstring>
#include <cstdlib>
#include <errno.h>

class LLNode{
public:
  LLNode(WINDOW * super,char * dir, int xpos, int ypos);
  ~LLNode();
  void updateNodeContents();
  void updateNodeContents(int y);
  void printColumnToWindow();
  void printColumnToWindow(int y);
  char *getCwd();
  void setCwd(char * newcwd);
  LLNode * prev;
  LLNode * next;
  int getNLines();

private:
  static int getContent(char *** content, char * directory);
  static short freeContent(char *** content, int contentCount);
  static int getLongestStrIndex(char ** strs, int numStrs);
  const int symbolLen = 3; // symbol space for "|\n\r"
  const char * symbol = "|\n\r"; // What will be printed at the end of each line
  char *prettyFormatStrings(char ** strings, int numstrs);
  WINDOW * curwin;
  char * cwd;
  char ** contents; // Array of strings which the column will contain
  // coordinates in the terminal window
  int x;
  int y;
  int nlines; // Describes the length of contents first dimension (number of lines)
  int ncols;
};
#endif
