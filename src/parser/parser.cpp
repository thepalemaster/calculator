#include "parser.hpp"
#include "calculator.hpp"

#include <cstring>
#include <cerrno>  

#include <iostream>
#include <cmath>

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

    double parseDouble(char *stringData, size_t len) {
        char* start{stringData};
        double value = 0;
        double temp = 0;
        bool sum = false;
        bool negative = false;
        char* end{stringData};
        while (true) {
            while ((start - stringData) < len) {
                if (*start == ' ') {
                    ++start;
                } else if (*start == '+') {
                    sum = true;
                    ++start;
                } else if (*start == '-') {
                    ++start;
                    sum = true;
                    negative = !negative;
                } else if (*start == '\0') {
                    return value;
                } else {
                    break;
                }
            }
            temp = std::strtod(start, &end);
            //std::cout << len << '%' << end - stringData << std::endl; 
            if (start == end || len < end - stringData) break;
            //std::cout << std::string(start, end - start) << '!' << temp << std::endl;
            start = end;
            if (errno == ERANGE){
                errno = 0;
                throw std::invalid_argument("out of range");
            }
            if (negative) {
                temp = -temp;
                negative = false;
            }
            if (sum) {
                value += temp;
                sum = false;
            } else {
                value = temp;
            }
            if (len == end - stringData) break;
        }
        while (len <(end - stringData)) {
            if (*end == ' ') {
                ++end;
            } else {
                std::invalid_argument("incorrect input");
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
        
    double toDouble (char* number, size_t len) {
        for (size_t i = 0; i < len; ++i) {
            if (number[i] == ','){
                number[i] = '.';
            }
        }
        return parseDouble(number, len);
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

    
    CalculatorParameters getCalcParams (char* input, size_t len, int paramNumber) {
        CalculatorParameters calcParam;
        if (paramNumber > 4 || paramNumber < 0)
            throw std::invalid_argument("incorrect number of parameters");
        char* start {input};
        char* pos;
        for (int i = 0; i < paramNumber; ++i) {
            while (*start == ' ' &&  len > (start - input)) {
                ++start;
            }
            pos = static_cast<char*> (std::memchr(start, ' ', len - (start - input)));
            if (pos) {
                calcParam.numbers[i] = toDouble(start, pos - start);
                start = pos;
            } else {
                if (i + 1 != paramNumber) {
                    throw std::invalid_argument("incorrect number of parameters");
                }
                calcParam.numbers[i] = toDouble(start,  len - (start - input));
                return calcParam;
            }
        }
        while (*start == ' ' &&  len > (start - input)) {
                ++start;
        }
        pos = static_cast<char*> (std::memchr(start, ' ', len - (start - input)));
        double factor;
        if (pos) {
            factor = toDouble(start, pos - start);
        } else {
            factor = toDouble(start,  len - (start - input));
        }
        if (factor && std::isnormal(factor)) {
            calcParam.factor = factor;
            start = pos;
        }
        bool firstOption = false;
        while (len > (start - input)) {
            if (*start == ' ') {
                ++start;
            } else if (*start == '+') {
                if (!firstOption) {
                    calcParam.options[0] = true;
                    firstOption = true;
                    ++start;
                } else {
                    calcParam.options[1] = true;
                    return calcParam;
                }
            } else if (*start == '-') {
                if (!firstOption) {
                    calcParam.options[0] = false;
                    firstOption = true;
                    ++start;
                } else {
                    calcParam.options[1] = false;
                    return calcParam;
                }
            } else {
                std::invalid_argument("incorrect input");
            }
        }
        return calcParam;
    }
    
    

    int pureIntOrZero(const std::string& command) noexcept {
        int x{};
        size_t pos;
        try {
            x = std::stoi(command, &pos);
            while (pos < command.size()) {
                if (command[pos] != ' ') throw std::invalid_argument ("incorrect input");
                pos++;
            }
        } catch (std::invalid_argument) {
            x = 0;
        }
        return x;  
    }
    
    int pureIntOrExcept(const std::string& command) {
        int x{};
        size_t pos;
        x = std::stoi(command, &pos);
        while (pos < command.size()) {
            if (command[pos] != ' ') throw std::invalid_argument ("incorrect input");
            pos++;
        }
        return x;  
    }
}
