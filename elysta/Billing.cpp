#include "billing.h"
#include <iostream>
#include "../color.h"
using namespace std;

Billing::Billing(double t) {
    total = t;
}

Billing Billing::operator+(const Billing& b) {
    return Billing(total + b.total);
}

ostream& operator<<(ostream& out, const Billing& b) {
        out << magentaTerang << "Total Biaya : Rp "
        << b.total
        << reset
        << endl;
        return out;
    }