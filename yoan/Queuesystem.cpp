#include "QueueSystem.h"
#include "../color.h"
#include "QueueSystem.h"

void QueueSystem::addQueue(string id, Doctor* d) {
    antrian.push_back(Appointment(id, d));
}

void QueueSystem::showQueue() {
    if(antrian.empty()) { 
            cout << turquoise << "+++++++++++++++++++++++++++++++++++++" << endl;
            cout << "---- " << putih << "BELUM ADA ANTRIAN HARI INI" << turquoise << " ----" << endl;
            cout << turquoise << "+++++++++++++++++++++++++++++++++++++" << endl;
        } else {
            cout << hijauTerang << "++++++++++++++++++++++++" << reset << endl;
            cout << hijauTerang << " ------" << salmon << " ANTRIAN " << hijauTerang <<  "------ \n";
            cout << hijauTerang << "++++++++++++++++++++++++" << reset << endl;
            for (int i = 0; i < antrian.size(); i++) {
                cout << i + 1 << ". ID Pasien: " << antrian[i].patientID 
                     << " | Dokter: " << antrian[i].chosenDoctor->getNama() << endl;
            }
        }
}

Doctor* QueueSystem::getDoctorFromQueue(string id) {
    for (int i = 0; i < antrian.size(); i++) {
            cout << i + 1 << ". ID Pasien: " << antrian[i].patientID 
            << " | Dokter: " << antrian[i].chosenDoctor->getNama() << endl;
    }
}

void QueueSystem::removeQueue(string id) {
    for (int i = 0; i < antrian.size(); i++) {
            if (antrian[i].patientID == id) {
                delete antrian[i].chosenDoctor; // Hapus memory alokasi objek dokter
                antrian.erase(antrian.begin() + i);
                break;
            }
        }
}
