#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <iostream>
#include <string>
using namespace std;

class Appointment {
    
    public:
        string patientID;
        string doctorName;
        
        Appointment(string p, string d);

        string getPatientID();
        string getDoctorName();
};

#endif