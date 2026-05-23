#include "TryThrowCatch.h"

// Implementasi constructor
CustomException::CustomException(string msg) {
    message = msg;
}

// Implementasi getter
string CustomException::getMessage() {
    return message;
}

// Function input angka valid
int inputAngka(string pesan, int min, int max) {
    int angka;

    while (true) {
        cout << pesan;
        cin >> angka;

        // kalau user input huruf
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');

            cout << "INPUT TIDAK VALID!! Masukkan angka.\n";
        }

        // kalau angka di luar range
        else if (angka < min || angka > max) {
            cout << "INPUT TIDAK VALID!! Pilih "
                 << min << " - " << max << ".\n";
        }

        // input benar
        else {
            cin.ignore(1000, '\n'); // bersihin enter
            return angka;
        }
    }
}