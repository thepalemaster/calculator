#include "shape_model.hpp"
#include <iostream>

struct ModelAsserts {
    std::array<std::string, 16> doubleNames;
    std::array<std::string, 4> format;
    std::array<std::string, 4> name;
    int paramNumbers;
    std::vector<std::string> shortNames;
    std::array<std::string, 2> boolNames;
    
    inline void setDoubleName (std::string str, int param) {
        if (param < 1 || param > 4) {
            return;
        }
        doubleNames[param - 1] = str;
    }
    
    inline void setDoubleNameOneOption (std::string str, int param, bool option1 = false) {
        if (param < 1 || param > 4) {
            return;
        }
        int index = param - 1 + option1 * 4;
        doubleNames[index] = str;
        doubleNames[index + 4] = doubleNames[0];
        doubleNames[index + 8] = str;
    }
    
    inline void setDoubleNameTwoOptions (std::string str, int param, bool option1 = false, bool option2 = false) {
        if (param < 1 || param > 4) {
            return;
        }
        int index = param - 1 + option1 * 4 + option2 * 8;
        doubleNames[param - 1] = str;
    }
    
     inline void setDoubleNameNoOptions (std::string str, int param) {
        if (param < 1 || param > 4) {
            return;
        }
        doubleNames[param - 1] = str;
        doubleNames[param + 4 - 1] = str;
        doubleNames[param + 8 - 1] = str;
        doubleNames[param + 12 - 1] = str;
    }
    inline std::string getDoubleName (int param, bool option1 = false, bool option2 = false) const {
        if (param < 1 || param > 4) {
            return {};
        }
        return doubleNames[param - 1 + option1 * 4 + option2 * 8];
    }
    
    inline void setFormatTwoOptions (std::string str, bool option1 = false, bool option2 = false) {
        int index = (option1 * 1 + option2 * 2);
        format[index] = str;
        
    }
    
    inline void setFormatOneOption (std::string str, bool option1 = false) {
        int index = (option1 * 1);
        format[index] = str;
        format[index + 2] = str;
    }
    
    inline void setFormat (std::string str) {
        format[0] = str;
    }
        
    
    inline std::string getFormat (bool option1 = false, bool option2 = false) const {
        int index = (option1 * 1 + option2 * 2);
        if (format[index].empty())
            return format[0];
        return format[index];
    }
    
};

void make_test_for_model(ShapeModel& model, ModelAsserts& amodel);
