#include "llwindow.hpp"

WHead::WHead(){
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}

void WHead::appendNode(WNode *window){
	WNode *temp = this->last;
	this->last = window;
	this->last->prev = temp;
	this->last->next = NULL;
	temp->next = this->last;
}
