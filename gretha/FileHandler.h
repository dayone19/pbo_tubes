#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include "Patient.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class FileHandler {
public:
    static void log(string text);
    static void savePatient(Patient p);
    static void saveBinary(Patient p);
    static void readBinary();
};

#endif