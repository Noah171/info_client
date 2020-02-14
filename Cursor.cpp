#include "Cursor.hpp"

Cursor::Cursor(int x, int y){
  this->y = y;
  this->x = x;
}
Cursor::~Cursor(){

}
void Cursor::goDown(){
  this->y = (this->y+1);
}
void Cursor::goUp(){
  this->y = (this->y-1);
}
void Cursor::goRight(){
  this->x = this->x+1;
}
void Cursor::goLeft(){
  this->x = this->x-1;
}

int Cursor::getX() { return this->x; }
int Cursor::getY() { return this->y; }
// update method to update the cursor
void Cursor::update(LLHead * head){
  char inp = getch();
  // adjust cursor position based on input
  switch(inp){
  case 'h':
    this->goLeft();
    break;
  case 'l':
    this->goRight();
    break;
  case 'j':
    this->goDown();
    break;
  case 'k':
    this->goUp();
    break;
  }
  fixBounds(head);
  head->setCursorX(this->x);
  head->setCursorY(this->y);		     
}

void Cursor::fixBounds(LLHead * head){

  // adjust x bound
  if(this->x < 0)
    this->x = 0;
  else if(this->x >= head->getSize())
    this->x = head->getSize()-1;
  
  // adjust y bound
  this->y = this->y % head->getNode(this->x)->getNLines();
}
