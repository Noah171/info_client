#include "Cursor.hpp"

Cursor::Cursor(WINDOW * x, int y, WINDOW * startWin){
	this->curwin = x;
	this->y = y;
}

Cursor::~Cursor(){

}

void Cursor::goDown(){
	this->y =this->y+1;
}
void Cursor::goUp(){
	this->y = this->y-1;
}
void Cursor::goRight(){
//	this->x = this->x+1;
}
void Cursor::goLeft(){

}
