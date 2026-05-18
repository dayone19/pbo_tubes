#include <iostream>
#include <vector> //untuk penggunaan vector (yoan)
#include <map> //untuk penggunaan map (yoan)
#include <fstream> //untuk file hendling (gretha)
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
            cout << turquoise << "+++++++++++++++++++++++++++++++++++++" << endl;
            cout << "---- " << putih << "BELUM ADA ANTRIAN HARI INI" << turquoise << " ----" << endl;
            cout << turquoise << "+++++++++++++++++++++++++++++++++++++" << endl;
        } else {
            cout << hijauTerang << "++++++++++++++++++++++++" << reset << endl;
            cout << hijauTerang << " ------" << salmon << " ANTRIAN " << hijauTerang <<  "------ \n";
            cout << hijauTerang << "++++++++++++++++++++++++" << reset << endl;
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

    //untuk menyimpan seluruh data rekam medis
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
            nama[len] = '\0';//biar sistem tau tipe data nya string

            file.read((char*)&len, sizeof(len));
            //iftream binary gabole string, jadi dibuat char dulu untuh wadah nya
            char diagnosis[100];
            file.read(diagnosis, len);
            diagnosis[len] = '\0'; //disini baru kasih tau ke sistem kalau ini adalah string

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

                            Patient p(nama, id, alamat);
                            db.add(id, p);

                            FileHandler::log("Registrasi: " + nama);
                            cout << endl;
                            cout << turquoise << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----" << putih << "    REGISTRASI BERHASIL     " << turquoise << "-----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << reset << endl;

                        } else if(pilihan == 2) {
                            system("cls");
                            string id;

                            cout << lavender << "----- " << kuningTerang << "TAMBAH ANTRIAN" << lavender << " -----" << reset << endl;
                            cout << "Masukkan ID Pasien : ";
                            cin >> id;

                            Patient* p = db.find(id);

                            if (p == NULL)
                                throw CustomException("Pasien tidak ditemukan!");

                            appointments.push_back(Appointment(id, "Dokter Spesialis"));
                            queue.addQueue(id);

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

                            cout << unguMuda << "\n========== DETAIL BIAYA ==========\n" << reset << endl;
                            cout << "Nama Pasien       : " << p->getNama() << endl;
                            cout << "Nama Dokter       : " << d->getNama() << endl;
                            cout << "Biaya Konsultasi  : Rp " << biayaDokter << endl;
                            cout << "Biaya Obat        : Rp " << biayaObat << endl;

                            Billing total = Billing(biayaDokter) + Billing(biayaObat);

                            cout << unguMuda << "-------------------------------\n" << reset << endl;
                            cout << total << endl;

                            p->setPaid(true);
                            queue.removeQueue(id);


                            FileHandler::log("Pembayaran pasien: " + p->getNama());
 
                            cout << endl;
                            cout << turquoise << "++++++++++++++++++++++++++++++++++++++" << endl;
                            cout << "-----" << putih << "    PEMBAYARAN BERHASIL     " << turquoise << "-----" << endl;
                            cout << "----" << putih << "  Pasien Keluar Dari Antrian  " << turquoise << "----" << endl;
                            cout << "++++++++++++++++++++++++++++++++++++++" << reset << endl;

                            delete d;

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
                            cout << hijauTerang << "================================ " << endl;
                            cout << " -- ++ " << cyanTerang << "   REKAM MEDIS   " << hijauTerang << " ++ --  " << reset << endl;
                            FileHandler::readBinary();
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