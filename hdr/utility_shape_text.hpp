#pragma once

#include <cmath>
#include <cstring>

#include "calculator.hpp"

namespace Utility {
    
    

    template <typename S>
    S getText(const Result& shapeResult, const Calculator& calc) {
        const int bufferFactorSize = 15;
        char factorBuff[bufferFactorSize];
        int realSizeFactor = std::snprintf(factorBuff, 15, " [k: %g]", shapeResult.param.factor);
        if (realSizeFactor > bufferFactorSize - 1) {
            factorBuff[bufferFactorSize - 2] = ']';
        }
        auto format = calc.models[shapeResult.shapeID].getFormat(shapeResult.param.options[0], shapeResult.param.options[1]);
        int expectedSize = format->text.size() + 4 * 10 + realSizeFactor;
        char buff[expectedSize];
        int realSize = std::snprintf(buff, expectedSize, format->text.data(), shapeResult.area, shapeResult.param.numbers[0], shapeResult.param.numbers[1],
                        shapeResult.param.numbers[2], shapeResult.param.numbers[3]);
        if (realSize + realSizeFactor > expectedSize) {
            char newBuff[realSize + 1 + realSizeFactor];
            int newSize = std::sprintf(newBuff, format->text.data(), shapeResult.area, shapeResult.param.numbers[0], shapeResult.param.numbers[1],
                        shapeResult.param.numbers[2], shapeResult.param.numbers[3]);
            std::strcat(buff + newSize, factorBuff);
            return S(newBuff);
        }
        std::strcat(buff + realSizeFactor, factorBuff);
        return S(buff);
    }

}
