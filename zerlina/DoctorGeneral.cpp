#include "DoctorGeneral.h"
#include "../color.h"

DoctorGeneral::DoctorGeneral(string nama, string id, string alamat)
    : Doctor(nama, id, alamat) {}

double DoctorGeneral::calculateFee() {
    return 100000; 
}

void DoctorGeneral::displayInfo() {
    cout << hijauTerang << "===== Dokter Umum =====\n" << reset;
    cout << cyanTerang << "Nama   : " << nama << reset << endl;
    cout << cyanTerang << "ID     : " << id << reset << endl;
    cout << cyanTerang << "Alamat : " << alamat << reset << endl;
}