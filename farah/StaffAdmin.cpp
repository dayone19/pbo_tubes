#include "StaffAdmin.h"
#include "../color.h"

StaffAdmin::StaffAdmin(string nama, string id, string alamat)
    : Person(nama, id, alamat) {}

void StaffAdmin::setJabatan(string x) {
    jabatan = x;
}

string StaffAdmin::getJabatan() {
    return jabatan;
}

string StaffAdmin::getID() {
    return id;
}

string StaffAdmin::getNama() {
    return nama;
}

void StaffAdmin::displayInfo() {

    cout << "Nama       : " << nama << endl;
    cout << "ID         : " << id << endl;
    cout << "Alamat     : " << alamat << endl;
    cout << "Jabatan    : " << jabatan << endl;
    cout << hijauTerang << "============================\n" << reset;
}