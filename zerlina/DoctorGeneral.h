#ifndef DOCTORGENERAL_H
#define DOCTORGENERAL_H

#include "Doctor.h"
#include <iostream>
#include <string>
using namespace std;

class DoctorGeneral : public Doctor {
public:
    DoctorGeneral(string nama, string id, string alamat);

    double calculateFee() override;
    void displayInfo() override;
};

#endif