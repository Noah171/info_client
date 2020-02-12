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
  void update(LLHead * llhead);
private:
  int y;
  int x;
  int curMaxX;
  int curMaxY;
};
#endif
