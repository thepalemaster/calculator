#pragma once
#include <string_view>
#include <stdexcept>
#include <result.hpp>


class Calculator;


namespace Parser {
    CalculatorParameters getCalcParams(char* input, size_t len, int paramNumber);
    //double toDouble (std::string_view number);
    double toDouble (char* input, size_t len);
    bool toBool (std::string_view boolean);
    int pureIntOrZero(const std::string& command) noexcept;
    int pureIntOrExcept(const std::string& command);
}
