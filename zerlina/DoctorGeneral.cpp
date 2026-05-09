#include "DoctorGeneral.h"
#include "../color.h"

DoctorGeneral::DoctorGeneral(string nama, string id, string alamat)
    : Doctor(nama, id, alamat) {}

double DoctorGeneral::calculateFee() {
    return 100000; 
}

void DoctorGeneral::displayInfo() {
    cout << hijau << "===== Dokter Umum =====\n" << reset;
    cout << cyan_terang << "Nama   : " << nama << reset << endl;
    cout << cyan_terang << "ID     : " << id << reset << endl;
    cout << cyan_terang << "Alamat : " << alamat << reset << endl;
}