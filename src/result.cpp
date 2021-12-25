#include "result.hpp"

CalculatorParameters::CalculatorParameters(){};

CalculatorParameters::CalculatorParameters(double first, double second, double third, double fourth):
    numbers{first, second, third, fourth} {}
    
CalculatorParameters::CalculatorParameters(bool option, double first, double second, double third, double fourth):
    numbers{first, second, third, fourth}, options{option} {}
    
CalculatorParameters::CalculatorParameters(bool option1, bool option2, double first, double second, double third, double fourth):
    numbers{first, second, third, fourth}, options{option1, option2} {}
    
void CalculatorParameters::setFactor(double newFactor) {
    factor = newFactor;
}

double CalculatorParameters::getFactor() const {
    return factor;
}

Result::Result(double shapeArea, int id, CalculatorParameters calcParam):
area{shapeArea}, shapeID {id}, param {calcParam}
{}
