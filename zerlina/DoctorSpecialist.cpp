#include "Doctor.cpp"

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