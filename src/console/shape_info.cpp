#include "hdr/shape_info.hpp"
#include <sstream>

void ShapeInfo::addName(std::string_view str) {
    information[0] = str;    
}

void ShapeInfo::addDoubleInput1(std::string_view str) {
    information[1] = str;    
}

void ShapeInfo::addDoubleInput2(std::string_view str) {
    information[2] = str;    
}

void ShapeInfo::addDoubleInput3(std::string_view str) {
    information[3] = str;    
}

void ShapeInfo::addDoubleInput4(std::string_view str) {
    information[4] = str;    
}

void ShapeInfo::addBoolInput1(std::string_view str) {
    information[5] = str;    
}

void ShapeInfo::addBoolInput2(std::string_view str) {
    information[6] = str;    
}

void ShapeInfo::addShortName (std::string_view str ) {
    if (aliasCount >= 6) return;
    information[7 + aliasCount] = str;
}

std::string ShapeInfo::toString()  {
    std::ostringstream stringStream;
    if (!information.empty()) {
        stringStream << information[0] << " :\n";
    } else {
        stringStream << "NONAME :\n";
    }
    if(information.empty()) {
        stringStream << "NO COMMANDS\n";
    } else {
        stringStream << "Commands:";
        for (auto it = information.begin() + 7; it != information.end(); ++it ) {
            if (it->empty()) break;
            stringStream << ' ' << *it;
        }
        stringStream << '\n';
    }
    std::string usageString;
    usageString.reserve(49);
    usageString+= "COMMAND ";
    stringStream << "Arguments:\n";
    for (int i = 1; i < 5; i++) {
        if (information.empty()) break;
        stringStream << "Number input #" << i << ": ";
        stringStream << information[i] << '\n';
        usageString += "NUMBER";
        usageString += i;
        usageString += ' ';
    }
    if (!information.empty()) {
        stringStream << "Option #1" << ": ";
        stringStream << information[6] << '\n';
        usageString += "OPTION1 ";
        if (!information.empty()) {
           stringStream << "Option #2" << ": ";
           stringStream << information[7] << '\n';
           usageString += "OPTION2";
        }
    }
    stringStream << "Usage: ";
    stringStream << usageString;
      
    return stringStream.str();
}

std::string ShapeInfo::getFormatString() {
    return " ";
}

