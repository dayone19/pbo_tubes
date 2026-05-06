#ifndef BILLING_H
#define BILLING_H

#include <iostream>
using namespace std;

class Billing {
private:
    double total;

public:
    Billing(double t = 0);

    Billing operator+(const Billing& b);

    friend ostream& operator<<(ostream& out, const Billing& b);
};

#endif