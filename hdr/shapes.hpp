#pragma once
#include <vector>
#include <stdexcept>
#include <string_view>

#include "result.hpp"

/*
 * Для добавления фигуры необходимо унаследоваться от от класса AbstactShape
 * и переопределить виртуальный метод double calculate(std::string input)
 */

namespace Shapes
{
    enum OptionType
    {
        NAME,
        SHORT_NAME,
        INPUT_DOUBLE_1,
        INPUT_DOUBLE_2,
        INPUT_DOUBLE_3,
        INPUT_DOUBLE_4,
        INPUT_BOOL_1,
        INPUT_BOOL_2,
        PRINTF_TEMPLATE,
        FLOAT_DEFAULT,
        BOOL_DEFAULT,
        IF_BOOL_ON,
        FI_BOOL_ON
    };
        
    struct Option
    {
        std::string text;
        OptionType type;
    };
           
    class AbstactShape {
    private:
        int m_position = 0;
        bool m_positive = true;
        double toDouble (std::string_view number);
        bool toBool(std::string_view boolean);
        void replaceComma(char *line, int len);
        void removeSpaces(char *line, int len);
        double parseDouble(const char *stringData);
    protected:
        std::vector<Option> options;
        double getDouble (const std::string& line);
        bool getBool(const std::string& line);
        double getFactor (const std::string& line);
    public:
        const int shapeID;
        AbstactShape(int id);
        Result calculate (std::string inpitLine);
        const std::vector<Option>& getOptions() const;
        virtual double calculateArea(std::string input);
        virtual ~AbstactShape(){};
    };
        
}
