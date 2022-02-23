#pragma once
#include <QStringList>

#include <QStringListModel>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <QAbstractItemView>
#include <array>

namespace Utility {
    const QStringList getLenghtList();    
    const QStringList getAreaList();
    const QString getShortName(int index);
    double magnitudeByIndex(int index);
}
