#include "Cursor.hpp"

Cursor::Cursor(int x, int y){
  this->y = y;
  this->x = x;
}
Cursor::~Cursor(){

}
void Cursor::goDown(){
  this->y =this->y+1;
}
void Cursor::goUp(){
  this->y = this->y-n1;
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
void update(int curMaxY, int curMaxX){
  if(this->curMaxX <= this->x){
    this->x = curMaxX - 1;
  }
  if(this->curMaxY <= this->y){
    this->y = 0;
  }
  else if(this->y < 0){
    this->y = curMaxY - 1;
  }
  
}
