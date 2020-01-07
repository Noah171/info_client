#include "mouse.hpp"

Mouse::Mouse(int x, int y){
	this->x = x;
	this->y = y;
}

Mouse::~Mouse(){

}

void Mouse::goDown(){
	this->y =this->y+1;
}
void Mouse::goUp(){
	this->y = this->y-1;
}
void Mouse::goRight(){
	this->x = this->x+1;
}
