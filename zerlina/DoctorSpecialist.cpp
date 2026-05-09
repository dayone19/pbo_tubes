#include "DoctorSpecialist.h"
#include "../color.h"

DoctorSpecialist::DoctorSpecialist(string nama, string id, string alamat)
    : Doctor(nama, id, alamat) {}

double DoctorSpecialist::calculateFee() {
    return 200000; 
}

void DoctorSpecialist::displayInfo() {
    cout << hijauTerang << "===== Dokter Spesialis =====\n" << reset;
    cout << cyanTerang << "Nama   : " << nama << reset << endl;
    cout << cyanTerang << "ID     : " << id << reset << endl;
    cout << cyanTerang << "Alamat : " << alamat << reset << endl;
}