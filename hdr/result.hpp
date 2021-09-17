#pragma once
#include <string>


struct Result {
    double area;
    int shapeID;
    std::string input;
    
    enum action{
        NEW_ITEM,
        REMOVE_ITEM,
        CHANGE_ITEM,
        RESET
    };
};
