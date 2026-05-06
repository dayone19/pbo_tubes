#include "Person.cpp"

class Patient : public Person {
    private:
    string diagnosis;

    public:

    Patient() : Person("", "", "") {}
        
    Patient(string nama, string id, string alamat) : Person(nama, id, alamat) {}

    void setDiagnosis(string d) {
        diagnosis = d;
    }

    string getDiagnosis() {
        return diagnosis;
    }

    string getID() {
        return id;
    }

    string getNama() {
        return nama;
    }

    void displayInfo() override {
        cout << "\n===== DATA PASIEN =====\n";
        cout << "Nama       : " << nama << endl;
        cout << "ID         : " << id << endl;
        cout << "Alamat     : " << alamat << endl;
        cout << "Diagnosis  : " << diagnosis << endl;
        cout << "=======================\n";
    }
};