#include "Person.cpp"

class Doctor : public Person {
public:
    Doctor(string nama, string id, string alamat) : Person(nama, id, alamat) {}

    // void displayInfo() override {
    //     cout << "Doctor\n";
    //     cout << "Nama: " << nama << endl;
    //     cout << "ID: " << id << endl;
    //     cout << "Alamat: " << alamat << endl;
    // }
};