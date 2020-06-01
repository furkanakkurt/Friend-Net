#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "FriendNet.h"
#include "List.h"
#include "Stack.h"

using namespace std;

int main() {

    FriendNet f("friend2.txt");
    FriendNet F(f);
    F.listFriends("A", 2);
    F.listFriends("K", 1);
    F.listFriends("N", 3);
    cout << endl;
    F.listFriends("BB", 2);
    F.listFriends("P", 3);
    cout << endl;
    F.displayAverageDegrees();
    cout << endl;
    F.displayDiameters();
    cout << endl;
    return 0;
}
