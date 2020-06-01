#ifndef __QUEUE_H
#define __QUEUE_H

#include <string>
using namespace std;

class Queue{
public:
    Queue();                     // default constructor
    //Queue(const Queue& Q);       // copy constructor
    ~Queue();                    // destructor

    // Queue operations:
    bool isEmpty() const;
    bool enqueue(int newId);
    bool dequeue();
    bool dequeue(int& queueFrontId);
    bool getFront(int& queueFrontId) const;

private:
    // The queue is implemented as a linked list with one external 
    // pointer to the front of the queue and a second external 
    // pointer to the back of the queue.

    struct Friend{
        //string  name;
        int id;
        Friend     *next;
    };
    Friend *backPtr;
    Friend *frontPtr;
};
#endif