#include "hdr/shapes.hpp"
#include <cstring>
#include <cerrno>  

	

namespace Shapes {
    
    AbstactShape::AbstactShape(int id): shapeID{id} {}

    
    double AbstactShape::calculateArea(std::string) {
        return 0;
    }

    bool AbstactShape::toBool (std::string_view boolean) {
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
    
    void AbstactShape::removeSpaces(char *line, int len) {
        int pos = 0;
        for (int i = 0; i < len; ++i) {
            if (line[i] == ' ') {
                continue;
            }
            line[pos] = line[i];
            ++pos;
        }
        line[pos] = '\0';
    }
    
    const std::vector<Option>& AbstactShape::getOptions() const {
        return options;
    }

    void AbstactShape::replaceComma(char* line, int len){
        for (int i = 0; i < len; ++i) {
            if (line[i] == ',') {
                line[i] = '.';
            }
            line[len] = '\0';
        }
    }
    
    double AbstactShape::parseDouble(const char *stringData) {
        char* end;
        double result {0.};
        for (result = std::strtod(stringData, &end); stringData != end; result += std::strtod(stringData, &end)) {
            if (errno == ERANGE){
                throw std::invalid_argument("out range");
            }
            stringData = end;
        }
        if (strlen(end) != 0) {
            throw std::invalid_argument("invalid input");
        }
        
        return result;
    }
        
    //предполагается, что у чисел в качестве десятичного разделителя могут быть как
    // точки, так и запятые, чтобы не переключать локали для каждого ввода
    // функция просто меняет все запятые на точки, а так же удаляет все пробелы
    double AbstactShape::toDouble (std::string_view number) {
        const char *stringData;
        int length = number.length();
        int spacePos = number.find(' ');
        int commaPos = number.find(',');
        if (spacePos != std::string_view::npos) {
            char tempData[length];
            std::memcpy(tempData, number.data(), length);
            removeSpaces(tempData + spacePos, length - spacePos);
            if (commaPos != std::string_view::npos) replaceComma(tempData + commaPos, length - commaPos);
            return parseDouble(tempData);
        } else if (commaPos != std::string_view::npos) {
            char tempData[length];
            std::memcpy(tempData, number.data(), length);
            replaceComma(tempData + commaPos, length - commaPos);
            stringData = tempData;
            return parseDouble(tempData);
        }
        stringData = number.data();
        return parseDouble(stringData);
    }
    
    Result AbstactShape::calculate (std::string inputLine){
        m_position = 0;
        m_positive = true;
        return {calculateArea(inputLine), shapeID, inputLine};
    }
    
   double AbstactShape::getDouble(const std::string& line) {
       int end = line.find('\t', m_position);
       double temp = toDouble(std::string_view(line.data() + m_position, end - m_position - 1));
       if (temp < 0) {
           temp = -temp;
           m_positive = false;
       }
       m_position = end + 1;
       return temp;
   }
   
   double AbstactShape::getFactor (const std::string& line) {
       if (m_position >= line.length()) {
           return m_positive ? 1 : -1;
       }
       double temp = toDouble(std::string_view(line.data() + m_position, line.length() - m_position - 1));
       if (temp == 0) {
           return m_positive ? 1 : -1;
       }
       if (!m_positive) {
           return temp > 0 ? -temp : temp;
       }
       return temp;
   }
   
   bool AbstactShape::getBool(const std::string& line) {
       int end = line.find('\t', m_position);
       bool temp = toBool(std::string_view(line.data() + m_position, line.length() - m_position - 1));
       m_position = end + 1;
       return temp;
    }
    
}
