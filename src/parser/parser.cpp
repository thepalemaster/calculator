#include "parser.hpp"
#include "calculator.hpp"

#include <cstring>
#include <cerrno>  

#include <iostream>

#include <charconv>
#include <system_error>
	

namespace Parser {
    bool toBool (std::string_view boolean) {
        if (boolean == "0" ||
            boolean == "false" ||
            boolean == "False"
        ) return false;
        if (boolean == "1" ||
            boolean == "true" ||
            boolean == "True"
        ) return true;
        throw std::invalid_argument("invalid bool cast");
    }
        
    void replaceComma(char* line, int len){
        for (int i = 0; i < len; ++i) {
            if (line[i] == ',') {
                line[i] = '.';
            }
        }
    }
    
    double parseDouble(const char *stringData, size_t len) {
        const char *end{stringData + len};
        double value = 0;
        double temp;
        bool negative = false;
        bool addition = false;
        while (true) {
            while(true) {
                if (*stringData == ' ') {
                    ++stringData;
                } else if (*stringData == '+') {
                    addition = true;
                    ++stringData;
                } else if (*stringData == '-') {
                    ++stringData;
                    addition = true;
                    negative = !negative;
                } else if (*stringData == '\0') {
                    return value;
                } else {
                    break;
                }
            }
            if (stringData >= end) return value;
            auto result = std::from_chars(stringData, end, temp);
            if (result.ec == std::errc()) {
                if (value && !addition) {
                    return value;
                }
                if (negative) {
                    temp = -temp;
                    negative = false;
                    addition = false;
                }
                value += temp;
                stringData = result.ptr;
            } else if (result.ec == std::errc::invalid_argument) {
                throw std::invalid_argument("incorrect input");
            } else if (result.ec == std::errc::result_out_of_range) {
                throw std::invalid_argument("out range");
            }
        }
        return value;
    }
    
    double parseDoubleOrZero(const char *stringData) {
        char* end;
        double result {0.};
        for (result = std::strtod(stringData, &end); stringData != end; result += std::strtod(stringData, &end)) {
            if (errno == ERANGE){
                return 0;
            }
            stringData = end;
        }      
        return result;
    }
        
    double toDouble (std::string_view number) {
        int commaPos = number.find(',');
        if (commaPos != std::string_view::npos) {
            int length = number.length();
            char tempData[length];
            std::memcpy(tempData, number.data(), length);
            replaceComma(tempData + commaPos, length - commaPos);
            return parseDouble(tempData, length);
        } else {
            return parseDouble(number.data(), number.length());
        }
    }
    
    double getFactorDouble (std::string_view number) {
        int commaPos = number.find(',');
        if (commaPos != std::string_view::npos) {
            char tempData[number.size()];
            std::memcpy(tempData, number.data(), number.size());
            replaceComma(tempData + commaPos, number.size() - commaPos);
            return parseDoubleOrZero(tempData);
        }
        return parseDoubleOrZero(number.data());
    }

    CalculatorParameters getCalcParams (std::string_view input, int paramNumber) {
        CalculatorParameters calcParam;
        if (paramNumber > 4 || paramNumber < 0)
            throw std::invalid_argument("incorrect number of parameters");
        for (int i = 0; i < paramNumber; ++i) {
            while (input[0] == ' ') {
                input.remove_prefix(1);
            }
            size_t pos = input.find(" ");
            if (pos == std::string_view::npos) {
                if (i + 1 != paramNumber) {
                    throw std::invalid_argument("incorrect number of parameters");
                }
                calcParam.numbers[i] = toDouble(input);
                input.remove_prefix(input.size());
            } else {
                calcParam.numbers[i] = toDouble({input.data(), pos});
                input.remove_prefix(pos + 1);
            }
        }
        while (input[0] == ' ') {
            input.remove_prefix(1);
        }
        if (!input.empty()) {
            size_t pos = input.find(" ");
            if (pos == std::string_view::npos) {
                pos = input.size();
            }
            calcParam.setFactor(toDouble({input.data(), pos}));
            input.remove_prefix(pos + 1);
        }
        if (!input.empty()) {
            size_t option = 0;
            size_t pos = 0;
            while (option < 2 && pos < input.size()) {
                if (input[pos] == ' ') {
                    ++pos;
                } else {
                    if (input[pos] != '+') break;
                    calcParam.options[option] = true;
                    ++option;
                    ++pos;
                }
            }

        }
        return calcParam;
    }

    int pureIntOrZero(std::string_view command) noexcept {
        int x{};
        const char* start = command.data();
        const char* end = start + command.size();
        while (*start == ' ' && start != end) ++start;
        auto result = std::from_chars(start, end, x);
        while (*result.ptr == ' ' && result.ptr != end) ++ result.ptr;
        if (result.ptr != end) x = 0;
        return x;
    }
    

}
