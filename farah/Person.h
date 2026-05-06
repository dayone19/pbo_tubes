#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
using namespace std;

class Person {
    protected:
        string nama;
        string id;
        string alamat;

    public:
        Person(string nama, string id, string alamat);

        string getID();
        string getNama();

        virtual void displayInfo() = 0; 
        virtual ~Person();
};

#endif