#include "FriendNet.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

FriendNet::FriendNet(const string fileName) {
    ifstream file(fileName);
    string lineString;
    int numberOfPeople;
    string pName;
    int friendNumber;
    if (file.is_open()) {
        getline(file, lineString);
        numberOfPeople = stoi(lineString);
        noOfFriends = numberOfPeople;
        int i = 0;
        int id;
        friendList = new List[noOfFriends];
        //cout << "num: " << numberOfPeople << endl;
        while (getline(file, lineString) && i <= numberOfPeople) {
            stringstream linestream(lineString);
            linestream >> id;
            linestream >> pName;
            linestream >> friendNumber;
            names.insert(1, pName, id);
            friendList[id].insert(1, pName, id);     //first index is always the person whose friend list is given
            int idHead = id;
            while (linestream >> id) {
                friendList[idHead].insert(friendList[idHead].getLength() + 1, " ", id);
            }
            i++;
        }
    }

    else {
        noOfFriends = 0;
        friendList = NULL;
    }

    assignNames();
}

FriendNet::FriendNet(const FriendNet& aNet) {
    if (aNet.noOfFriends > 0) {
        friendList = new List[aNet.noOfFriends];   
        //cout << "copy before for " << endl;
        names = aNet.names;
        noOfFriends = aNet.noOfFriends;
        for (int i = 0; i < noOfFriends; ++i) {
            friendList[i] = aNet.friendList[i];
        }
    }

    else {
        noOfFriends = 0;
        friendList = NULL;
    }
}

FriendNet::~FriendNet() {
    if (friendList) 
        delete [] friendList;
    friendList = NULL;
}

void FriendNet::listFriends(const string personName, const int hopNo) {
    string name;
    int id;
    int index;

    bool exist = false;
    for (int i = 1; i <= noOfFriends; i++) {
        if (names.retrieve(i, name, id)) { 
            if (name == personName) {
                exist = true;
                index = id;
                break;
            }
        }
    }
    if (!exist) {
        cout << personName << " does not exist in the list." << endl;
        return;
    }
    
    cout << "People accessible from " << personName << " within " << hopNo << " hops: ";
    if (hopNo <= 0) { 
        cout << "NOBODY" << endl;
        return;
    }

    int* visited = new int[noOfFriends];
    bool* printed = new bool[noOfFriends];
    for (int j = 0; j < noOfFriends; j++) {
        visited[j] = 0;
        printed[j] = false;
    }
    
    string namesString = "";
    for (int k = 2; k <= friendList[index].getLength(); k++) {
        //cout << "DEBUGGG" << endl;
        friendList[index].retrieve(k, name, id);
        namesString += name + ", ";
        visited[id] = 1;
        printed[id] = true;
    }
    printed[index] = true;

    for (int i = 1; i < hopNo; i++) {
        for (int j = 0; j < noOfFriends; j++) {
            if (visited[j] == i) {
                friendList[j].retrieve(1, name, id);
                int tmpId = id;
                for (int k = 2; k <= friendList[tmpId].getLength(); k++) {
                    friendList[tmpId].retrieve(k, name, id);
                    if (!printed[id]) {
                        namesString += name + ", "; 
                        visited[id] = i + 1;
                        printed[id] = true;
                    }
                }
                visited[tmpId] = 0;
            }
        }    
    }

    namesString = namesString.substr(0, namesString.size()-2);
    if (namesString == "") {
        namesString = "NOBODY";
    }
    cout << namesString << endl;
    delete [] visited;
    delete [] printed;
    //cout << endl << endl << "array " << endl;
}

void FriendNet::displayAverageDegrees() {
    if (noOfFriends == 0) {
        cout << "No connected components. No person was found in the Friend Net." << endl;
        return;
    }
    
    int* degrees = new int[noOfFriends];
    int totalComponent = 0;
    calculateComponents(degrees, totalComponent);
    
    cout << "There are " << totalComponent << " connected components. The average degrees are: " << endl;
    for (int i = 0; i < totalComponent; i++) {
        double averageLength = 0;
        int totalLength = 0;
        int number = 0;
        for (int j = 0; j < noOfFriends; j++) {
            if (degrees[j] == i) {
                totalLength += friendList[j].getLength() - 1;
                number++;
            }
        }
        averageLength = (double)totalLength / number;
        cout << "For component " << i << ": " << setprecision(3) << averageLength << endl;
    }

    delete [] degrees;
}

