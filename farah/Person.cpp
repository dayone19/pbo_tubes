#include "Person.h"

Person::Person(string nama, string id, string alamat) {
    this->nama = nama;
    this->id = id;
    this->alamat = alamat;
}

string Person::getID() {
    return id;
}

string Person::getNama() {
    return nama;
}

Person::~Person() {
    
}