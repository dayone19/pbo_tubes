#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <iostream>
#include <string>
using namespace std;

class CustomException {
private:
    string message;

public:
    // Constructor untuk menyimpan pesan error
    CustomException(string msg);

    // Getter untuk mengambil pesan error
    string getMessage();
};

int inputAngka(string pesan, int min, int max);

#endif