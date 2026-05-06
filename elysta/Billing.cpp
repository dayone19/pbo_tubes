#include "billing.h"
#include <iostream>
using namespace std;

Billing::Billing(double t) {
    total = t;
}

Billing Billing::operator+(const Billing& b) {
    return Billing(total + b.total);
}

ostream& operator<<(ostream& out, const Billing& b) {
    out << "\033[1;34mTotal Biaya: \033[1;32mRp "
        << b.total
        << "\033[0m";
    return out;
}