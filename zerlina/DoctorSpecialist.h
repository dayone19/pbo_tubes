#ifndef DOCTORSPECIALIST_H
#define DOCTORSPECIALIST_H

#include "../farah/Doctor.h"
#include <iostream>
#include <string>
using namespace std;

class DoctorSpecialist : public Doctor {
    public:
        DoctorSpecialist(string nama, string id, string alamat);

        double calculateFee() override;
        void displayInfo() override;
};

#endif