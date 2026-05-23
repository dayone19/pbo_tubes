#include <iostream>
#include <vector> //untuk penggunaan vector (yoan)
#include <map> //untuk penggunaan map (yoan)
#include <fstream> //untuk file hendling (gretha)
#include <iomanip> //untuk atur jarak table (output)
using namespace std;

string cyanTerang    = "\033[96m";
string kuningTerang  = "\033[93m";
string hijauTerang   = "\033[92m";
string magentaTerang = "\033[95m";
string putih         = "\033[37m";
string unguMuda      = "\033[38;2;200;120;255m";
string turquoise     = "\033[38;2;64;224;208m";
string salmon        = "\033[38;2;250;128;114m";
string navy          = "\033[38;2;0;0;128m";
string lavender      = "\033[38;2;230;190;255m";
string peach         = "\033[38;2;255;218;185m";
string softPink      = "\033[38;2;255;192;203m";
string bold          = "\033[1m";
string reset         = "\033[0m";

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
        cout << magentaTerang << "\n======= DATA PASIEN =======" << reset << endl;
        cout << "Nama       : " << nama << endl;
        cout << "ID         : " << id << endl;
        cout << "Alamat     : " << alamat << endl;
        cout << "Diagnosis  : " << diagnosis << endl;
        cout << magentaTerang << "=============================" << reset << endl;
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

    double calculateFee() override { 
        return 100000; 
    }

    void displayInfo() {
        cout << hijauTerang << "======= Dokter Umum =======\n" << reset;
        cout << cyanTerang << "Nama   : " << nama << reset << endl;
    }
};

class DoctorSpecialist : public Doctor {
public:
    DoctorSpecialist(string nama, string id, string alamat)
        : Doctor(nama, id, alamat) {}

    double calculateFee() override {
         return 200000; 
    }

    void displayInfo() {
         cout << hijauTerang << "======= Dokter Spesialis =======\n" << reset;
        cout << cyanTerang << "Nama   : " << nama << reset << endl;
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
        cout << hijauTerang << "============================\n" << reset;
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
        out << magentaTerang << "Total Biaya : Rp " << b.total << reset << endl;
        return out;
    }
};


//yoan buat antrian
class Appointment {
    public:
        string patientID;
        Doctor* chosenDoctor;

        Appointment(string p, Doctor* d) {
            patientID = p;
            chosenDoctor = d;
        }

        ~Appointment() {

        }
};

//pakai teknik queue (FIFO) untuk antrian (yoan)
class QueueSystem {

    public:
    vector<Appointment> antrian;

    void addQueue(string id, Doctor* d) {
        antrian.push_back(Appointment(id, d));
    }

    void showQueue() {
        if(antrian.empty()) { 
            cout << turquoise << "+++++++++++++++++++++++++++++++++++++" << endl;
            cout << "---- " << putih << "BELUM ADA ANTRIAN HARI INI" << turquoise << " ----" << endl;
            cout << turquoise << "+++++++++++++++++++++++++++++++++++++" << endl;
        } else {
            cout << hijauTerang << "=====================================================" << endl;
            cout << " ------" << salmon << "              DAFTAR ANTRIAN           " << hijauTerang <<  "------ \n";
            cout << hijauTerang << "=====================================================" << endl;
            
            // 1. Membuat Header Tabel (No, ID Pasien, Dokter)
            // string(x, '-') digunakan untuk membuat garis horizontal pembatas sepanjang x karakter
            cout << turquoise << "+" << string(4, '-') << "+" << string(14, '-') << "+" << string(31, '-') << "+" << reset << endl;
            cout << turquoise << "| " << left << setw(3)  << "NO" 
                << "| " << setw(13) << "ID PASIEN" 
                << "| " << setw(30) << "DOKTER" << "|" << reset << endl;
            cout << turquoise << "+" << string(4, '-') << "+" << string(14, '-') << "+" << string(31, '-') << "+" << reset << endl;

            // 2. Looping untuk memasukkan data antrian ke dalam kolom tabel
            for (int i = 0; i < antrian.size(); i++) {
                cout << turquoise << "| " << reset << left << setw(3) << i + 1 
                    << turquoise << "| " << reset << setw(13) << antrian[i].patientID 
                    << turquoise << "| " << reset << setw(30) << antrian[i].chosenDoctor->getNama() 
                    << turquoise << "|" << reset << endl;
            }

            // 3. Penutup Garis Tabel
            cout << turquoise << "+" << string(4, '-') << "+" << string(14, '-') << "+" << string(31, '-') << "+" << reset << endl;
        }
    }
        


    Doctor* getDoctorFromQueue(string id) {
        for (int i = 0; i < antrian.size(); i++) {
            if (antrian[i].patientID == id) {
                return antrian[i].chosenDoctor;
            }
        }
        return NULL;
    }

    void removeQueue(string id) {
        for (int i = 0; i < antrian.size(); i++) {
            if (antrian[i].patientID == id) {
                delete antrian[i].chosenDoctor; // Hapus memory alokasi objek dokter
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

        bool exists(string id) {
            // validasi id unique
            return data.find(id) != data.end();
        }
};

//gretha buat file hendling
class FileHandler {
public:
    //untuk registrasi
    static void log(string text) {
        ofstream file("hospital_log.txt", ios::app); //app untuk menulis setelah baris terakhir di file
        file << text << endl;
        file.close();
    }

    //kalo udah di diagnosis
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

    static void readBinary() {
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

    int inputAngka(string pesan, int min, int max) {
    int angka;

    while (true) {
        cout << pesan;
        cin >> angka;

        // kalau input huruf
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << salmon
                 << "INPUT TIDAK VALID!! Masukkan angka.\n"
                 << reset;
        }

        // kalau angka di luar pilihan
        else if (angka < min || angka > max) {
            cout << salmon
                 << "INPUT TIDAK VALID!! Pilih "
                 << min << "-" << max << ".\n"
                 << reset;
        }

        // input benar
        else {
            return angka;
        }
    }
}

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

        role = inputAngka(
        navy + string("Masukkan Input [1-4] : ") + reset,
        1, 4
    );

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

                    pilihan = inputAngka(
                    navy + string("Masukkan Input [1-7] : ") + reset,
                    1, 7
                );

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
                            cin.ignore(); 
                            cout << "Masukkan Nama Dokter: ";
                            getline(cin, namaDokter);
                            cout << "Nama dokter: " << namaDokter << endl;

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

                    pilihan = inputAngka(
                    navy + string("Masukkan Input [1-4] : ") + reset,
                    1, 4
                );

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

                    pilihan = inputAngka(
                    navy + string("Masukkan Input [1-2] : ") + reset,
                    1, 2
                );

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