#include <iostream>
#include <vector> //untuk penggunaan vector (yoan)
#include <map> //untuk penggunaan map (yoan)
#include <fstream> //untuk file hendling (gretha)
using namespace std;

string cyan = "\033[36m";
string kuning = "\033[33m";
string merah  = "\033[31m";
string biruTerang   = "\033[94m";
string hijauTerang  = "\033[92m";
string bold = "\033[1m";
string reset  = "\033[0m";

//farah buat class & subclass
class Person {
    public:

    string nama,
           id,
           alamat;

    //untuk input pasien saat mau registrasi
    //parameter constructor dengan initializer list we
    Person(string nama, string id, string alamat) {
        this->nama = nama;
        this->id = id;
        this->alamat = alamat;
    }
        
    string getID() {
        return id;
    }

    string getNama() {
        return nama;
    }

    virtual void displayInfo() = 0;

    virtual ~Person() {
        // cout << "Menghapus data" << endl;
    }
};

//farah 
class Patient : public Person {
    private:
    string diagnosis;
    bool diagnosed;
    bool paid;

    public:
    Patient() : Person("", "", "") {}

    Patient (string nama, string id, string alamat)
    : Person(nama, id, alamat), diagnosis("-"), diagnosed(false), paid(false) {}

    void setDiagnosis(string d) {
        diagnosis = d;
        diagnosed = true; 
    }

    string getDiagnosis() {
        return diagnosis;
    }

    string getID() {
        return id;
    }

    string getNama() {
        return nama;
    }

    bool isDiagnosed() { 
        return diagnosed; 
    }

    bool isPaid() { 
        return paid; 
    
    }

    void setPaid(bool status) { 
        paid = status; 
    }

    void displayInfo() override {
        cout << "\n===== DATA PASIEN =====\n";
        cout << "Nama       : " << nama << endl;
        cout << "ID         : " << id << endl;
        cout << "Alamat     : " << alamat << endl;
        cout << "Diagnosis  : " << diagnosis << endl;
        cout << "=======================\n";
    }

};

//zerlina buat encapsulasi & polymorphsim & subclass (inheritance) untuk dookter umum ma specialis
// zer, nama dokternya langsung dibuat di class aja
class Doctor : public Person {
    public:
    Doctor (string nama, string id, string alamat)
    : Person(nama, id, alamat){}

    virtual double calculateFee() = 0;
};

class DoctorGeneral : public Doctor {
public:
    DoctorGeneral(string nama, string id, string alamat)
        : Doctor(nama, id, alamat) {}

    double calculateFee() override { return 100000; }

    void displayInfo() {
        cout << "=== Dokter Umum ===\n";
        cout << "Nama   : " << nama << endl;
    }
};

class DoctorSpecialist : public Doctor {
public:
    DoctorSpecialist(string nama, string id, string alamat)
        : Doctor(nama, id, alamat) {}

    double calculateFee() override { return 200000; }

    void displayInfo() {
        cout << "=== Dokter Spesialis ===\n";
        cout << "Nama   : " << nama << endl;
    }
};

//farah
class StaffAdmin : public Person {
    private:
    string jabatan;

    public:
    StaffAdmin(string nama, string id, string alamat)
    : Person(nama, id, alamat), jabatan("-") {}

    void setJabatan(string x) {
        jabatan = x;
    }

    string getJabatan() {
        return jabatan;
    }

    string getID() {
        return id;
    }

    string getNama() {
        return nama;
    }

    void displayInfo() override {

        cout << "Nama       : " << nama << endl;
        cout << "ID         : " << id << endl;
        cout << "Alamat     : " << alamat << endl;
        cout << "Jabatan    : " << jabatan << endl;
        cout << "=======================\n";
    }
};

//elysta buat billing untuk hitung biaya dokter yag dibuat zer dan biaya obat nya
class Billing {
private:
    double total;

public:
    Billing(double t = 0) {
        total = t;
    }

    Billing operator+(const Billing& b) {
        return Billing(total + b.total);
    }

    friend ostream& operator<<(ostream& out, const Billing& b) {
        out << "Total Biaya : Rp " << b.total;
        return out;
    }
};


//yoan buat antrian
class Appointment {
    public:
        string patientID;
        string doctorName;

        Appointment(string p, string d) {
            patientID = p;
            doctorName = d;
        }
};

//pakai teknik queue (FIFO) untuk antrian (yoan)
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
            cout << " --- ANTRIAN ---\n";
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


//database yoan
template <typename T>
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

//gretha buat file hendling
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

//untuk try-throw-catch (yoan)
class CustomException {
    private:
        string message;

    public:
        //nyimpan pesan error nya pakai contructor we
        CustomException(string msg) {
            message = msg;
        }

        //ini message nya akan keluar, diambil dari main lewat parameter yang di CustomException
        string getMessage() {
            return message;
        }
};

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