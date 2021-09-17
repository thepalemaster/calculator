#include "hdr/shape_areas.hpp"

const double PI = 3.141592653589793;

namespace Shapes {
    
    Rectangle::Rectangle(int id): AbstactShape(id) {
        options = {
            Option {"Прямоугольник", NAME},
            Option {"rect", SHORT_NAME},
            Option {"Сторона А", INPUT_DOUBLE_1},
            Option {"Сторона Б", INPUT_DOUBLE_2},
        };
    }
    
    double Rectangle::calculateArea(std::string input) {
        double a = getDouble(input);
        double b = getDouble(input);
        double factor = getFactor(input);
        return a * b * factor;
    }
    
    Circle::Circle(int id): AbstactShape(id) {
        options = {
            Option {"Круг", NAME},
            Option {"circle", SHORT_NAME},
            Option {"Диаметр", INPUT_DOUBLE_1}
        };
    }
    
    double Circle::calculateArea(std::string input) {
        double r = getDouble(input);
        double factor = getFactor(input);
        return r * r * PI * factor;
    }
}
