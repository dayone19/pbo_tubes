#include "Doctor.cpp"

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