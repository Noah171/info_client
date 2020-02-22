#include "LLHead.hpp"

LLHead::LLHead(){
  this->first = NULL;
  this->last = NULL;
  this->size = 0;

}// end LLHeadp

LLHead::~LLHead(){
  deleteLList();
} // end ~LLHead

// appends newnode to the linked list
void LLHead::appendNode(LLNode * newNode){
  // If it is the first node take appropriate action
  if(this->size == 0){
    this->first = newNode;
    this->last = newNode;
    newNode->next = NULL;
    newNode->prev = NULL;
  }
  // otherwise append it in the standard way
  else{
    LLNode *temp = this->last;
    this->last = newNode;
    this->last->prev = temp;
    this->last->next = NULL;
    temp->next = this->last;
  }
  this->size++;
}// end appendNode

// Deletes the linked list
void LLHead::deleteLList(){
  int llsize = this->size;
  for(int i = 0; i < llsize; ++i){
    delnode(i); 
  }
  this->size = 0;
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
  this->size--;
} // end delnode

// Simply returns the node at an index, analogous to array[i]
LLNode *LLHead::getNode(int index){
  // If the index exceeds the bounds return null
  if(index >= this->size || index < 0){ return NULL; }
  LLNode *temp = this->first;
  for(int i = 0; i < index; ++i){
    temp = temp->next;
  }
  return temp;
} // end getNode

// Prints out the contents of each node into their respective windows in curwin
void LLHead::print(){
  for(int i = 0; i < this->size; ++i ){
    LLNode *curNode = this->getNode(i);
	if(i == cursorX){
		curNode->printColumnToWindow(i);
	}
	else {
    	curNode->printColumnToWindow();
	}
  }
} // end print
// updates every node member in the linked list
void LLHead::update() {
  for(int i = 0; i < this->size; ++i ){
    LLNode *curNode = this->getNode(i);
    if(this->cursorX == i){
      curNode->updateNodeContents(this->cursorY);
    }
    else{
      curNode->updateNodeContents();
    }
  }
}// end update

// Size getter
int LLHead::getSize(){
  return this->size;
}// end getSize

void LLHead::setCursorY(int y){
  this->cursorY = y;
}// end setCursorY

void LLHead::setCursorX(int x){
  this->cursorX = x;
}// end setCursorX
