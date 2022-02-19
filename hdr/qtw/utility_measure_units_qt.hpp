#pragma once

#include <QStringListModel>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QAbstractItemView>
#include <array>

namespace Utility {
    struct MeasureType {
        QString name;
        QString shortNameLen;
        QString shortNameArea;
        double value;
    };
    
    const std::array<MeasureType, 5> units {
        MeasureType {"метры", "м", "м²", 10},
        MeasureType {"дециметры", "дм", "дм²", 1},
        MeasureType {"дюймы", "дюйм", "дюйм²", 0.254},
        MeasureType {"сантиметры", "см", "см²", 0.1},
        MeasureType {"миллиметры", "мм", "мм²", 0.01}
    };
    
    
    inline const QStringList getLenghtList(){
        QStringList list;
        for (auto& unit: units) {
            list << unit.shortNameLen;
        }
        return list;
    }
    
    inline const QStringList getAreaList(){
        QStringList list;
        for (auto& unit: units) {
            list << unit.shortNameArea;
        }
        return list;
    }
    
    inline const QString getShortName(int index){
        if (index < 0 || index >= units.size()) return "";
        return units[index].shortNameArea;
    }
    
    inline double magnitudeByIndex(int index) {
        if (index < 0 || index >= units.size()) return 0;
        return units[index].value;        
    }
}
