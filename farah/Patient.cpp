#include "Person.cpp"

class Patient : public Person {
public:
    Patient(string n, int i, string a) : Person(n, i, a) {}

    void displayInfo() override {
        cout << "Patient\n";
        cout << "Nama: " << nama << endl;
        cout << "ID: " << id << endl;
        cout << "Alamat: " << alamat << endl;
    }
};