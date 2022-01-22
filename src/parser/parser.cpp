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
        auto pos = static_cast<char*> (std::memchr(number, ',', len));
        while (pos) {
            *pos = '.';
            pos = static_cast<char*> (std::memchr(pos, ',', len - (pos  - number)));
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
    
    int pureIntOrExcept(std::string_view command) {
        int x{};
        const char* start = command.data();
        const char* end = start + command.size();
        while (*start == ' ' && start != end) ++start;
        auto result = std::from_chars(start, end, x);
        while (*result.ptr == ' ' && result.ptr != end) ++ result.ptr;
        if (result.ptr != end) throw std::invalid_argument("unable convert to number");
        return x;  
    }

    

}

    /*
    std::from_chars version
    
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
    
        double parseDouble(const char *stringData, size_t len) {
        const char *end {stringData + len};
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
    
    */
