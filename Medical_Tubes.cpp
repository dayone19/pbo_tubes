#include <iostream>
#include <vector> //untuk penggunaan vector
#include <map> //untuk penggunaan map
#include <fstream> //untuk file hendling
using namespace std;

//farah buat class & subclass
class Person {
    public:

    string nama,
           id,
           alamat;

    //untuk input pasien saat mau registrasi
    //parameter constructor dengan initializer list we
    Person(string nama, string id, string alamat) 
        : nama(nama), id(id), alamat(alamat) {}
    

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
    
    //diplay infonya zer
    // void displayInfo() override {
    //     cout << "\n=== DOKTER SPESIALIS ===\n";
    //     cout << "Nama       : " << nama << endl;
    //     cout << "ID         : " << id << endl;
    //     cout << "Alamat     : " << alamat << endl;
    //     cout << "Biaya      : Rp " << calculateFee() << endl;
    //     cout << "========================\n";
    // }
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


