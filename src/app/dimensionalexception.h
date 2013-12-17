#ifndef DIMENSIONALEXCEPTION_H
#define DIMENSIONALEXCEPTION_H

#include <iostream>
#include <sstream>
#include <exception>

template <class T>
class DimensionalException : public std::exception {
public:
    DimensionalException(T expected, T found, std::string dimension) {
        std::ostringstream oss;
        oss << "Expected " << expected << " " << dimension
            << ", found " << found << " " << dimension
            << ". so disappointing...";
        this->msg = oss.str();
    }

    virtual const char * what() const throw() {
        return this->msg.c_str();
    }

private:
    std::string msg;
};

#endif // DIMENSIONALEXCEPTION_H
