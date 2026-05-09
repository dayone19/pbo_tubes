#include <iostream>
using namespace std;

// Farah
#include "farah/Person.h"
#include "farah/Doctor.h"
#include "farah/Patient.h"
#include "farah/StaffAdmin.h"

// Zerlina
#include "zerlina/DoctorGeneral.h"
#include "zerlina/DoctorSpesialist.h"

// Elysta
#include "elysta/Billing.h"

// Yoan
#include "yoan/Database.h"
#include "yoan/Appointment.h"
#include "yoan/Queuesystem.h"
#include "yoan/TryThrowCatch.h"

// Gretha
#include "gretha/FileHandler.h"

int main() {
    Database<Patient> db; //objek untuk database
    QueueSystem queue; //untuk queue
    vector<Appointment> appointments; //untuk antrin

    vector<StaffAdmin> staffList; //membaca staf pakai vector
    staffList.push_back(StaffAdmin("Admin1", "A1", "Medan"));
    staffList.push_back(StaffAdmin("Admin2", "A2", "Binjai"));

    //BUAT MENU
    int role;
    int pilihan;

    do {
        cout << "============================ " << endl;
        cout << "---- ++ MEDICAL LINK ++ ---- " << endl;
        cout << "     -- LOGIN ACCESS --      " << endl;
        cout << "| 1. Staff Admin            |"  << endl;
        cout << "| 2. Doctor                 |"  << endl;
        cout << "| 3. Patient                |"  << endl;
        cout << "| 4. Exit                   |"  << endl;
        cout << "============================" << endl;

        cout << "Masukkan Input ---- : ";
        cin >> role;

        if (role == 1) {
            do {

                    cout << "============================ " << endl;
                    cout << "-- ++ STAFF ADMIN PAGE ++ -- " << endl;
                    cout << "| 1. Registrasi Pasien      |"  << endl;
                    cout << "| 2. Tambah Antrian         |"  << endl;
                    cout << "| 3. Billing                |"  << endl;
                    cout << "| 4. Lihat Antrian          |"  << endl;
                    cout << "| 5. Lihat Staff Admin      |"  << endl;
                    cout << "| 6. Lihat Aktivitas        |"  << endl;
                    cout << "| 7. Exit                   |"  << endl;
                    cout << "============================ " << endl;

                    cout << "Masukkan Input ---- : ";
                    cin >> pilihan;

                    try {

                        if(pilihan == 1) {
                            system("cls");
                            string nama, id, alamat;

                            cout << "----- REGISTRASI PASIEN  -----" << endl;
                            cout << "Nama Pasien   : "; cin >> nama;
                            cout << "ID Pasien     : "; cin >> id;
                            cout << "Alamat Pasien : "; cin >> alamat;

                            Patient p(nama, id, alamat);
                            db.add(id, p);

                            FileHandler::log("Registrasi: " + nama);
                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----    REGISTRASI BERHASIL     -----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;

                        } else if(pilihan == 2) {
                            system("cls");
                            string id;

                            cout << "----- TAMBAH ANTRIAN  -----" << endl;
                            cout << "Masukkan ID Pasien : ";
                            cin >> id;

                            Patient* p = db.find(id);

                            if (p == NULL)
                                throw CustomException("Pasien tidak ditemukan!");

                            appointments.push_back(Appointment(id, "Dokter Spesialis"));
                            queue.addQueue(id);

                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----  TAMBAH ANTRIAN BERHASIL   -----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;

                        } else if(pilihan == 3) {
                            system("cls");

                            string id;
                            cout << "Masukkan ID Pasien: ";
                            cin >> id;

                            Patient* p = db.find(id);

                            if (p == NULL)
                                throw CustomException("Pasien tidak ditemukan!");

                            if (!p->isDiagnosed()) {
                                throw CustomException("Pasien belum didiagnosis, tidak bisa melakukan pembayaran!");
                            }
                            if (p->isPaid()) {
                                throw CustomException("Pasien sudah melakukan pembayaran!");
                            }

                            Doctor* d;
                            int jenis;

                            cout << "1. Dokter Umum\n2. Spesialis\nPilih: ";
                            cin >> jenis;

                            if (jenis == 1)
                                d = new DoctorGeneral("Dr.A", "D1", "Medan");
                            else
                                d = new DoctorSpecialist("Dr.B", "D2", "Medan");

                            double biayaObat;
                            cout << "Masukkan biaya obat: ";
                            cin >> biayaObat;

                            if (biayaObat < 0)
                                throw CustomException("Biaya obat tidak valid!");

                            double biayaDokter = d->calculateFee();

                            cout << "\n=== DETAIL BIAYA ===\n";
                            cout << "Nama Pasien       : " << p->getNama() << endl;
                            cout << "Nama Dokter       : " << d->getNama() << endl;
                            cout << "Biaya Konsultasi  : Rp " << biayaDokter << endl;
                            cout << "Biaya Obat        : Rp " << biayaObat << endl;

                            Billing total = Billing(biayaDokter) + Billing(biayaObat);

                            cout << "--------------------------\n";
                            cout << total << endl;

                            p->setPaid(true);
                            queue.removeQueue(id);


                            FileHandler::log("Pembayaran pasien: " + p->getNama());

                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----    PEMBAYARAN BERHASIL     -----" << endl;
                            cout << "----  Pasien Keluar Dari Antrian  ----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;

                            delete d;

                        } else if(pilihan == 4) {
                            system("cls");
                            queue.showQueue();
                            
                        } else if(pilihan == 5) {
                            system("cls");
                            cout << "============================ " << endl;
                            cout << "-- ++ DATA STAFF ADMIN ++ -- " << endl;

                            for (int i = 0; i < staffList.size(); i++) {
                                staffList[i].displayInfo();

                            }

                        } else if(pilihan == 6) {
                            system("cls");
                            ifstream file("hospital_log.txt");
                            string line;

                            cout << "============================== " << endl;
                            cout << "-- ++ AKTIVITAS HARI INI ++ -- " << endl;

                            while (getline(file, line)) {
                                cout << line << endl;
                            }
                            file.close();
                        } 
                        
                    } catch (CustomException e) {
                        cout << "ERROR: " << e.getMessage() << endl;
                    }
                } while(pilihan != 7);

        } else if(role == 2) {

            do {
                    cout << "============================ " << endl;
                    cout << "---- ++ DOCTOR  PAGE ++ ---- " << endl;
                    cout << "| 1. Diagnosis              |"  << endl;
                    cout << "| 2. Cari Pasien            |"  << endl;
                    cout << "| 3. Lihat Rekam Medis      |"  << endl;
                    cout << "| 4. Exit                   |"  << endl;
                    cout << "============================ " << endl;

                    cout << "Masukkan Input ---- : ";
                    cin >> pilihan;

                    try {

                        if(pilihan == 1) {
                            system("cls");
                            string id, diag;

                            cout << "----- DIAGNOSIS PASIEN  -----" << endl;
                            cout << "Masukkan ID Pasien : ";
                            cin >> id;

                            Patient* p = db.find(id);

                            if (p == NULL)
                                throw CustomException("Pasien tidak ditemukan!");

                            cout << "Diagnosis Pasien : ";
                            cin >> diag;

                            p->setDiagnosis(diag);
                            FileHandler::savePatient(*p);
                            FileHandler::saveBinary(*p);

                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----   SET DIAGNOSIS BERHASIL   -----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;

                        } else if(pilihan == 2) {
                            system("cls");
                            string id;

                            cout << "----- CARI PASIEN  -----" << endl;
                            cout << "Masukkan ID Pasien : ";
                            cin >> id;

                            Patient* p = db.find(id);

                            if (p == NULL)
                                throw CustomException("Data tidak ditemukan!");

                            if (p->isPaid()) {
                                throw CustomException("Pasien sudah keluar dari karena sudah melakukan pembayaran!");
                            }


                            p->displayInfo();

                        } else if(pilihan == 3) {
                            system("cls");
                            cout << "============================ " << endl;
                            cout << "-- ++    REKAM MEDIS   ++ -- " << endl;
                            FileHandler::readBinary();
                        }

                    } catch (CustomException e) {
                        cout << "ERROR: " << e.getMessage() << endl;
                    }

            } while(pilihan != 4);

        } else if(role == 3) {

            do {
                    cout << "============================ " << endl;
                    cout << "---- ++ PATIENT PAGE ++ ---- " << endl;
                    cout << "| 1. lihat Antrian          |"  << endl;
                    cout << "| 2. Exit                   |"  << endl;
                    cout << "============================ " << endl;

                    cout << "Masukkan Input ---- : ";
                    cin >> pilihan;

                    try {

                        if(pilihan == 1) {
                            system("cls");
                            queue.showQueue();

                        } 

                    } catch (CustomException e) {
                        cout << "ERROR: " << e.getMessage() << endl;
                    }

            } while(pilihan != 2);
        }

    } while(role != 4);

    return 0;
}
