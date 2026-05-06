#ifndef STAFFADMIN_H
#define STAFFADMIN_H

#include "Person.h"
#include <iostream>
#include <string>
using namespace std;

class StaffAdmin : public Person {
private:
    string jabatan;

public:
    StaffAdmin(string nama, string id, string alamat);

    void setJabatan(string x);
    string getJabatan();

    string getID();
    string getNama();

    void displayInfo() override;
};

#endif