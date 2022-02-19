#include "shapes.hpp"
#include <cstring>
#include <cerrno>  


namespace Shapes {
    
    AbstractShape::AbstractShape(int id, std::initializer_list<Shapes::Option> list):
    options{list}, shapeID{id}
    {}

    double AbstractShape::calculate(const CalculatorParameters&) const {
        return 100;
    }
        
    const std::vector<Option>& AbstractShape::getOptions() const {
        return options;
    }

    
}
