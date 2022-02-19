#include "model_test.hpp"



void compare_short_names (const ShapeModel& model, const ModelAsserts& amodel ) {
    const char* error = "[-] Short names of shape not compare\n";
    bool equal = true;
    if (amodel.shortNames.size() != model.getDefaultShortNames().size()) {
        std::cout << error << "\t Number of short names in model differs from expected\n";
    } else {
        for (size_t i = 0; i < amodel.shortNames.size(); ++i) {
            if (amodel.shortNames[i] != model.getDefaultShortNames()[i]->text) {
                if (equal) {
                    std::cout << error;
                    equal = false;
                }
                std::cout << "\t Short names are not equal. Expected: " << amodel.shortNames[i] << ". From model: " << model.getDefaultShortNames()[i]->text << '\t';
            }
        }
        if (equal) {
            std::cout << "[+] Short names of shape are equal\n";
        }
    }
}

void compare_numbers_names_case (const ShapeModel& model, const ModelAsserts& amodel) {
    bool equal = true;
    const char* error = "[-] Number names are not equal (for options)\n";
    bool first;
    bool second;
    int i = 1;
    while (i < 4) {
        first = i & 1;
        second = i > 1;
        auto names = model.updateNames(first, second);
        for (size_t index = 0; index < 4; ++index) {
            if (amodel.doubleNames[index + i * 4].empty() ^ !names[index + 1]) {
                if (equal) {
                    std::cout << error;
                    equal = false;
                }
                std::cout << "\tFor index " << index << ", option 1: " << std::boolalpha << first
                << ", option 2: " << std::boolalpha << second; 
                if (!names[index + 1]) {
                    std::cout << ", name expected: " << amodel.doubleNames[index + i * 4] << ", but name from model are empty.\n";
                } else {
                    std::cout << ", unexpected name from model: " << names[index + 1]->text <<'\n';
                }
                
            } else if (names[index + 1] && (names[index + 1]->text != amodel.doubleNames[index + i * 4])) {
                if (equal) {
                    std::cout << error;
                    equal = false;
                }
                std::cout << "\tFor index " << index << ", option 1: " << std::boolalpha << first
                << ", option 2: " << std::boolalpha << second << " Name expected: " << amodel.doubleNames[index + i * 4] << "\n\t"
                << " Name from model: " << names[index + 1]->text;
            }
        }
        ++i;
    }
    if (equal) {
        std::cout << "[+] Number names are equal (for options)\n";
    }
}


void compare_numbers_names (const ShapeModel& model, const ModelAsserts& amodel) {
    bool equal = true;
    const char* error = "[-] Number names are not equal\n";
    auto names = model.getParamNames();;
    for (size_t index = 0; index < 4; ++index) {
        if (amodel.doubleNames[index].empty() ^ !names[index + 1]) {
            if (equal) {
                std::cout << error;
                equal = false;
            }
            std::cout << "\tFor number number " << index + 1;
            if (!names[index + 1]) {
                std::cout << ", name from model are empty, but expected name: " << amodel.doubleNames[index] <<'\n';
            } else {
                std::cout << ", name expected: " << amodel.doubleNames[index] << ", but name from model are empty.\n";
            }
        } else if (names[index + 1] && (names[index + 1]->text != amodel.doubleNames[index])) {
            if (equal) {
                std::cout << error;
                equal = false;
            }
            std::cout << "\tFor number number " << index + 1 << " Name expected: " << amodel.doubleNames[index]
            << " Name from model: " << names[index + 1]->text << '\n';
        }
    }
    if (equal) {
        std::cout << "[+] Number names are equal\n";
    }
}

void compare_option_names(const ShapeModel& model, const ModelAsserts& amodel) {
    bool equal = true;
    const char* error = "[-] Option names are not equal\n";
    auto names = model.getParamNames();
    if (!(amodel.boolNames[0].empty() && !names[5]) && amodel.boolNames[0] != names[5]->text) {
        std::cout << error;
        equal = false;
        std::cout << "\tOption 1. Name expected: " << amodel.boolNames[0]
                    << " Name from model: " << names[5]->text << '\n';
    }
    if (!(amodel.boolNames[1].empty() && !names[6]) && amodel.boolNames[1] != names[6]->text) {
        if (equal) {
            std::cout << error;
            equal = false;
        }
        std::cout << "\tOption 2. Name expected: " << amodel.boolNames[1]
        << " Name from model: " << names[6]->text << '\n';
    }
    if (equal) {
        std::cout << "[+] Option names are equal\n";
    }
}

void compare_format (const ShapeModel& model, const ModelAsserts& amodel) {
    bool equal = true;
    const char* error = "[-] Format strings are not equal:\n";
    if (amodel.getFormat(false, false) != model.getFormat(false, false)->text) {
        std::cout << error;
        std::cout << "\tExpected format (false, false): " << amodel.getFormat(false, false) 
        << "Format from model" << model.getFormat(false, false)->text << '\n';
        equal = false;
    }
    if (amodel.getFormat(true, false) != model.getFormat(true, false)->text) {
        if (equal) std::cout << error;
        std::cout << "\tExpected format (true, false):" << amodel.getFormat(true, false) 
        << " Format from model: " << model.getFormat(true, false)->text << '\n';
        equal = false;
    }
    if (amodel.getFormat(false, true) != model.getFormat(false, true)->text) {
        if (equal) std::cout << error;
        std::cout << "\tExpected format (false, true):" << amodel.getFormat(false, true) 
        << " Format from model: " << model.getFormat(false, true)->text << '\n';
        equal = false;
    }
    if (amodel.getFormat(true, true) != model.getFormat(true, true)->text) {
        if (equal) std::cout << error;
        std::cout << "\tExpected format (true, true): " << amodel.getFormat(true, true) 
        << " Format from model: " << model.getFormat(true, true)->text << '\n';
        equal = false;
    }
    if (equal) std::cout << "[+] Format strings are equal.\n";
}

void make_test_for_model(ShapeModel& model, ModelAsserts& amodel){
    if (amodel.paramNumbers == model.getParamNumber()) {
        std::cout << "[+] Numbers of parameters are equal\n";
    } else {
        std::cout << "[-] Number of parameters are not equal\n";
        std::cout << "\tExpected number of parameters: " << amodel.paramNumbers << '\n';
        std::cout << "\tNumber of parameters from model: " << model.getParamNumber() << '\n';
    }
    if (amodel.name[0] == model.getName()->text) {
        std::cout << "[+] Names of shape are equal\n";
    } else {
        std::cout << "[-] Names of shape are not equal\n";
        std::cout << "\tExpected name: " << amodel.name[0] << '\n';
        std::cout << "\tName from model: " << model.getName()->text << '\n';
    }
    compare_format(model, amodel);
    compare_option_names(model, amodel);
    compare_numbers_names(model, amodel);
    compare_numbers_names_case(model, amodel);
    compare_short_names(model, amodel);    
}

