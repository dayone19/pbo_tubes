#ifndef DOCTOR_H
#define DOCTOR_H

#include "Person.h"

class Doctor : public Person {
public:
    Doctor(string nama, string id, string alamat);

    virtual double calculateFee() = 0; // pure virtual function
};

#endif