#include "Person.cpp"

class StaffAdmin : public Person {
public:
    StaffAdmin(string n, int i, string a) : Person(n, i, a) {}

    void displayInfo() override {
        cout << "Staff Admin\n";
        cout << "Nama: " << nama << endl;
        cout << "ID: " << id << endl;
        cout << "Alamat: " << alamat << endl;
    }
};