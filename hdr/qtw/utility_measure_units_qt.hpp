#pragma once

#include <QStringListModel>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QAbstractItemView>
#include <array>

namespace Utility {
    struct MeasureType {
        QString lenght;
        QString area;
        QString shortNameArea;
        double value;
    };
    
    const std::array<MeasureType, 5> units {
        MeasureType {"метры", "метры квадратные", "м<sup>2</sup>", 10},
        MeasureType {"дециметры", "дециметры квадратные", "дм<sup>2</sup>", 1},
        MeasureType {"дюймы", "дюймы квадратные", "дюйм<sup>2</sup>", 0.254},
        MeasureType {"сантиметры", "сантиметры квадратные", "см<sup>2</sup>", 0.1},
        MeasureType {"миллиметры", "миллиметры квадратные", "мм<sup>2</sup>", 0.01}
    };
    
    
    inline const QStringList getLenghtList(){
        QStringList list;
        for (auto& unit: units) {
            list << unit.lenght;
        }
        return list;
    }
    
    inline const QStringList getAreaList(){
        QStringList list;
        for (auto& unit: units) {
            list << unit.area;
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
