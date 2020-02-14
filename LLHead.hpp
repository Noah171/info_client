#ifndef LLWINDOW
#define LLWINDOW
#define LLHEAD_BUFFLEN 128

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
  int getSize();
  void update();
  void setCursorY(int y);
  void setCursorX(int x);
private:
  // attributes
  LLNode *first;
  LLNode *last;
  int size;
  int cursorX;
  int cursorY;
};
#endif
