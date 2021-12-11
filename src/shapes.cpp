#include "shapes.hpp"
#include <cstring>
#include <cerrno>  


namespace Shapes {
    
    AbstactShape::AbstactShape(int id, std::initializer_list<Shapes::Option> list):
    options{list}, shapeID{id}
    {}

    double AbstactShape::calculate(const CalculatorParameters&) const {
        return 100;
    }
        
    const std::vector<Option>& AbstactShape::getOptions() const {
        return options;
    }

    
}
