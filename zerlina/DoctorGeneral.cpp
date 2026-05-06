#include "DoctorGeneral.h"

DoctorGeneral::DoctorGeneral(string nama, string id, string alamat)
    : Doctor(nama, id, alamat) {}

double DoctorGeneral::calculateFee() {
    return 100000; 
}

void DoctorGeneral::displayInfo() {
    cout << "=== Dokter Umum ===\n";
    cout << "Nama   : " << nama << endl;
    cout << "ID     : " << id << endl;
    cout << "Alamat : " << alamat << endl;
}