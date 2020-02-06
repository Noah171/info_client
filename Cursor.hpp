#ifndef CURSOR
#define CURSOR

#include <ncurses.h>
#include "LLHead.hpp"

class Cursor{

public:
  Cursor(int x, int y);
  ~Cursor();
  void goUp();
  void goDown();
  void goRight();
  void goLeft();
  int getY();
  int getX();
private:
  int y;
  int x;
};
#endif
