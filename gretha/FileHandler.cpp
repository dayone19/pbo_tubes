#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <fstream>
#include <iostream>
#include <cstring>          // untuk strncpy
#include "../farah/Patient.h"   // ← ini yang penting!
using namespace std;

class FileHandler {
public:
    static void log(string text);
    static void savePatient(Patient p);
    static void saveBinary(Patient p);
    static void readBinary();
};

#endif