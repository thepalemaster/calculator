# pragma once
#include <iostream>
#include <map>

#include "calculator.hpp"

class ConsoleView {
private:
    bool anotherCallbackReady = false;
    std::map<std::string, int> idMap;
    std::vector<std::string> list;
    double totalArea;
    Calculator& calculator;
    void printStatus();
    std::string resultToString(Result result);
    void setupOptions (Shapes::AbstactShape& shape);
    enum InputType {
        NONE,
        DOUBLE,
        BOOL
    };
public:
    ConsoleView(Calculator& calc);
    void mainLoop();
    void updateResult(double result);
    void updateList(int index, Result::action action);
};
