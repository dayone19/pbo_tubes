#ifndef CUSTOMEXCEPTION_H
#define CUSTOMEXCEPTION_H

#include <string>
using namespace std;

class CustomException {
private:
    string message;

public:
    CustomException(string msg);
    string getMessage();
};

#endif