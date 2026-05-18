#ifndef QUEUESYSTEM_H
#define QUEUESYSTEM_H

#include <iostream>
#include <vector>
#include <string>
#include "Appointment.h"
using namespace std;

class QueueSystem {
    public:
        vector<Appointment> antrian;

        void addQueue(string id, Doctor* d);
        void showQueue();
        Doctor* getDoctorFromQueue(string id);
        void removeQueue(string id);
};

#endif
