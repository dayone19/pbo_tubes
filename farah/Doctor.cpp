#include "Person.cpp"

class Doctor : public Person {
public:
    Doctor(string nama, string id, string alamat) : Person(nama, id, alamat) {}

    virtual double calculateFee() = 0;
};