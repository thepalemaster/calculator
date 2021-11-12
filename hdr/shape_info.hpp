#pragma once
#include <string_view>
#include <array>

class ShapeInfo {
private:
    std::array<std::string_view, 12> information;
    int aliasCount = 0;
public:
    void addName(std::string_view str);
    void addDoubleInput1(std::string_view str);
    void addDoubleInput2(std::string_view str);
    void addDoubleInput3(std::string_view str);
    void addDoubleInput4(std::string_view str);
    void addBoolInput1(std::string_view str);
    void addBoolInput2(std::string_view str);
    void addShortName(std::string_view str);
    std::string toString();
    std::string getFormatString();
    
};
