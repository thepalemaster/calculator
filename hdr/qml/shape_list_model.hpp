#pragma once
#include <QAbstractListModel>

#include "calculator.hpp"


class ShapeListModel: public QAbstractListModel {
    Q_OBJECT
private:
    std::vector<const std::string*> strList;
    Calculator calc;
public:
    ShapeListModel(QObject* parent = nullptr);
    ShapeListModel(Calculator& calc, QObject* parent = nullptr);
    int rowCount(const QModelIndex & parent) const override;
    int columnCount(const QModelIndex & parent) const override;
    QVariant data(const QModelIndex & index, int role) const override;
};
