#pragma once

#include "shapes.hpp"

namespace Shapes {
    class Rectangle: public AbstractShape {
    public:
        Rectangle(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Circle: public AbstractShape {
    public:
        Circle(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Cylinder: public AbstractShape {
    public:
        Cylinder(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Sphere: public AbstractShape {
    public:
        Sphere(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Hexagon: public AbstractShape {
    public:
        Hexagon(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Bushing: public AbstractShape {
    public:
        Bushing(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class HexPrism: public AbstractShape {
    public:
        HexPrism(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Cuboid: public AbstractShape {
    public:
        Cuboid(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
    
    class Triangle: public AbstractShape {
    public:
        Triangle(int id);
        virtual double calculate(const CalculatorParameters& param) const override;
    };
}
