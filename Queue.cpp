#include "Queue.h"

// default constructor
Queue::Queue() : backPtr(NULL), frontPtr(NULL){

}

// destructor
Queue::~Queue(){

    while (!isEmpty())
        dequeue();

}

bool Queue::isEmpty() const {

    return backPtr == NULL;

}

bool Queue::enqueue(int newId){
    // create a new node
    Friend *newPtr = new Friend;
    // set data portion of new node
    newPtr->id = newId;
    newPtr->next = NULL;
    // insert the new node
    if (isEmpty())   // insertion into empty queue
        frontPtr = newPtr;
    else             // insertion into nonempty queue
        backPtr->next = newPtr;
    backPtr = newPtr;  // new node is at back
    return true;
}

bool Queue::dequeue(){
    if (isEmpty())
        return false;
    else{
        // queue is not empty; remove front
        Friend *tempPtr = frontPtr;

        if (frontPtr == backPtr){   // special case
            frontPtr = NULL;
            backPtr = NULL;
        }
        else
            frontPtr = frontPtr->next;

        tempPtr->next = NULL;  // defensive strategy
        delete tempPtr;
        return true;
    }
}

bool Queue::dequeue(int& queueFrontId){
    if (isEmpty())
        return false;
    else{
        // queue is not empty; retrieve front
        //queueFrontName = frontPtr->name;
        queueFrontId = frontPtr->id;
        dequeue();  // delete front 
        return true;
    }
}

bool Queue::getFront(int& queueFrontId) const {
    if (isEmpty())
        return false;
    else {
        // queue is not empty; retrieve front
        //queueFrontName = frontPtr->name;
        queueFrontId = frontPtr->id;
        return true;
    }
}
