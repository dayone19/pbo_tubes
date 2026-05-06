#include "DoctorSpesialist.h"
#include "Color.h"

DoctorSpecialist::DoctorSpecialist(string nama, string id, string alamat)
    : Doctor(nama, id, alamat) {}

double DoctorSpecialist::calculateFee() {
    return 200000; 
}

void DoctorSpecialist::displayInfo() {
    cout << hijau << "===== Dokter Spesialis =====\n" << reset;
    cout << cyan_terang << "Nama   : " << nama << reset << endl;
    cout << cyan_terang << "ID     : " << id << reset << endl;
    cout << cyan_terang << "Alamat : " << alamat << reset << endl;
}