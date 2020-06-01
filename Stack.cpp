#include "Stack.h"

// default constructor
Stack::Stack() : topPtr(NULL){

}

// destructor 
Stack::~Stack(){

    // pop until stack is empty
    while (!isEmpty())
        pop();

}

bool Stack::isEmpty() const {

    return topPtr == NULL;

}

bool Stack::push(string newName, int newId) {

    // create a new node
    Friend *newPtr = new Friend;

    // set data portion  of new node
    newPtr->name = newName;
    newPtr->id = newId;
    // insert the new node
    newPtr->next = topPtr;
    topPtr = newPtr;

    return true;
}

bool Stack::pop() {

    if (isEmpty())
        return false;

    // stack is not empty; delete top
    else{   
        Friend *temp = topPtr;
        topPtr = topPtr->next;

        // return deleted node to system
        temp->next = NULL;  // safeguard
        delete temp;
        return true;
    }
}

bool Stack::getTop(string& topName, int& topId) const {

    if (isEmpty())
        return false;

    // stack is not empty; retrieve top
    else {
        topName = topPtr->name;
        topId = topPtr->id;
        return true;
    }

}
