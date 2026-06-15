#ifndef ZADANIE11_EXCEPTIONS_H
#define ZADANIE11_EXCEPTIONS_H

#include <stdexcept>
#include <string>

using namespace std;

class ArraySizeException : public runtime_error {
public:
    ArraySizeException(const string &msg) : runtime_error(msg) {}
};

class WrongDataException : public runtime_error {
public:
    WrongDataException(const string &msg) : runtime_error(msg) {}
};

#endif //ZADANIE11_EXCEPTIONS_H
