#include "Person.cpp"

class StaffAdmin : public Person {
    private:
    string jabatan;

    public:
        StaffAdmin(string nama, string id, string alamat) : Person(nama, id, alamat) {}

    void setJabatan(string x) {
        jabatan = x;
    }

    string getJabatan() {
        return jabatan;
    }

    string getID() {
        return id;
    }

    string getNama() {
        return nama;
    }

    void displayInfo() override {
        cout << "\n===== STAFF ADMIN =====\n";
        cout << "Nama       : " << nama << endl;
        cout << "ID         : " << id << endl;
        cout << "Alamat     : " << alamat << endl;
        cout << "Jabatan    : " << jabatan << endl;
        cout << "=======================\n";
    }
};