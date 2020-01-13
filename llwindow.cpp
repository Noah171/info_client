#include "llwindow.hpp"

WHEAD::WHEAD(){
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}

void WHEAD::appendNode(WNODE *window){
	WNODE *temp = this->last;
	this->last = window;
	this->last->prev = temp;
	this->last->next = NULL;
	temp->next = this->last;
}
