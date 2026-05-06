#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <map>
#include <string>
using namespace std;

template <typename T>
class Database {
    public:
        map<string, T> data;

        void add(string id, T obj);
        T* find(string id);
};

#endif
