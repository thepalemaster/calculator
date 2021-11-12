#include <cstdio>

#include "console_view.hpp"
#include "shape_info.hpp"
#include "parser.hpp"

#include <cassert>
#include <sstream>
#include <limits>
//#define NDEBUG


enum InputType {
    NONE,
    DOUBLE,
    BOOL1,
    BOOL2,
    BOTH_BOOL
};


ConsoleView::ConsoleView(Calculator& calc): calculator{calc} {
    auto& shapes = calculator.getShapes();
    models.reserve(shapes.size());
    for(auto& shape: shapes) {
        auto& currentModel = models.emplace_back(shape->getOptions());
        auto& shortNames = currentModel.getDefaultShortNames();
        for (auto name: shortNames) {
            idMap.emplace(name->text, shape->shapeID);
        }
        addHelpString(currentModel.getParamNames());
        assert(helpList.size() - 1 == shape->shapeID && "Shape ID must always be equal to index of shape in the help string vector");
    }
    calculator.setupListCallback(updateList);
    calculator.setupResultCallback(updateResult);
    std::cout << "Калькулятор для расчёта площади.\n";
    std::cout << "Для справки введите help.\n";
}

void ConsoleView::addHelpString(std::array<const Shapes::Option *, 7> params) {
    std::ostringstream stringStream;
    if (params[0]) {
        stringStream << params[0]->text;
    } else {
        stringStream << "БЕЗ_ИМЕНИ";
    }
    stringStream << '\n';
    for (int i = 1; i < 5; ++i) {
        if(params[i]){
            stringStream << "Параметр " << i << ": " << params[i]->text << '\n';
        } else {
            break;
        }
    }
    if (params[5]) {
        stringStream << "Опция 1:" << params[5]->text << '\n';
        if (params[6]) {
            stringStream << "Опция 2:" << params[6]->text << '\n';
        }
    }
    helpList.push_back(stringStream.str());
}


void ConsoleView::mainLoop() {
    std::string command;
    while(true) {
        std::cout << '>';
        std::getline(std::cin, command);
        auto firstSpace = command.find(' ');
        if (command == "help"){
            //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            printHelp();
        } else if (command.rfind("del", 0) == 0) {
            int i = Parser::pureIntOrZero(command.data() + 3);
            if (!i) {
                std::cout << "Не верные аргументы команды del\n";
            } else {
                calculator.remove(i - 1);
                printStatus();
            }
        } else if (firstSpace != std::string::npos) {
            auto itr = idMap.find({command, 0, firstSpace});
            if (itr != idMap.end()) {
                int id = itr->second;
                
                try {
                    auto param = Parser::getCalcParams({command.data() + firstSpace, command.size() - firstSpace}, models[id].getParamNumber());
                    calculator.calculate(id, param);
                    printStatus();
                } catch (std::invalid_argument) {
                    std::cout << "Invalid argument.\n";
                }
            } else {
                std::cout << "Неизвестная команда\n";
            }
        } else {
            std::cout << "Неверный формат команды\n";
        }
    }
}
    
void ConsoleView::printStatus() {
    if (list.size() == 0) {
        std::cout << "Список фигур пуст.\n";
    } else {
        std::cout << "  Список фигур: \n";
    for (int i = 0; i < list.size(); ++i){
        std::cout << i + 1 << ") " << list[i] << '\n';
    }
    }
    std::cout << "------------------------\n";
    std::cout << "Общая площадь: " << totalArea << '\n';
}

std::string ConsoleView::resultToString(const Result& result) {
    auto format = models[result.shapeID].getFormat(result.param.options[0], result.param.options[1]);
    std::string s(format->text.size() + 5 * 10, '\0');
    int y = std::snprintf(s.data(), s.size(), format->text.data(), result.area, result.param.numbers[0], result.param.numbers[1],
                        result.param.numbers[2], result.param.numbers[3]);
    if (y > s.size()) {
        s.resize(y, '\0');
        std::sprintf(s.data(), format->text.data(), result.area, result.param.numbers[0], result.param.numbers[1],
                        result.param.numbers[2], result.param.numbers[3]);
    } else {
        s.resize(y);
    }
    return s;
}

void ConsoleView::printHelp() {
    std::cout << "Доступные фигуры:\n";
    for (int i = 0; i < helpList.size(); ++i) {
        std::cout << helpList[i];
        auto& commands = models[i].getDefaultShortNames();
        if (commands.empty()) {
            std::cout << "Нет активных комманд для этой фигуры.\n";
            continue;
        }
        if (commands.size() == 1) {
            std::cout << "Команда вызова: ";
            std::cout << commands[0]->text << '\n';
        } else {
            std::cout << "Команды вызова:";
            for (auto command: commands) {
                std::cout << command->text << ' ';
            }
            std::cout << ".\n";
        }
    }
}
