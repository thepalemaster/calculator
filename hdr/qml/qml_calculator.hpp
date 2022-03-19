#pragma once

#include <QAbstractListModel>

#include "calculator.hpp"

namespace CalculatorWrapper {
    Calculator& getCalculator ();

    class ShapeListModel: public QAbstractListModel {
    Q_OBJECT
    private:
        std::vector<const std::string*> strList;
        Calculator calc1;
    public:
        ShapeListModel(QObject* parent = nullptr);
        int rowCount(const QModelIndex & parent) const override;
        int columnCount(const QModelIndex & parent) const override;
        QVariant data(const QModelIndex & index, int role) const override;
    };

    class ShapeInputModel {};

    class ResultListModel {};
}
