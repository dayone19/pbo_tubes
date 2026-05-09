#ifndef PATIENT_H
#define PATIENT_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class Patient : public Person {
    private:
        string diagnosis;
        bool diagnosed;
        bool paid;

    public:
        Patient(); // konstruktor default
        Patient(string nama, string id, string alamat);

        void setDiagnosis(string d);
        string getDiagnosis();

        string getID();
        string getNama();

        bool isDiagnosed();
        bool isPaid();
        void setPaid(bool status);

        void displayInfo() override;
};

#endif