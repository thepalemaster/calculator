#pragma once
#include <string_view>
#include <stdexcept>
#include <result.hpp>


class Calculator;


namespace Parser {
    CalculatorParameters getCalcParams(std::string_view, int paramNumber);
    double toDouble (std::string_view number);
    bool toBool (std::string_view boolean);
    int pureIntOrZero(std::string_view command) noexcept;
}
