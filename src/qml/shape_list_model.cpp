#include "qml_calculator.hpp"


CalculatorWrapper::ShapeListModel::ShapeListModel(QObject* parent):
QAbstractListModel(parent) {
    auto& calc = getCalculator();
    strList.reserve(calc.models.size());
    for (auto& model:  calc.models) {
        strList.push_back(&model.getName()->text);
    }    
}

int CalculatorWrapper::ShapeListModel::rowCount(const QModelIndex & parent) const {
    return strList.size();
};

int CalculatorWrapper::ShapeListModel::columnCount(const QModelIndex & parent) const {
    return 1;
};

QVariant CalculatorWrapper::ShapeListModel::data(const QModelIndex & index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }
    size_t rowIndex = index.row();
    if (rowIndex >= strList.size()) {
        return {};
    }
    return QVariant(strList[rowIndex]->data());
};
