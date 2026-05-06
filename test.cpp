#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "color.h"
using namespace std;

/* ===============================
   ABSTRACT CLASS
================================= */
class Person {
protected:
    string nama, id, alamat;

public:
    Person(string nama, string id, string alamat) {
        this->nama = nama;
        this->id = id;
        this->alamat = alamat;
    }

    virtual void displayInfo() = 0;

    string getID() { return id; }
    string getNama() { return nama; }

    virtual ~Person() {}
};

/* ===============================
   DOCTOR
================================= */
class Doctor : public Person {
public:
    Doctor(string nama, string id, string alamat)
        : Person(nama, id, alamat) {}

    virtual double calculateFee() = 0;
};

class DoctorGeneral : public Doctor {
public:
    DoctorGeneral(string nama, string id, string alamat)
        : Doctor(nama, id, alamat) {}

    double calculateFee() override { return 100000; }

    void displayInfo() {
        cout << hijau << "===== Dokter Umum =====\n" << reset;
        cout << cyan_terang << "Nama   : " << nama << reset << endl;
        cout << cyan_terang << "ID     : " << id << reset << endl;
        cout << cyan_terang << "Alamat : " << alamat << reset << endl;
    }
};

class DoctorSpecialist : public Doctor {
public:
    DoctorSpecialist(string nama, string id, string alamat)
        : Doctor(nama, id, alamat) {}

    double calculateFee() override { return 200000; }

    void displayInfo() {
        cout << hijau << "===== Dokter Spesialis =====\n" << reset;
        cout << cyan_terang << "Nama   : " << nama << reset << endl;
        cout << cyan_terang << "ID     : " << id << reset << endl;
        cout << cyan_terang << "Alamat : " << alamat << reset << endl;
    }
};

/* ===============================
   PATIENT
================================= */
class Patient : public Person {
private:
    string diagnosis;

public:
    Patient() : Person("", "", "") {}

    Patient(string nama, string id, string alamat)
        : Person(nama, id, alamat) {}

    void setDiagnosis(string d) { diagnosis = d; }
    string getDiagnosis() { return diagnosis; }

    void displayInfo() {
        cout << "\n=== DATA PASIEN ===\n";
        cout << "Nama       : " << nama << endl;
        cout << "ID         : " << id << endl;
        cout << "Alamat     : " << alamat << endl;
        cout << "Diagnosis  : " << diagnosis << endl;
    }
};

/* ===============================
   STAFF ADMIN
================================= */
class StaffAdmin : public Person {
public:
    StaffAdmin(string nama, string id, string alamat)
        : Person(nama, id, alamat) {}

    void displayInfo() {
        cout << "=== Staff Admin ===\n";
        cout << "Nama   : " << nama << endl;
        cout << "ID     : " << id << endl;
        cout << "Alamat : " << alamat << endl;
    }
};

/* ===============================
   BILLING
================================= */
class Billing {
private:
    double total;

public:
    Billing(double t = 0) { total = t; }

    Billing operator+(Billing b) {
        return Billing(total + b.total);
    }

    friend ostream& operator<<(ostream& out, Billing b) {
        out << "Total Biaya: Rp " << b.total;
        return out;
    }
};

/* ===============================
   APPOINTMENT & ANTRIAN
================================= */
class Appointment {
public:
    string patientID;
    string doctorName;
    string Name;

    Appointment(string p, string d) {
        patientID = p;
        doctorName = d;
    }
};

class QueueSystem {
public:
    vector<string> antrian;

    void addQueue(string id) {
        antrian.push_back(id);
    }

    void showQueue() {
        if(antrian.empty()) {
            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
            cout << "----- BELUM ADA ANTRIAN HARI INI -----" << endl;
            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
        } else {
            cout << "++++++++++++++++++" << endl;
            cout << "\n--- ANTRIAN ---\n";
            cout << "++++++++++++++++++" << endl;
            for (int i = 0; i < antrian.size(); i++) {
                cout << i + 1 << ". " << antrian[i] << endl;
            }
        }
        
    }

    void removeQueue(string id) {
        for (int i = 0; i < antrian.size(); i++) {
            if (antrian[i] == id) {
                antrian.erase(antrian.begin() + i);
                break;
            }
        }
    }
};

/* ===============================
   DATABASE
================================= */
template <class T>
class Database {
public:
    map<string, T> data;

    void add(string id, T obj) {
        data[id] = obj;
    }

    T* find(string id) {
        if (data.find(id) != data.end())
            return &data[id];
        return NULL;
    }
};

/* ===============================
   FILE HANDLER
================================= */
class FileHandler {
public:
    static void log(string text) {
        ofstream file("hospital_log.txt", ios::app);
        file << text << endl;
        file.close();
    }

    static void savePatient(Patient p) {
        ofstream file("hospital_log.txt", ios::app);
        file << "[PATIENT] "
             << p.getID() << " | "
             << p.getNama() << " | "
             << p.getDiagnosis() << endl;
        file.close();
    }

    static void saveBinary(Patient p) {
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

    static void readBinary() {
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
};

/* ===============================
   EXCEPTION
================================= */
class CustomException {
private:
    string message;

public:
    CustomException(string msg) {
        message = msg;
    }

    string getMessage() {
        return message;
    }
};

/* ===============================
   MAIN
================================= */
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

                            cin.ignore(); 
                            cout << "----- REGISTRASI PASIEN  -----" << endl;
                            cout << "Nama Pasien   : "; getline(cin, nama);
                            cout << "ID Pasien     : "; getline(cin, id);
                            cout << "Alamat Pasien : "; getline(cin, alamat);

                            Patient p(nama, id, alamat);
                            db.add(id, p);

                            FileHandler::log("Registrasi: " + nama);
                            cout << "++++++++++++++++++++++++++++++++++++++" << endl;
                            
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

                            cout << "----- PEMBAYARAN  -----" << endl;
                            //billing(tunggu elysta)

                        } else if(pilihan == 4) {
                            system("cls");
                            queue.showQueue();
                            
                        } else if(pilihan == 5) {
                            system("cls");
                            cout << "============================ " << endl;
                            cout << "-- ++ DATA STAFF ADMIN ++ -- " << endl;

                            for (int i = 0; i < staffList.size(); i++) {
                                staffList[i].displayInfo();

                                cout << "============================ " << endl;
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


                            cin.ignore();
                            cout << "Diagnosis Pasien : "; getline(cin, diag);

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