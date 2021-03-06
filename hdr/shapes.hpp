#pragma once
#include <vector>
#include "result.hpp"

namespace Shapes
{
    enum OptionType
    {
        NAME,
        SHORT_NAME,
        PRINTF_TEMPLATE,
        
        INPUT_DOUBLE_1,
        INPUT_DOUBLE_2,
        INPUT_DOUBLE_3,
        INPUT_DOUBLE_4,
        DOUBLE_DEFAULT,
        
        INPUT_BOOL_1,
        INPUT_BOOL_2,
        
        IF_BOOL_1_ON,
        IF_BOOL_2_ON,
        IF_BOTH_BOOL_ON,
        FI_BOOL_ON,

        LANGUAGE
    };
        
    struct Option
    {
        std::string text;
        OptionType type;
    };
           
    class AbstractShape {
    protected:
        const std::vector<Option> options;
    public:
        const int shapeID;
        AbstractShape(int id,  std::initializer_list<Option> list);
        virtual double calculate(const CalculatorParameters& param) const;
        const std::vector<Shapes::Option>& getOptions() const;
        virtual ~AbstractShape(){};
    };
        
}