void FriendNet::displayDiameters() {
    if (noOfFriends == 0) {
        cout << "No connected components. No person was found in the Friend Net." << endl;
        return;
    }

    int* componentSet = new int[noOfFriends];
    int componentNumber = 0;
    calculateComponents(componentSet, componentNumber);

    int* diameters = new int[componentNumber];
    for (int i = 0; i < componentNumber; i++) {
        diameters[i] = -1;
    }

    for (int i = 0; i < componentNumber; i++) {
        int longestPath = 0;
        for (int j = 0; j < noOfFriends; j++) {
            if (componentSet[j] == i) {
                //find shortest path for each vertex
                //find max, compare with the longestPath
                int* dist = new int[noOfFriends];
                dijkstra(dist, j);
                int max = -1;
                for (int k = 0; k < noOfFriends; k++) {
                    if (dist[k] > max && dist[k] != noOfFriends) {
                        max = dist[k];
                    }
                }
                if (max > longestPath) {
                    longestPath = max;
                }
                delete [] dist;
            }
        }
        diameters[i] = longestPath;
    }

    cout << "There are " << componentNumber << " connected components. The diameters are: " << endl;
    for (int i = 0; i < componentNumber; i++) {
        cout << "For component: " << i << ": " << diameters[i] << endl;
    }
    delete [] componentSet;
    delete [] diameters;
}

void FriendNet::dijkstra(int*& dist, int source) {
    //int* dist = new int[noOfFriends];
    int* prev = new int[noOfFriends];
    bool* visited = new bool[noOfFriends];
    for (int i = 0; i < noOfFriends; i++) {
        dist[i] = noOfFriends;
        prev[i] = -1;
        visited[i] = false;
    }
    dist[source] = 0;
    visited[source] = true;

    Queue Q;
    //cout << "Source: " << source << endl;
    Q.enqueue(source);
    string name;
    int id, tmpId;
    while (!Q.isEmpty()) {
        Q.dequeue(id);
        //cout << "id in dijkstra: " << id << endl;
        for (int i = 2; i <= friendList[id].getLength(); i++) {
            friendList[id].retrieve(i, name, tmpId);
            if (!visited[tmpId]) {
                prev[tmpId] = id;
                visited[tmpId] = true;
                dist[tmpId] = dist[id] + 1;
                Q.enqueue(tmpId);
            }
        }
    }

    delete [] visited;
    delete [] prev;
}

void FriendNet::calculateComponents(int*& degrees, int& componentNumber) {
    for (int i = 0; i < noOfFriends; i++) {
        degrees[i] = -1;
    }
    
    //degrees[0] = 0;
    string name, tmpName;
    int id, tmpId;
    Stack S;
    int currentDegree = 0;

    for (int i = 0; i < noOfFriends; i++) {
        if (degrees[i] != -1) {
            continue;
        }
        friendList[i].retrieve(1, name, id);
        S.push(name, id);
        degrees[id] = currentDegree;
        while (!S.isEmpty()) {
            int j;
            S.getTop(tmpName, tmpId);
            for (j = 2; j <= friendList[tmpId].getLength(); j++) {
                friendList[tmpId].retrieve(j, name, id);
                if (degrees[id] == -1) {
                    S.push(name, id);
                    degrees[id] = currentDegree;
                    break;
                }
            }
            if (j > friendList[tmpId].getLength()) {
                S.pop();
            }
        }
        currentDegree++; 
    }
    componentNumber = currentDegree;
}

void FriendNet::assignNames() {
    string origName, name;
    int origId, id;
    for (int i = 0; i < noOfFriends; i++) {
        for (int j = 2; j <= friendList[i].getLength(); j++) {
            friendList[i].retrieve(j, name, id);
            for (int k = 1; k <= noOfFriends; k++) {
                names.retrieve(k, origName, origId);
                if (origId == id) { 
                    //cout << "origId: " << origId << " id: " << id << endl;
                    friendList[i].changeData(j, origName, origId);
                    break;
                }
            }        
        }
    }
}

// USED FOR DEBUGGING PURPOSES
// void FriendNet::display() {
//     string name1, name2;
//     int id1, id2;
//     for (int i = 0; i < noOfFriends; i++) {
//         friendList[i].retrieve(1, name1, id1);
//         cout << name1 << ": ";
//         for (int j = 2; j <= friendList[i].getLength(); j++) {
//             friendList[i].retrieve(j, name1, id1);
//             cout << name1 << " with id " << id1 << " ";
//         }
//         cout << endl;
//     }
// }