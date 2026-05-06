#include <iostream>
using namespace std;

class Person {
protected:
    string nama,
           id,
           alamat;

public:
    Person(string nama, string id, string alamat) {
        this->nama = nama;
        this->id = id;
        this->alamat = alamat;
    }
        
    string getID() {
        return id;
    }

    string getNama() {
        return nama;
    }

    virtual void displayInfo() = 0; // pure virtual

    virtual ~Person() {}
};