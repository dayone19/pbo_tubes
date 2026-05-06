#include "TryThrowCatch.h"

// Implementasi constructor
CustomException::CustomException(string msg) {
    message = msg;
}

// Implementasi getter
string CustomException::getMessage() {
    return message;
}