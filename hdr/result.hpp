#pragma once
#include <string>
#include <array>

struct CalculatorParameters {
    std::array<double,4> numbers {};
    std::array<bool,2> options {};
    double factor = 1.;
    CalculatorParameters();
    CalculatorParameters(double first, double second = 0, double third = 0, double fourth = 0);
    CalculatorParameters(bool option, double first, double second = 0, double third = 0, double fourth = 0);    
    CalculatorParameters(bool option1, bool option2, double first, double second = 0, double third = 0, double fourth = 0);
    void setFactor(double);
    double getFactor() const;
};

struct Result {
    double area;
    int shapeID;
    CalculatorParameters param;
    
    Result (double shapeArea, int id, CalculatorParameters calcParam);
    
    enum action{
        NEW_ITEM,
        REMOVE_ITEM,
        CHANGE_ITEM,
        RESET
    };
};
