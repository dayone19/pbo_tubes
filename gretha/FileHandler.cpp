#include "FileHandler.h"

void FileHandler::log(string text) {
    ofstream file("hospital_log.txt", ios::app);
    file << text << endl;
    file.close();
}

void FileHandler::savePatient(Patient p) {
    ofstream file("hospital_log.txt", ios::app);
    file << "[PATIENT] "
         << p.getID() << " | "
         << p.getNama() << " | "
         << p.getDiagnosis() << endl;
    file.close();
}

void FileHandler::saveBinary(Patient p) {
    ofstream file("medical_record.dat", ios::binary | ios::app);

    int len = p.getNama().length();
    file.write((char*)&len, sizeof(len));
    file.write(p.getNama().c_str(), len);

    string diag = p.getDiagnosis();
    len = diag.length();
    file.write((char*)&len, sizeof(len));
    file.write(diag.c_str(), len);

    file.close();
}

void FileHandler::readBinary() {
    ifstream file("medical_record.dat", ios::binary);

    while (true) {
        int len;
        file.read((char*)&len, sizeof(len));
        if (file.eof()) break;

        char nama[100];
        file.read(nama, len);
        nama[len] = '\0';

        file.read((char*)&len, sizeof(len));
        char diagnosis[100];
        file.read(diagnosis, len);
        diagnosis[len] = '\0';

        cout << "Nama: " << nama
             << " | Diagnosis: " << diagnosis << endl;
    }

    file.close();
}

