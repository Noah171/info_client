#include "LLHead.hpp"

LLHead::LLHead(){
	this->first = NULL;
	this->last = NULL;
	this->size = 0;
}// end LLHead

LLHead::~LLHead(){
	deleteLList();
}

void LLHead::appendNode(LLNode * newNode){
	if(size == 0){
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
	size++;
}// end appendNode

void LLHead::deleteLList(){
	int llsize = this->size;
	for(int i = 0; i < llsize; ++i){
		// write getnode btw
		delnode(i);
	}
}// end deleteLList

void LLHead::delnode(int index){
	LLNode *nodeToDelete = NULL;
	LLNode *tprev = NULL;
	LLNode *tnxt = NULL;

	if(index >= size || index < 0){
		return;
	}
	// Assign nodeToDelete and ensure that the node exists
	if((nodeToDelete = getNode(index)) == NULL){
		return;
	}
	
	// if the node to delete is the first one
	if(index == 0){
		if(this->first->next != NULL){
			this->first = nodeToDelete->next;
			this->first->prev = NULL;
			delete(nodeToDelete);
		}
		else{
			this->first = NULL;
			this->last = NULL;
			delete(nodeToDelete);
		}
	}
	// If the node to be deleted is the last one
	else if(index == size-1){
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

	size --;

} // end delnode

LLNode *LLHead::getNode(int index){

	if(index >= this->size || index < 0){
		return NULL;
	}
	LLNode *temp = this->first;
	for(int i = 0; i < index; ++i)
		temp = temp->next;
	return temp;
} // end getNode

void LLHead::print(){
	for(int i = 0; i < size; ++i ){
		this->getNode(i)->printColumn();
		printf("%s\n", this->getNode(i)->getCwd());
	}
} // end print
