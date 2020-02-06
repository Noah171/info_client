#include "LLHead.hpp"

LLHead::LLHead(){
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}// end LLHeadp

LLHead::~LLHead(){
	deleteLList();
} // end ~LLHead

void LLHead::appendNode(LLNode * newNode){
	if(this->size == 0){
		this->first = newNode;
		this->last = newNode;
		newNode->next = NULL;
		newNode->prev = NULL;
	}
	else{
		LLNode *temp = this->last;
		this->last = newNode;
		this->last->prev = temp;
		this->last->next = NULL;
		temp->next = this->last;
	}
	this->size++;
}// end appendNode

void LLHead::deleteLList(){
	int llsize = this->size;
	for(int i = 0; i < llsize; ++i){
		delnode(i);
	}
}// end deleteLList

// Deletes a node in the linked list of the object and index i
void LLHead::delnode(int index){
	LLNode *nodeToDelete = NULL;
	LLNode *tprev = NULL;
	LLNode *tnxt = NULL;

	 // If the index is out of bounds
	if(index >= this->size || index < 0){  return; }
	
	// Assign nodeToDelete and ensure that the node exists
	if((nodeToDelete = getNode(index)) == NULL){ return; }
	
	// if the node to delete is the first one
	if(index == 0){
		if(this->first->next != NULL){
			this->first = nodeToDelete->next;
			this->first->prev = NULL;
			delete(nodeToDelete);
		}
		else {
			this->first = NULL;
			this->last = NULL;
			delete(nodeToDelete);
		}
	}
	// If the node to be deleted is the last one
	else if(index == this->size-1){
		this->last = nodeToDelete->prev;
		this->last->next = NULL;
		delete(nodeToDelete);
	}
	// otherwise, the node is in the middle, delete appropriately
	else {
		tprev = nodeToDelete->prev;
		tnxt = nodeToDelete->next;
		tprev->next = tnxt;
		tnxt->prev =tprev;
		delete(nodeToDelete);
	}
	this->size --;
} // end delnode

// Simply returns the node at an index, analogous to array[i]
LLNode *LLHead::getNode(int index){
  
	if(index >= this->size || index < 0){ return NULL; }
	LLNode *temp = this->first;
	for(int i = 0; i < index; ++i)
		temp = temp->next;
	return temp;
} // end getNode

// Prints out the contents of each node into their respective windows in curwin
void LLHead::print(){
	for(int i = 0; i < this->size; ++i ){
		LLNode *curNode = this->getNode(i);
		curNode->updateNodeContents();
		curNode->printColumnToWindow();
	}
} // end print
