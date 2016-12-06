#pragma once

#include <string>

union Value {
    int Int;
    char Char;
    float Float;
    double Double;
    bool Bool;
    std::string * Str;
};
