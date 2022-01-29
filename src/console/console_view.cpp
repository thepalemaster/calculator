#include <cstdio>

#include "console_view.hpp"
#include "parser.hpp"
#include "console_literals.hpp"

#include <cassert>
#include <sstream>
#include <limits>

using namespace russian_literals;

enum InputType {
    NONE,
    DOUBLE,
    BOOL1,
    BOOL2,
    BOTH_BOOL
};


ConsoleView::ConsoleView(Calculator& calc): calculator{calc} {
    auto& shapes = calculator.getShapes();
    for(auto& shape: shapes) {
        auto& currentModel = calculator.models[shape->shapeID];
        auto& shortNames = currentModel.getDefaultShortNames();
        for (auto name: shortNames) {
            idMap.emplace(name->text, shape->shapeID);
        }
        addHelpString(currentModel.getParamNames());
    }
    calculator.setupListCallback(updateList);
    calculator.setupResultCallback(updateResult);
    std::cout << calculatorForArea;
    std::cout << enterHelpCommand;
}

void ConsoleView::addHelpString(std::array<const Shapes::Option *, 7> params) {
    std::ostringstream stringStream;
    if (params[0]) {
        stringStream << params[0]->text;
    } else {
        stringStream << noName;
    }
    stringStream << '\n';
    for (int i = 1; i < 5; ++i) {
        if(params[i]){
            stringStream << '\t' << parameterLiteral << i << ": " << params[i]->text << '\n';
        } else {
            break;
        }
    }
    if (params[5]) {
        stringStream << '\t' << optionOne << params[5]->text << '\n';
        if (params[6]) {
            stringStream << '\t' << optionTwo << params[6]->text << '\n';
        }
    }
    helpList.push_back(stringStream.str());
}

void ConsoleView::mainLoop() {
    std::string command;
    while(true) {
        std::cout << '>';
        std::getline(std::cin, command);
        size_t start = 0;
        while (start < command.size() && command[start] == ' ') start++;
        auto firstSpace = command.find(' ', start);
        if (command.rfind("help", start) == start){
            printHelp();
        } else if (command.rfind("del", start) == 0) {
            int i = Parser::pureIntOrZero(command.data() + 3);
            if (!i) {
                std::cout << optionTwo;
            } else {
                calculator.remove(i - 1);
                printStatus();
            }
        } else if (firstSpace != std::string::npos) {
            auto searchResult = command.find("measure", start);
            if (searchResult != std::string::npos) {
                try {
                    auto searchOutput = command.find("output", start);
                    if (searchOutput != std::string::npos) {
                        searchOutput += 6;
                        std::string_view{command.data() + searchOutput, command.size() - searchOutput};
                        auto result = Parser::toDouble(command.data() + searchOutput, command.size() - searchOutput);
                        calculator.setMeasureOutput(result);
                        printStatus();
                        std::cout << setOutput << result << '\n';
                    } else {
                        auto searchInput = command.find("input", start);
                        if (searchInput != std::string::npos) {
                            searchInput +=5;
                            auto result = Parser::toDouble(command.data() + searchInput, command.size() - searchInput);
                            calculator.setMeasureInput(result);
                            printStatus();
                            std::cout << setInput << result << '\n';
                        } else {
                            std::cout << wrongMeasure;
                        }
                    }
                } catch (std::invalid_argument e) {
                    std::cout << e.what();
                }  
            } else {
                auto itr = idMap.find({command, start, firstSpace});
                if (itr != idMap.end()) {
                    int id = itr->second;
                    try {
                        auto param = Parser::getCalcParams(command.data() + firstSpace, command.size() - firstSpace, calculator.models[id].getParamNumber());
                        calculator.calculate(id, param);
                        printStatus();
                    } catch (std::invalid_argument) {
                        std::cout << invalidArgument;
                    }
                } else {
                    std::cout << unknownCommand;
                }
            }
        } else if (command.rfind("exit", start) == start) {
            break;
        } else if (command.rfind("clear", start) == start) {
            calculator.reset();
        } else {
            std::cout << wrongCommandFormat;
        }
    }
}
    
void ConsoleView::printStatus() {
    if (list.size() == 0) {
        std::cout << emptyShapeList;
    } else {
        std::cout << shapeListLiteral;
    for (int i = 0; i < list.size(); ++i){
        std::cout << i + 1 << ") " << list[i] << '\n';
    }
    }
    std::cout << "------------------------\n";
    std::cout << totalAreaLiteral << totalArea << '\n';
}

void ConsoleView::printHelp() {
    std::cout << calculatorForArea;
    std::cout << fullHelp;
    std::cout << availableShapes;
    for (int i = 0; i < helpList.size(); ++i) {
        std::cout << helpList[i];
        auto& commands = calculator.models[i].getDefaultShortNames();
        if (commands.empty()) {
            std::cout << noCommandsForShape;
            continue;
        }
        if (commands.size() == 1) {
            std::cout << "\t" <<commandForShape;
            std::cout << commands[0]->text << '\n';
        } else {
            std::cout << "\t" << commandsForShape;
            for (auto command: commands) {
                std::cout << command->text << ' ';
            }
            std::cout << ".\n";
        }
        std::cout << '\n';
    }
}
