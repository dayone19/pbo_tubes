#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
#include "../farah/Doctor.h" 

using namespace std;

class Appointment {
    public:
        string patientID;
        Doctor* chosenDoctor;

        // Deklarasi Constructor
        Appointment(string p, Doctor* d);

        // Deklarasi Destructor
        ~Appointment();
};

#endif 