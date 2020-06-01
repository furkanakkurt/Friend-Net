#ifndef __STACK_H
#define __STACK_H

#include <string>
using namespace std;

class Stack{

public:
    Stack();
    //Stack(const Stack& aStack);
    ~Stack();

    bool isEmpty() const;
    bool push(string name, int id);
    bool pop();
    //bool pop(StackItemType& stackTop);
    bool getTop(string& stackTop, int& id) const;

private:
    struct Friend {            // a node on the stack
        string name;
        int id;
        Friend    *next;        // pointer to next node
    };

   Friend *topPtr;     // pointer to first node in the stack
};
#endif