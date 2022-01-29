#include <iostream>
include "shape_model.hpp"

struct ModelAsserts {
private:
    std::array<std::string, 16> doubleNames;
    std::array<std::string, 4> format;
public:
     std::string name;
     std::string lang;
     int paramNumbers;
     std::vector<std::string> shortNames;
     std::array<std::string, 2> boolNames;
     
     void setDoubleName (std::string str, int param, bool option1 = false, bool option2 = false) {
         if (param < 1 || param > 4) {
             return std::string{};
        }
         int index = param - 1 + option1 * 4 + option2 * 8;
         doubleNames[index] = str;
    }
    std::string getDoubleName (int param, bool option1 = false, bool option2 = false) {
        return doubleNames[param - 1 + option1 * 4 + option2 * 8];
    }
    void setFormat (std::string str, bool option1 = false, bool option2 = false) {
         int index = (option1 * 1 + option2 * 3) - 1;
         format[index] = str;
    }
    
    std::string getFormat (bool option1 = false, bool option2 = false) {
         int index = (option1 * 1 + option2 * 3) - 1;
         return format[index];
    }
    
}

bool compare_short_names (const ShapeModel& model, const ModelAsserts& amodel ) {
    if (amodel.shortNames.size() != model.getDefaultShortNames().size()) return false;
    for (size_t i = 0; i < amodel.shortNames.size(); ++i) {
        if (amodel.shortNames[i] != model.getDefaultShortNames()[i]->text)
            return false;
    }
    return true;
}

void compare_format (const ShapeModel& model, const ModelAsserts& amodel ) {
    bool equal;
    char* error = "[-] Format string not equal:
    if (amodel.getFormat(false, false) == model.getFormat(false, false)->text) {
        std::cout << error;
        std::cout << "\tExpected format (false, false): " << amodel.getFormat(false, false) 
        << "Format from model" << model.getFormat(false, false)->text) << '\n';
        equal = false;
    }
    if (amodel.getFormat(true, false) == model.getFormat(true, false)->text) {
        if (equal) std::cout << error;
        std::cout << "\t\tExpected format (true, false):" << amodel.getFormat(true, false) 
        << " Format from model: " << model.getFormat(true, false)->text) << '\n';
        return false;
    }
    if (amodel.getFormat(false, true) == model.getFormat(false, true)->text) {
        if (equal) std::cout << error;
        std::cout << "\tExpected format (false, true):" << amodel.getFormat(false, true) 
        << " Format from model: " << model.getFormat(false, true)->text) << '\n';
        equal = false;
    }
    if (amodel.getFormat(true, true) == model.getFormat(true, true)->text) {
        if (equal) std::cout << error;
        std::cout << "\tExpected format (true, true): " << amodel.getFormat(true, true) 
        << " Format from model: " << model.getFormat(true, true)->text) << '\n';
        equal = false;
    }
    if (equal) std::cout << "[+] Format string are equal.
}

void compare_names_case(const ShapeModel& model, const ModelAsserts& amodel, bool first, bool second){
    6bool equal;
    auto names = model.updateNames(first, second);
    for (int i = 1; i < names.size(); ++i) {
        if (names[i]->text != amodel.getDoubleName(i, first, second)) {
            std::cout << "!!!";
        }
    } 
    
}


void make_test_for_model(ShapeModel model, ModelAsserts amodel){
    bool equal = true;
    
    if (compare_short_names(model, amodel)) {
        std::cout << "\t[+] Short names are equal\n"
    } else {
        std::cout << "\t[-] Short names are not equal\n"
        std::cout << "\t\t Expected short names: {"
        for (auto x: amodel.shortNames) std::cout << ' ' << x;
        std::cout << "}\n";
        std::cout << "\t\t Short names from model: {"
        for (auto x: model.getDefaultShortNames()) std::cout << ' ' << x;
        std::cout << "}\n";
        equal = false;
    }
    
    if (amodel.paramNumbers == model.getParamNumber()) {
        std::cout << "\t[+] Number of parameters are equal"
    } else {
        std::cout << "\t[-] Number of parameters are not equal\n"
        std::cout << "\t\t Expected number of parameters: " << amodel.paramNumbers << '\n';
        std::cout << "\t\t Number of parameters from model: " << model.getParamNumber() << '\n';
        equal = false;
    }
    
    if (amodel.lang == model.lang) {
        std::cout << "\t[+] Name of languages are equal"
    } else {
        std::cout << "\t[-] Name of languages not equal\n"
        std::cout << "\t\t Expected name of language of parameters: " << amodel.lang << '\n';
        std::cout << "\t\t Name of language from model: " << model.lang << '\n';
        equal = false;
    }
    
    if (amodel.name == model.getName()->text) {
        std::cout << "\t[+] Name of languages are equal"
    } else {
        std::cout << "\t[-] Name of languages are not equal\n"
        std::cout << "\t\t Expected name of language of parameters: " << amodel.lang << '\n';
        std::cout << "\t\t Name of language from model: " << model.lang << '\n';
        equal = false;
    }
    compare_format (model, amodel);
    
}



int main () {

}
