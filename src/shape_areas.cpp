#include "shape_areas.hpp"
#include  <cmath>

const double PI = 3.141592653589793;

namespace Shapes {
    
    Rectangle::Rectangle(int id): 
    AbstactShape(id, { 
        Option {"Прямоугольник", NAME},
        Option {"rect", SHORT_NAME},
        Option {"Сторона А", INPUT_DOUBLE_1},
        Option {"Сторона Б", INPUT_DOUBLE_2},
        Option {"Прямоугольник S: %g (%g × %g)", PRINTF_TEMPLATE}
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
        Option {"Круг S: %g, D: %g", PRINTF_TEMPLATE}
    })
    {}
    
    double Circle::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[0] * PI / 4;
    }
    
    Cylinder::Cylinder(int id):
    AbstactShape(id, {
        Option {"Цилиндр", NAME},
        Option {"cyl", SHORT_NAME},
        Option {"Высота", INPUT_DOUBLE_1},
        Option {"Диаметр", INPUT_DOUBLE_2},
        Option {"Цилиндр S: %g, h: %g, D: %g", PRINTF_TEMPLATE}
    }){}
    
    double Cylinder::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[1] * PI;
    }
    
    Sphere::Sphere(int id):
    AbstactShape(id, {
        Option {"Шар", NAME},
        Option {"sphere", SHORT_NAME},
        Option {"Диаметр", INPUT_DOUBLE_1},
        Option {"Шар S: %g, D: %g", PRINTF_TEMPLATE}
    })
    {}
    
    double Sphere::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[0] * PI;
    }
    
    Hexagon::Hexagon(int id):
    AbstactShape(id, {
        Option {"Шестиугольник", NAME},
        Option {"hex", SHORT_NAME},
        Option {"Диаметр", INPUT_DOUBLE_1},
        Option {"Диаметр вписаной окружности", INPUT_BOOL_1},
        Option {"Шестиугольник S: %g, D(описаная): %g", PRINTF_TEMPLATE},
        Option {"", IF_BOOL_1_ON},
        Option {"Шестиугольник S: %g, d(вписаная): %g", PRINTF_TEMPLATE},
        Option {"", FI_BOOL_ON},
    })
    {}
    
    double Hexagon::calculate(const CalculatorParameters& param) const {
        if(param.options[0]) {
            return param.numbers[0] * param.numbers[0] * 2 * sqrt(3);
        } else {
            return param.numbers[0] * param.numbers[0] * 3 * sqrt(3) / 2;
        }
    }
    
    Bushing::Bushing(int id):
    AbstactShape(id, {
        Option {"Втулка", NAME},
        Option {"bushing", SHORT_NAME},
        Option {"Диаметр втулки", INPUT_DOUBLE_1},
        Option {"Диаметр отверстия", INPUT_DOUBLE_2},
        Option {"Высота втулки", INPUT_DOUBLE_3},
        Option {"Втулка S: %g, D: %g, d: %g, h: %g",  PRINTF_TEMPLATE},
    })
    {}
    
    double Bushing::calculate(const CalculatorParameters& param) const {
        return PI * ((param.numbers[0] * param.numbers[0] / 4 - param.numbers[1] * param.numbers[1] / 4) * 2 + 
        param.numbers[2] * (param.numbers[0] + param.numbers[1]));
    }
}
