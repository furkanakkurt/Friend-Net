#ifndef __FRIENDNET_H
#define __FRIENDNET_H

#include <string>
#include "List.h"
#include "Stack.h"
#include "Queue.h"

using namespace std;

class FriendNet {

public:
    FriendNet(const string fileName); // constructor
    FriendNet(const FriendNet& aNet); // copy constructor
    ~FriendNet(); // destructor
    void listFriends(const string personName, const int hopNo);
    void displayAverageDegrees();
    void displayDiameters();
    //void display(); //remove before submit
    

private:
    //functions
    void calculateComponents(int*& degrees, int& componentNumber);
    void assignNames();
    void dijkstra(int*& dist, int source);

    //private data members 
    List* friendList;
    int   noOfFriends;
    List  names;
};
#endif