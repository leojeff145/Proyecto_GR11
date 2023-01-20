#pragma once
#include <string>

class Ayuda {
public:
    static std::string uppercase(std::string str) {
        for (int i = 0; i < str.length(); i++) {
            str[i] = toupper(str[i]);
        }

        return str;
    }
};
