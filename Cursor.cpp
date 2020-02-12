#include "Cursor.hpp"

Cursor::Cursor(int x, int y){
  this->y = y;
  this->x = x;
}
Cursor::~Cursor(){

}
void Cursor::goDown(){
  this->y = (this->y+1) % this->curMaxY;
}
void Cursor::goUp(){
  this->y = (this->y-1) % this-> curMaxY;
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
}
