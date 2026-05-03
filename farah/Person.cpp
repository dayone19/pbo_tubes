#include <iostream>
using namespace std;

class Person {
protected:
    string nama;
    int id;
    string alamat;

public:
    Person(string n, int i, string a) {
        nama = n;
        id = i;
        alamat = a;
    }

    virtual void displayInfo() = 0; // pure virtual

    virtual ~Person() {}
};