#include "llwindowNode.hpp"
/*
 * WNODE CODE
*/
WNode::WNode(WINDOW * win){
	this->window = win;
}
WNode::~WNode(){
	delwin(window);
}
