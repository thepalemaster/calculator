#include "shape_areas.hpp"
#include  <cmath>

const double PI = 3.141592653589793;

namespace Shapes {
    
    Rectangle::Rectangle(int id): 
    AbstactShape(id, { 
        Option {"rect", SHORT_NAME},
        
        Option {"ru", LANGUAGE},
        Option {"Прямоугольник", NAME},
        Option {"Сторона А", INPUT_DOUBLE_1},
        Option {"Сторона Б", INPUT_DOUBLE_2},
        Option {"Прямоугольник S: %g (%g × %g)", PRINTF_TEMPLATE},
                 
        Option {"eng", LANGUAGE},
        Option {"Rectangle", NAME},
        Option {"Length", INPUT_DOUBLE_1},
        Option {"Height", INPUT_DOUBLE_2},
        Option {"Прямоугольник S: %g (%g × %g)", PRINTF_TEMPLATE}
    })
    {}
    
    double Rectangle::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[1];
    }
    
    Circle::Circle(int id):
    AbstactShape(id, {
        Option {"circle", SHORT_NAME},
        
        Option {"ru", LANGUAGE},
        Option {"Круг", NAME},
        Option {"Диаметр", INPUT_DOUBLE_1},
        Option {"Круг S: %g, D: %g", PRINTF_TEMPLATE},
        
        Option {"eng", LANGUAGE},
        Option {"Circle", NAME},
        Option {"Diameter", INPUT_DOUBLE_1},
        Option {"Circle S: %g, D: %g", PRINTF_TEMPLATE}
    })
    {}
    
    double Circle::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[0] * PI / 4;
    }
    
    Cylinder::Cylinder(int id):
    AbstactShape(id, {
        Option {"cyl", SHORT_NAME},
        
        Option {"ru", LANGUAGE},
        Option {"Цилиндр", NAME},
        Option {"Высота", INPUT_DOUBLE_1},
        Option {"Диаметр", INPUT_DOUBLE_2},
        Option {"Цилиндр S: %g, h: %g, D: %g", PRINTF_TEMPLATE},
        
        Option {"eng", LANGUAGE},
        Option {"Cylinder", NAME},
        Option {"Height", INPUT_DOUBLE_1},
        Option {"Diameter", INPUT_DOUBLE_2},
        Option {"Cylinder S: %g, h: %g, D: %g", PRINTF_TEMPLATE}
    }){}
    
    double Cylinder::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[1] * PI;
    }
    
    Sphere::Sphere(int id):
    AbstactShape(id, {
        Option {"sphere", SHORT_NAME},
        
        Option {"ru", LANGUAGE},
        Option {"Шар", NAME},
        Option {"Диаметр", INPUT_DOUBLE_1},
        Option {"Шар S: %g, D: %g", PRINTF_TEMPLATE},
        
        Option {"eng", LANGUAGE},
        Option {"Sphere", NAME},
        Option {"Diameter", INPUT_DOUBLE_1},
        Option {"Sphere S: %g, D: %g", PRINTF_TEMPLATE}
    })
    {}
    
    double Sphere::calculate(const CalculatorParameters& param) const {
        return param.numbers[0] * param.numbers[0] * PI;
    }
    
    Hexagon::Hexagon(int id):
    AbstactShape(id, {
        Option {"hex", SHORT_NAME},
        
        Option {"ru", LANGUAGE},
        Option {"Шестиугольник", NAME},
        Option {"Диаметр вписанной окружности", INPUT_DOUBLE_1},
        Option {"Описанная окружность", INPUT_BOOL_1},
        Option {"Шестиугольник S: %g, d(вписаная): %g", PRINTF_TEMPLATE},
        Option {"", IF_BOOL_1_ON},
        Option {"Шестиугольник S: %g, D(описаная): %g", PRINTF_TEMPLATE},
        Option {"Диаметр описанной окружности", INPUT_DOUBLE_1},
        Option {"", FI_BOOL_ON},
        
        Option {"eng", LANGUAGE},
        Option {"Hexagon", NAME},
        Option {"Diameter of inscribed circle", INPUT_DOUBLE_1},
        Option {"Сircumscribed circle", INPUT_BOOL_1},
        Option {"Hexagon S: %g, d(inscribed): %g", PRINTF_TEMPLATE},
        Option {"", IF_BOOL_1_ON},
        Option {"Hexagon S: %g, D(circumscribed): %g", PRINTF_TEMPLATE},
        Option {"Diameter of circumscribed circle", INPUT_DOUBLE_1},
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
        Option {"bushing", SHORT_NAME},
        Option {"ru", LANGUAGE},
        Option {"Втулка", NAME},
        Option {"Диаметр втулки", INPUT_DOUBLE_1},
        Option {"Диаметр отверстия", INPUT_DOUBLE_2},
        Option {"Высота втулки", INPUT_DOUBLE_3},
        Option {"Втулка S: %g, D: %g, d: %g, h: %g",  PRINTF_TEMPLATE},
        
        Option {"eng", LANGUAGE},
        Option {"Bushing", NAME},
        Option {"Outer diameter", INPUT_DOUBLE_1},
        Option {"Inner diameter", INPUT_DOUBLE_2},
        Option {"Height", INPUT_DOUBLE_3},
        Option {"Bushing S: %g, D: %g, d: %g, h: %g",  PRINTF_TEMPLATE},
    })
    {}
    
    double Bushing::calculate(const CalculatorParameters& param) const {
        return PI * ((param.numbers[0] * param.numbers[0] / 4 - param.numbers[1] * param.numbers[1] / 4) * 2 + 
        param.numbers[2] * (param.numbers[0] + param.numbers[1]));
    }
    
    HexPrism::HexPrism(int id):
    AbstactShape(id, {
        Option {"hexprism", SHORT_NAME},
        Option {"ru", LANGUAGE},
        Option {"Призма (N=6)", NAME},
        Option {"Диаметр вписанной окружности", INPUT_DOUBLE_1},
        Option {"Высота призмы", INPUT_DOUBLE_2},
        Option {"Описанная окружность", INPUT_BOOL_1},
        Option {"Боковые грани призмы N=6  S: %g, d: %g h: %g",  PRINTF_TEMPLATE},
        Option {"", IF_BOOL_1_ON},
        Option {"Боковые грани призмы N=6  S: %g, D: %g h: %g", PRINTF_TEMPLATE},
        Option {"Диаметр описанной окружности", INPUT_DOUBLE_1},
        Option {"", FI_BOOL_ON},
        
        Option {"eng", LANGUAGE},
        Option {"Hex Prism", NAME},
        Option {"Diameter of inscribed circle", INPUT_DOUBLE_1},
        Option {"Height of prism", INPUT_DOUBLE_2},
        Option {"Сircumscribed circle", INPUT_BOOL_1},
        Option {"Sides of hex prism S: %g, d: %g h: %g",  PRINTF_TEMPLATE},
        Option {"", IF_BOOL_1_ON},
        Option {"Sides of hex prism S: %g, D: %g h: %g", PRINTF_TEMPLATE},
        Option {"Diameter of circumscribed circle", INPUT_DOUBLE_1},
        Option {"", FI_BOOL_ON},
    })
    {}
    
    double HexPrism::calculate(const CalculatorParameters& param) const {
        if (param.options[0]) {
            return 6 * param.numbers[0] * param.numbers[0] * sqrt(3) / 2;
        } else {
            return 6 * param.numbers[0] * param.numbers[0];
        }
    }
}
