#include "CustomException.h"

// Constructor: menyimpan pesan error ke dalam attribute message
CustomException::CustomException(string msg) {
    message = msg;
}

// Getter: mengembalikan pesan error supaya bisa ditampilkan di catch block
string CustomException::getMessage() {
    return message;
}