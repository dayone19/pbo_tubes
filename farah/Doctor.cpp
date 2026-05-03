#include "Person.cpp"

class Doctor : public Person {
public:
    Doctor(string n, int i, string a) : Person(n, i, a) {}

    void displayInfo() override {
        cout << "Doctor\n";
        cout << "Nama: " << nama << endl;
        cout << "ID: " << id << endl;
        cout << "Alamat: " << alamat << endl;
    }
};