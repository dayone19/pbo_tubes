#include <iostream>
#include <iomanip> 
#include "color.h"
using namespace std;

// Farah
#include "farah/Person.h"
#include "farah/Doctor.h"
#include "farah/Patient.h"
#include "farah/StaffAdmin.h"

// Zerlina
#include "zerlina/DoctorGeneral.h"
#include "zerlina/DoctorSpecialist.h"

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
    vector<Appointment> appointments; //untuk antrian

    vector<StaffAdmin> staffList; //membaca staf pakai vector
    staffList.push_back(StaffAdmin("Admin1", "A1", "Medan"));
    staffList.push_back(StaffAdmin("Admin2", "A2", "Binjai"));

    //BUAT MENU
    int role;
    int pilihan;

    do {
        cout << cyanTerang << "\n ================================" << reset << endl;
        cout << cyanTerang << "|" << peach << "    -- ++ MEDICAL LINK ++ --    " << cyanTerang << "|" << reset << endl;
        cout << cyanTerang << "|" << peach << "       -- LOGIN ACCESS --       " << cyanTerang << "|" << reset << endl;
        cout << cyanTerang << "|--------------------------------|" << reset << endl;
        cout << cyanTerang << "|" << putih << " 1. Staff Admin                 " << cyanTerang << "|" << reset << endl;
        cout << cyanTerang << "|" << putih << " 2. Doctor                      " << cyanTerang << "|" << reset << endl;
        cout << cyanTerang << "|" << putih << " 3. Patient                     " << cyanTerang << "|" << reset << endl;
        cout << cyanTerang << "|" << putih << " 4. Exit                        " << cyanTerang << "|" << reset << endl;
        cout << cyanTerang << " ================================" << reset << endl;

        cout << navy << "Masukkan Input [1-4] : " << reset;
        cin >> role;

        if (role == 1) {
            system("cls");
            do {

                    cout << kuningTerang << "\n ================================ " << reset << endl;
                    cout << kuningTerang << "|" << softPink << "  -- ++ STAFF ADMIN PAGE ++ --  " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|--------------------------------|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 1. Registrasi Pasien           " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 2. Tambah Antrian              " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 3. Billing                     " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 4. Lihat Antrian               " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 5. Lihat Staff Admin           " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 6. Lihat Aktivitas             " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 7. Exit                        " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << " ================================ " << reset << endl;

                    cout << navy << "Masukkan Input [1-7] : " << reset;
                    cin >> pilihan;

                    try {

                        if(pilihan == 1) {
                            system("cls");
                            string nama, id, alamat;

                            cout << lavender << "----- " << kuningTerang << "REGISTRASI PASIEN" << lavender << " -----" << reset << endl;
                            cout << "Nama Pasien   : "; cin >> nama;
                            cout << "ID Pasien     : "; cin >> id;
                            cout << "Alamat Pasien : "; cin >> alamat;

                            if (db.exists(id)) {
                                throw CustomException("ID Pasien '" + id + "' sudah terdaftar! Gunakan ID lain.");
                            }

                            Patient p(nama, id, alamat);
                            db.add(id, p);

                            FileHandler::log("Registrasi: " + nama);
                            cout << endl;
                            cout << turquoise << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----" << putih << "    REGISTRASI BERHASIL     " << turquoise << "-----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << reset << endl;

                        } else if(pilihan == 2) {
                            system("cls");
                            string id, namaDokter;
                            int jenisDokter;

                            cout << lavender << "----- " << kuningTerang << "TAMBAH ANTRIAN" << lavender << " -----" << reset << endl;
                            cout << "Masukkan ID Pasien : ";
                            cin >> id;

                            Patient* p = db.find(id);

                            if (p == NULL)
                                throw CustomException("Pasien tidak ditemukan!");

                            cout << "Pilih Jenis Dokter:\n1. Dokter Umum\n2. Dokter Spesialis\nPilih [1-2]: ";
                            cin >> jenisDokter;
                            cout << "Masukkan Nama Dokter: ";
                            cin >> namaDokter;

                            Doctor* d = NULL;
                            if (jenisDokter == 1) {
                                d = new DoctorGeneral(namaDokter, "D-UMUM", "Rumah Sakit");
                            } else if (jenisDokter == 2) {
                                d = new DoctorSpecialist(namaDokter, "D-SPESIALIS", "Rumah Sakit");
                            } else {
                                throw CustomException("Pilihan dokter tidak valid!");
                            }

                            queue.addQueue(id, d);

                            cout << endl;
                            cout << turquoise << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----" << putih << "  TAMBAH ANTRIAN BERHASIL   " << turquoise << "-----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << reset << endl;

                        } else if(pilihan == 3) {
                            system("cls");

                            string id;
                            cout << lavender << "Masukkan ID Pasien: " << reset;
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

                            // Mengambil data dokter langsung dari sistem antrian (Tanpa Input Ulang)
                            Doctor* d = queue.getDoctorFromQueue(id);
                            if (d == NULL) {
                                throw CustomException("Data dokter untuk pasien ini tidak ditemukan di antrian!");
                            }

                            double biayaObat;
                            cout << "Masukkan biaya obat: ";
                            cin >> biayaObat;

                            if (biayaObat < 0)
                                throw CustomException("Biaya obat tidak valid!");

                            double biayaDokter = d->calculateFee();

                            cout << unguMuda << "\n========== DETAIL BIAYA ==========\n" << reset << endl;
                            cout << "Nama Pasien       : " << p->getNama() << endl;
                            cout << "Nama Dokter       : " << d->getNama() << endl;
                            cout << "Biaya Konsultasi  : Rp " << biayaDokter << endl;
                            cout << "Biaya Obat        : Rp " << biayaObat << endl;

                            Billing total = Billing(biayaDokter) + Billing(biayaObat);

                            cout << unguMuda << "-------------------------------\n" << reset << endl;
                            cout << total << endl;

                            p->setPaid(true);

                            FileHandler::log("Pembayaran pasien: " + p->getNama());
 
                            cout << endl;
                            cout << turquoise << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----" << putih << "    PEMBAYARAN BERHASIL     " << turquoise << "-----" << endl;
                            cout << "----" << putih << "  Pasien Keluar Dari Antrian  " << turquoise << "----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << reset << endl;

                            queue.removeQueue(id);

                        } else if(pilihan == 4) {
                            system("cls");
                            queue.showQueue();
                            
                        } else if(pilihan == 5) {
                            system("cls");
                            cout << hijauTerang << "============================ " << endl;
                            cout << hijauTerang << "-- ++ " << salmon << "DATA STAFF ADMIN" << hijauTerang << " ++ --" << reset << endl;

                            for (int i = 0; i < staffList.size(); i++) {
                                staffList[i].displayInfo();

                            }

                        } else if(pilihan == 6) {
                            system("cls");
                            ifstream file("hospital_log.txt");
                            string line;

                            cout << hijauTerang << "============================== " << endl;
                            cout << hijauTerang << "-- ++ " << salmon << "AKTIVITAS HARI INI" << hijauTerang << " ++ -- " << reset << endl;

                            while (getline(file, line)) {
                                cout << line << endl;
                            }
                            file.close();
                        } else if(pilihan == 7) {
                            system("cls");
                        }
                        
                    } catch (CustomException e) {
                        cout << "ERROR: " << e.getMessage() << endl;
                    }
                } while(pilihan != 7);

        } else if(role == 2) {
            system("cls");
            do {
                    cout << kuningTerang << "\n ============================ " << reset << endl;
                    cout << kuningTerang << "|" << peach << "  -- ++ DOCTOR  PAGE ++ --  " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|----------------------------|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 1. Diagnosis               " << kuningTerang << "|"  << endl;
                    cout << kuningTerang << "|" << putih << " 2. Cari Pasien             " << kuningTerang << "|"  << endl;
                    cout << kuningTerang << "|" << putih << " 3. Lihat Rekam Medis       " << kuningTerang << "|"  << endl;
                    cout << kuningTerang << "|" << putih << " 4. Exit                    " << kuningTerang << "|"  << endl;
                    cout << kuningTerang << " ============================ " << reset << endl;

                    cout << navy << "Masukkan Input [1-4] : " << reset;
                    cin >> pilihan;

                    try {

                        if(pilihan == 1) {
                            system("cls");
                            string id, diag;

                            cout << lavender << "----- DIAGNOSIS PASIEN  -----" << reset << endl;
                            cout << "Masukkan ID Pasien : ";
                            cin >> id;

                            Patient* p = db.find(id);

                            if (p == NULL)
                                throw CustomException("Pasien tidak ditemukan!");

                            if (p->isDiagnosed()) {
                                throw CustomException("Pasien sudah didiagnosis sebelumnya!");
                            }

                            cout << "Diagnosis Pasien : ";
                            cin >> diag;

                            p->setDiagnosis(diag);
                            FileHandler::savePatient(*p);
                            FileHandler::saveBinary(*p);

                            cout << endl;
                            cout << turquoise << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----" << putih << "   SET DIAGNOSIS BERHASIL   " << turquoise << "-----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << reset << endl;

                        } else if(pilihan == 2) {
                            system("cls");
                            string id;

                            cout << lavender << "----- CARI PASIEN  -----" << reset << endl;
                            cout << "Masukkan ID Pasien : ";
                            cin >> id;

                            Patient* p = db.find(id);

                            if (p == NULL)
                                throw CustomException("Data tidak ditemukan!");

                            if (p->isPaid()) {
                                throw CustomException("Pasien sudah keluar dari rumah sakit karena sudah melakukan pembayaran!");
                            }


                            p->displayInfo();

                        } else if(pilihan == 3) {
                            system("cls");

                            cout << hijauTerang << "=====================================================================================" << endl;
                            cout << " -- ++ " << cyanTerang << "                           REKAM MEDIS    PASIEN                       " << hijauTerang << " ++ --  " << reset << endl;
                            cout << hijauTerang << "=====================================================================================" << endl;

                            // buka file binary
                            ifstream file("medical_record.dat", ios::binary);

                            if (!file) {
                                cout << magentaTerang << "[!] Belum ada data rekam medis yang tersimpan." << reset << endl;
                            } else {
                                cout << cyanTerang
                                    << "+" << string(20, '-')
                                    << "+" << string(30, '-')
                                    << "+" << string(32, '-')
                                    << "+" << reset << endl;

                                cout << cyanTerang
                                    << "| " << left << setw(18) << "ID PASIEN"
                                    << "| " << left << setw(28) << "NAMA PASIEN"
                                    << "| " << left << setw(33) << "DIAGNOSIS"
                                    << "|" << reset << endl;

                                cout << cyanTerang
                                    << "+" << string(20, '-')
                                    << "+" << string(30, '-')
                                    << "+" << string(32, '-')
                                    << "+" << reset << endl;

                                bool adaData = false;

                                while (true) {

                                    int len;

                                    file.read((char*)&len, sizeof(len));

                                    if (file.eof())
                                        break;

                                    adaData = true;

                                    char idPasien[100];
                                    file.read(idPasien, len);
                                    idPasien[len] = '\0';

                                    file.read((char*)&len, sizeof(len));

                                    char nama[100];
                                    file.read(nama, len);
                                    nama[len] = '\0';

                                    file.read((char*)&len, sizeof(len));

                                    char diagnosis[100];
                                    file.read(diagnosis, len);
                                    diagnosis[len] = '\0';

                                    string diagText = diagnosis;

                                    if (diagText.length() > 28) {
                                        diagText = diagText.substr(0, 27) + ".";
                                    }

                                    cout << cyanTerang
                                         << "| " << reset << left << setw(18) << idPasien
                                         << cyanTerang
                                         << "| " << reset << left << setw(28) << nama
                                         << cyanTerang
                                         << "| " << reset << left << setw(33) << diagText
                                         << cyanTerang
                                         << "|" << reset << endl;
                                }

                                cout << cyanTerang
                                    << "+" << string(20, '-')
                                    << "+" << string(30, '-')
                                    << "+" << string(32, '-')
                                    << "+" << reset << endl;

                                if (!adaData) {
                                    cout << magentaTerang << "[!] File rekam medis kosong." << reset << endl;
                                }

                                file.close();
                            }
                            
                            
                        } else if(pilihan == 4) {
                            system("cls");
                        }

                    } catch (CustomException e) {
                        cout << "ERROR: " << e.getMessage() << endl;
                    }

            } while(pilihan != 4);

        } else if(role == 3) {
            system("cls");
            do {
                    cout << kuningTerang << "\n ============================ " << reset << endl;
                    cout << kuningTerang << "|" << peach << "  -- ++ PATIENT PAGE ++ --  " << kuningTerang << "|" << reset << endl;
                    cout << kuningTerang << "|----------------------------|" << reset << endl;
                    cout << kuningTerang << "|" << putih << " 1. Lihat Antrian           " << kuningTerang << "|"  << endl;
                    cout << kuningTerang << "|" << putih << " 2. Exit                    " << kuningTerang << "|"  << endl;
                    cout << kuningTerang << " ============================ " << reset << endl;

                    cout << navy << "Masukkan Input [1-2] : " << reset;
                    cin >> pilihan;

                    try {

                        if(pilihan == 1) {
                            system("cls");
                            queue.showQueue();

                        } else if(pilihan == 2) {
                            system("cls");
                        }

                    } catch (CustomException e) {
                        cout << "ERROR: " << e.getMessage() << endl;
                    }

            } while(pilihan != 2);
        } else if(role == 4) {
         
        }

    } while(role != 4);

    return 0;
}