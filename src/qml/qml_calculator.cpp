#include "qml_calculator.hpp"

namespace CalculatorWrapper {
    Calculator calc{};
    
    Calculator& getCalculator () {
        static Calculator calc;
        return calc;
    }
}
