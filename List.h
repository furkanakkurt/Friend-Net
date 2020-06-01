// ****************************************
// Header file ListP.h for the ADT list.
// Pointer-based implementation.
//*****************************************
#ifndef __LIST_H
#define __LIST_H
#include <string>
#include <iostream>
using namespace std;
//typedef desired-type-of-list-item ListItemType;

class List{

// constructors and destructor:
public:
    List();                  // default constructor
    List(const List& aList); // copy constructor
    ~List();                 // destructor
    // list operations:
    bool isEmpty() const;

    int getLength() const;

    void operator=(const List& right);

    bool retrieve(int index, string& nameData, int& idData) const;

    bool insert(int index, string newName, int newId);

    bool remove(int index);

    bool changeData(int index, string name, int id);
    //for debugging purposes
    void display();

private:

    struct Friend{      // a node on the list
        string name; // a data item on the list
        int    id;
        Friend* friendNext;    // pointer to the next friend if any
        //Friend* netNext;       // pointer to the next person in the net if any
    };

    int       size;  // number of items in list
    Friend*   head;  // pointer to linked list 
                        // of items


    Friend *find(int index) const;
    // Returns a pointer to the index-th node
    // in the linked list
};
#endif