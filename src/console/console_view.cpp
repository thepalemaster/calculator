#include "hdr/console_view.hpp"
#include "hdr/shape_info.hpp"




ConsoleView::ConsoleView(Calculator& calc): calculator{calc} {
    std::cout << "ПРИВЕТСТВИЕ";
    auto shapes = calculator.getShapes();
    for(auto& shape: shapes) {
        setupOptions(shape);
        auto options = shape.getOptions();
        for (auto& option: options) {
            if(option.type == Shapes::SHORT_NAME) {
                idMap.emplace(option.text, shape.shapeID);
            }
        }
    }
}

void ConsoleView::mainLoop() {
    int id;
    std::string tmp;
    while(true) {
        anotherCallbackReady = false;
        std::cin >> tmp;
        auto itr = idMap.find(tmp);
        if (itr != idMap.end()) {
            int id = itr->second;
            std::getline(std::cin, tmp);
            calculator.calculate(id, tmp);
        }
    }
}

void ConsoleView::setupOptions(Shapes::AbstactShape& shape) {
    std::string customPrint;
    ShapeInfo info;
    InputType previous = NONE;
    auto options = shape.getOptions();
    for(auto& option: options) {
        switch (option.type) {
            case Shapes::NAME:
                previous = NONE;
                info.addName(&option.text);
                break;
            case Shapes::SHORT_NAME:
                idMap.emplace(option.text, shape.shapeID);
                previous = NONE;
                break;
            case Shapes::PRINTF_TEMPLATE:
                customPrint = option.text;
                previous = NONE;
                break;
            case Shapes::INPUT_BOOL_1:
                previous = BOOL;
            default:
                break;
        }
        
    }//список фигур **
    if(customPrint.empty()) return;
}
    



void ConsoleView::printStatus() {
    int i = 1;
    for (/*int i = 1;*/ auto& str : list){
        std::cout << i << ") " << str;
    }
    std::cout << "------------------------";
    std::cout << "Общая площадь: " << totalArea;
}


void ConsoleView::updateResult(double result) {
    totalArea = result;
    if(anotherCallbackReady) {
        printStatus();
    }
}

std::string ConsoleView::resultToString(Result result) {
    return " Фигура ";
}


void ConsoleView::updateList(int index, Result::action action) {
    std::string item;
    switch (action) {
        case Result::NEW_ITEM :
            item = resultToString(calculator.getResultList()[index]);
            list.push_back(item);
            break;
        case Result::RESET:
            list.clear();
            break;
        case Result::CHANGE_ITEM:
            item = resultToString(calculator.getResultList()[index]);
            list[index] = item;
            break;
        case Result::REMOVE_ITEM:
            list.erase(list.begin() + index);
            break;
        default:
            break;
    }
}
