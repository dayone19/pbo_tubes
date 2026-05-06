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

    public:
    Patient() : Person("", "", "") {}

    Patient (string nama, string id, string alamat)
    : Person(nama, id, alamat), diagnosis("-") {}

    void setDiagnosis(string d) {
        diagnosis = d;
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
        cout << "\n===== STAFF ADMIN =====\n";
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

};


//yoan buat antrian
class Appointment {

};

//pakai teknik queue (FIFO) untuk antrian
class Queuesystem {

};


//database yoan
template <class T>
class Database {

};

//gretha buat file hendling
class FileHandler {
public:
    static void log(string text) {
       
    }

    static void savePatient(Patient p) {
       
    }

    static void saveBinary(Patient p) {
    }

    static void readBinary() {

    }
};

int main() {
    
}


