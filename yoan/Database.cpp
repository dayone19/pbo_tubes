#include "Database.h"
#include "../farah/Patient.h"

template <typename T>
    void Database<T>::add(string id, T obj) {
        data[id] = obj;
}

template <typename T>
    T* Database<T>::find(string id) {
        if (data.find(id) != data.end())
            return &data[id];
        return NULL;
}

//biar bisa dipakai untuk tipe data lain
template class Database<int>;
template class Database<string>;
template class Database<double>;
template class Database<float>;
template class Database<char>;
template class Database<Patient>;
