#ifndef QUEUESYSTEM_H
#define QUEUESYSTEM_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

class QueueSystem {
    public:
        vector<string> antrian;

        void addQueue(string id);
        void showQueue();
        void removeQueue(string id);
};

#endif
