#pragma once

#include "shapes.hpp"

namespace Shapes {
    class Rectangle: public AbstactShape {
    public:
        Rectangle(int id);
        virtual double calculateArea (std::string input) override;
    };
    
    class Circle: public AbstactShape {
    public:
        Circle(int id);
        virtual double calculateArea (std::string input) override;
    };
}
