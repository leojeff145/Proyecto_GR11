#pragma once
#include <string>

class Modelo {
public:
    virtual std::string toCSV() = 0;
};