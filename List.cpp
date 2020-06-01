#include "List.h"     // header file
#include <cstddef>     // for NULL

List::List(): size(0), head(NULL){

}

List::List(const List& aList): size(aList.size){
    
   if (aList.head == NULL)
      head = NULL;  // original list is empty
   
   else {
      // copy first node
      head = new Friend;
      head->name = aList.head->name;
      head->id = aList.head->id;
      // copy rest of list
      Friend *newPtr = head;  // new list ptr

      for (Friend *origPtr = aList.head->friendNext; origPtr != NULL; origPtr = origPtr->friendNext){
         newPtr->friendNext = new Friend;
         newPtr = newPtr->friendNext;
         newPtr->name = origPtr->name;
         newPtr->id = origPtr->id;
      }
      newPtr->friendNext = NULL;
   }
}  // end copy constructor


List::~List() {

   while (!isEmpty())
      remove(1);

} // end destructor

bool List::isEmpty() const{

   return size == 0;

}  // end isEmpty

int List::getLength() const{

   return size;

}  // end getLength

List::Friend* List::find(int index) const {
// Locates a specified node in a linked list.
// Precondition: index is the number of the
// desired node.
// Postcondition: Returns a pointer to the 
// desired node. If index < 1 or index > the 
// number of nodes in the list, returns NULL.

   if ( (index < 1) || (index > getLength()) )
      return NULL;
   
   else{ // count from the beginning of the list
      Friend *cur = head;
      for (int skip = 1; skip < index; ++skip)
         cur = cur->friendNext;
      return cur;
   }
}  // end find

bool List::retrieve(int index, string& dataItem, int& idData) const {

   if ((index < 1) || (index > getLength()))
      return false;
   
   // get pointer to node, then data in node
   Friend *cur = find(index);
   dataItem = cur->name;
   idData = cur->id;
   
   return true;

} // end retrieve

bool List::insert(int index, string newItem, int newId) {

   int newLength = getLength() + 1;

   if ((index < 1) || (index > newLength))
      return false;

   Friend *newPtr = new Friend;
   size = newLength;
   newPtr->name = newItem;
   newPtr->id = newId;

   if (index == 1){
      newPtr->friendNext = head;
      head = newPtr;
   }
   else{
      Friend *prev = find(index-1);
      newPtr->friendNext = prev->friendNext;
      prev->friendNext = newPtr;
   }
   return true;

} // end insert

bool List::remove(int index) {

   Friend *cur;
   if ((index < 1) || (index > getLength()))
      return false;

   --size;
   if (index == 1){
      cur = head;  
      head = head->friendNext;
   }
   else{
      Friend *prev = find(index-1);
      cur = prev->friendNext;
      prev->friendNext = cur->friendNext;
   }
   cur->friendNext = NULL;
   delete cur;
   cur = NULL;
   
   return true;

}  // end remove

bool List::changeData(int index, string name, int id) {
   if ((index < 1) || (index > getLength()))
      return false;
   
   // get pointer to node, then data in node
   Friend *cur = find(index);
   cur->name = name;
   cur->id = id;
   
   return true;
}

void List::display() {
   Friend * cur = head;
   if (head == NULL) {
      cout << "No nodes!" << endl;
   }

   for (cur; cur != NULL; cur = cur->friendNext) {
      cout << "name: " << cur->name << endl;
   }
}

void List::operator=(const List& right) {
    if ( &right != this ) {
        while ( size > 0 ) {
            remove(1);
        }
        if ( right.size > 0 ) {

            head = new Friend;
            head->name = right.head->name;
            head->id = right.head->id;

            Friend * tmp = head;
            for ( Friend * curr = right.head->friendNext; curr != NULL; curr = curr->friendNext ) {
                tmp->friendNext = new Friend;
                tmp = tmp->friendNext;
                tmp->name = curr->name;
                tmp->id = curr->id;
            }
            tmp->friendNext = NULL;
        }
    }
    size = right.size;
}