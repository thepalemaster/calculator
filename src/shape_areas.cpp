#include "shape_areas.hpp"

const double PI = 3.141592653589793;

namespace Shapes {
    
    Rectangle::Rectangle(int id): 
    AbstactShape(id, { 
        Option {"Прямоугольник", NAME},
        Option {"rect", SHORT_NAME},
        Option {"Сторона А", INPUT_DOUBLE_1},
        Option {"Сторона Б", INPUT_DOUBLE_2},
        Option {"Прямоугольник S: %f (%f × %f)", PRINTF_TEMPLATE}
    })
    {}
    
    double Rectangle::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[1];
    }
    
    Circle::Circle(int id):
    AbstactShape(id, {
        Option {"Круг", NAME},
        Option {"circle", SHORT_NAME},
        Option {"Диаметр", INPUT_DOUBLE_1},
        Option {"Круг S: %f, D: %f", PRINTF_TEMPLATE}
    })
    {}
    
    double Circle::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[0] * PI;
    }
}
