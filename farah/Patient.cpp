#include "Patient.h"

Patient::Patient() : Person("", "", "") {
}

Patient::Patient(string nama, string id, string alamat)
    : Person(nama, id, alamat) {}

void Patient::setDiagnosis(string d) {
    diagnosis = d;
}

string Patient::getDiagnosis() {
    return diagnosis;
}

string Patient::getID() {
    return id;
}

string Patient::getNama() {
    return nama;
}

void Patient::displayInfo() {
    cout << "\n===== DATA PASIEN =====\n";
    cout << "Nama       : " << nama << endl;
    cout << "ID         : " << id << endl;
    cout << "Alamat     : " << alamat << endl;
    cout << "Diagnosis  : " << diagnosis << endl;
    cout << "=======================\n";
}