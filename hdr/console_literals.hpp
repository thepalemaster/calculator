#pragma once

#include <string>

namespace english_literals{
    const char* lang {"eng"};
    const char* commonArea{"Common area: "};
    const char* availableShapes {"Available shapes:\n"};
    const char* enterHelpCommand {"Enter \"help\" for display help.\n"};
    const char* noName {"NO_NAME"};
    const char* parameterLiteral{"Paramrter "};
    const char* optionOne {"Option 1: "};
    const char* optionTwo {"Option 2: "};
    const char* wrongDel {"Invalid arguments of the del command\n"};
    const char* invalidArgument {"Invalid arguments for shape\n"};
    const char* unknownCommand {"Unknown command\n"};
    const char* wrongCommandFormat {"Invalid command format\n"};
    const char* emptyShapeList {"Shape list is empty\n"};
    const char* shapeListLiteral {" Shape list: \n"};
    const char* commandsForShape {"Call Commands: "};
    const char* commandForShape {"Call Command: "};
    const char* noCommandsForShape {"No call command for this shape.\n"};
    const char* wrongMeasure {"Invalid input for measure units"};
    const char* setOutput {"Magnitude of output measure unit:"};
    const char* setInput {"Magnitude of input measure unit:"};
    const char* fullHelp {
        "The area of primitive shape calculate in the following way:\n"
        "SHAPE_COMMAND ARGUMENTS [FACTOR] [OPIONS]\n"
        "ARGUMENTS - numeric values calculating the area. Each figure has its own number of parameters\n"
        "FACTOR - coefficient by which the resulting area is multiplied, if not specified, the default coefficient is 1\n"
        "OPTIONS - the options that are set for some shapes have the value YES/NO, are set with the symbols +/-, by default the option is '-' (NO).\n"
        "'clear' command clears the list of calculated figures\n"
        "'help' command print this help\n"
        "'measure input [VALUE]' command sets the multiplicity of input measure units\n"
        "'measure output [VALUE]' command sets the multiplicity of output units. Note that the multiplicity value is set in units of length, which means that when calculating the area it will be squared.\n"
        "'exit' command exits this program\n"
    };
}

namespace russian_literals {
    const char* lang {"ru"};
    const char* totalAreaLiteral{"Общая площадь: "};
    const char* availableShapes {"Доступные фигуры:\n"};
    const char* calculatorForArea {"Калькулятор для расчёта площади.\n"};
    const char* enterHelpCommand {"Для справки введите help.\n"};
    const char* noName {"БЕЗ_ИМЕНИ"};
    const char* parameterLiteral{"Параметр "};
    const char* optionOne {"Опция 1: "};
    const char* optionTwo {"Опция 2: "};
    const char* wrongDel {"Неверные аргументы команды del\n"};
    const char* invalidArgument {"Неверные аргументы для фигуры\n"};
    const char* unknownCommand {"Неизвестная команда\n"};
    const char* wrongCommandFormat {"Неверный формат команды\n"};
    const char* emptyShapeList {"Список фигур пуст.\n"};
    const char* shapeListLiteral {" Список фигур: \n"};
    const char* commandsForShape {"Команды вызова: "};
    const char* commandForShape {"Команда вызова: "};
    const char* noCommandsForShape {"Нет комманд для этой фигуры.\n"};
    const char* wrongMeasure {"Неверный формат ввода единиц измерений"};
    const char* setOutput {"Значение единицы вывода:"};
    const char* setInput {"Значение единицы ввода:"};
    const char* fullHelp {
        "Площадь простой фигуры рассчитывается следующим способом:\n"
        "КОМАНДА_ФИГУРЫ ПАРАМЕТРЫ [КОЭФФИЦИЕНТ] [ОПЦИИ]\n"
        "ПАРАМЕТРЫ - числовые значения для рассчёта площади. У каждой фигуры своё количество параметров\n"
        "КОЭФФИЦИЕНТ - коэффициент на который домножается полученная плошадь, если не указан то коэффициент по умолчанию равен 1\n"
        "ОПЦИИ - опции, которые задаются для некоторых фигур, имеет значение ДА/НЕТ, задаются символами +/-, по умолчанию опция равно '-' (НЕТ).\n"
        "Команда clear отчищает список рассчитаных фигур\n"
        "Команда help выводит эту справку\n"
        "Команда measure input [ЗНАЧЕНИЕ] задаёт кратность единиц ввода\n"
        "Команда measure output [ЗНАЧЕНИЕ] задаёт кратность единиц вывода. Следует иметь в виду что значение кратности задаётся в единицах длинны, а значит при вычислении площади будет возведено в квадрат.\n"
        "Команда exit выход из этой программы\n"
    };
}
