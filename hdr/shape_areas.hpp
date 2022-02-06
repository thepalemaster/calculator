#pragma once

#include "shapes.hpp"

namespace Shapes {
    class Rectangle: public AbstactShape {
    public:
        Rectangle(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Circle: public AbstactShape {
    public:
        Circle(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Cylinder: public AbstactShape {
    public:
        Cylinder(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Sphere: public AbstactShape {
    public:
        Sphere(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Hexagon: public AbstactShape {
    public:
        Hexagon(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Bushing: public AbstactShape {
    public:
        Bushing(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class HexPrism: public AbstactShape {
    public:
        HexPrism(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
}
