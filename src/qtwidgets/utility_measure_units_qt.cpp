#include "utility_measure_units_qt.hpp"

#include <array>

namespace Utility {
    struct MeasureType {
        QString name;
        QString shortNameLen;
        QString shortNameArea;
        double value;
    };
    

#ifdef LANG_ENG
    const std::array<MeasureType, 5> units {
        MeasureType {"metre", "m", "m²", 10},
        MeasureType {"decimetre", "dm", "dm²", 1},
        MeasureType {"inch", "inch", "inch²", 0.254},
        MeasureType {"centimetre", "cm", "cm²", 0.1},
        MeasureType {"millimetre", "mm", "mm²", 0.01}
    };
#else 
    const std::array<MeasureType, 5> units {
        MeasureType {"метры", "м", "м²", 10},
        MeasureType {"дециметры", "дм", "дм²", 1},
        MeasureType {"дюймы", "дюйм", "дюйм²", 0.254},
        MeasureType {"сантиметры", "см", "см²", 0.1},
        MeasureType {"миллиметры", "мм", "мм²", 0.01}
    };
#endif
    
    
    const QStringList getLenghtList(){
        QStringList list;
        for (auto& unit: units) {
            list << unit.shortNameLen;
        }
        return list;
    }
    
    const QStringList getAreaList(){
        QStringList list;
        for (auto& unit: units) {
            list << unit.shortNameArea;
        }
        return list;
    }
    
    const QString getShortName(int index){
        if (index < 0 || index >= units.size()) return "";
        return units[index].shortNameArea;
    }
    
    double magnitudeByIndex(int index) {
        if (index < 0 || index >= units.size()) return 0;
        return units[index].value;        
    }
}
