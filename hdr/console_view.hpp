# pragma once
#include <iostream>
#include <map>

#include "calculator.hpp"
#include "shape_model.hpp"
#include "utility_shape_text.hpp"

class ConsoleView {
private:
    std::function<void(double)> updateResult {[this](double result) {
        totalArea = result;
    }};
    std::function<void(int index, Result::action action)> updateList {[this](int index, Result::action action){
        std::string item;
        switch (action) {
            case Result::NEW_ITEM :
                list.push_back(Utility::getText<std::string>(calculator.getResultList()[index], calculator));
                break;
            case Result::RESET:
                list.clear();
                break;
            case Result::CHANGE_ITEM:
                list[index] = Utility::getText<std::string>(calculator.getResultList()[index], calculator);
                break;
            case Result::REMOVE_ITEM:
                list.erase(list.begin() + index);
                break;
            default:
                break;
        }
    }};
    std::map<std::string, int> idMap;
    std::vector<std::string> helpList;
    std::vector<std::string> list;
    double totalArea = 0.;
    Calculator& calculator;
    void printStatus();
    void printHelp();
    std::string resultToString(const Result& result);
    void setupOptions (Shapes::AbstactShape& shape);
    void addHelpString(std::array<const Shapes::Option*, 7> params);

public:
    ConsoleView(Calculator& calc);
    void mainLoop();
    void updateResult1(double result);
    void updateList1(int index, Result::action action);
};

