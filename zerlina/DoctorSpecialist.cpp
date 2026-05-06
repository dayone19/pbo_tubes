#include "DoctorSpesialist.h"

DoctorSpecialist::DoctorSpecialist(string nama, string id, string alamat)
    : Doctor(nama, id, alamat) {}

double DoctorSpecialist::calculateFee() {
    return 200000; 
}

void DoctorSpecialist::displayInfo() {
    cout << "=== Dokter Spesialis ===\n";
    cout << "Nama   : " << nama << endl;
    cout << "ID     : " << id << endl;
    cout << "Alamat : " << alamat << endl;
}