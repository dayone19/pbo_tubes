#include "Patient.h"
#include "../color.h"

Patient::Patient() : Person("", "", "") {
}

Patient::Patient(string nama, string id, string alamat)
    : Person(nama, id, alamat), diagnosis("-"), diagnosed(false), paid(false){}

void Patient::setDiagnosis(string d) {
    diagnosis = d;
    diagnosed = true; 
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

bool Patient::isDiagnosed() { 
    return diagnosed; 
}

bool Patient::isPaid() { 
    return paid; 
    
}
    
void Patient::setPaid(bool status) { 
    paid = status; 
}

void Patient::displayInfo() {
    cout << magentaTerang << "\n======= DATA PASIEN =======" << reset << endl;
        cout << "Nama       : " << nama << endl;
        cout << "ID         : " << id << endl;
        cout << "Alamat     : " << alamat << endl;
        cout << "Diagnosis  : " << diagnosis << endl;
        cout << magentaTerang << "===========================" << reset << endl;
}