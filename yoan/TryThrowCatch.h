#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

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

#endif