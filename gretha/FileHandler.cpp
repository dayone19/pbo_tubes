#include "FileHandler.h"
#include "../color.h"

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

        string id = p.getID();
        int len = id.length();
        file.write((char*)&len, sizeof(len));
        file.write(id.c_str(), len);

        string nama = p.getNama();
        len = nama.length();
        file.write((char*)&len, sizeof(len));
        file.write(nama.c_str(), len);

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
            
            // Baca ID
            file.read((char*)&len, sizeof(len));
            if (file.eof()) break;
            char id[100];
            file.read(id, len);
            id[len] = '\0';

            // Baca Nama
            file.read((char*)&len, sizeof(len));
            char nama[100];
            file.read(nama, len);
            nama[len] = '\0';

            // Baca Diagnosis
            file.read((char*)&len, sizeof(len));
            char diagnosis[100];
            file.read(diagnosis, len);
            diagnosis[len] = '\0';

            cout << "ID: " << id
                 << " | Nama: " << nama
                 << " | Diagnosis: " << diagnosis << endl;
        }
        file.close();
}

