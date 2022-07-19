#include "qml_calculator.hpp"

CalculatorWrapper::ResultListModel::ResultListModel (QObject* parent):
QAbstractListModel (parent){
    auto& calc = getCalculator();
    calc.setupListCallback([this](int index, Result::action action){
        switch (action) {
            case Result::NEW_ITEM:
                emit beginInsertRows(QModelIndex(), index, index);
                emit endInsertRows();
                break;
            case Result::RESET:
                emit beginResetModel();
                emit endResetModel();
                break;
            case Result::CHANGE_ITEM:
                {
                    auto i = createIndex(index, 0, this);
                    emit dataChanged(i, i);
                }
                break;
            case Result::REMOVE_ITEM:
                emit beginRemoveRows(QModelIndex(), index, index);
                emit endRemoveRows();
                break;
            default:
                break;
        }
    });
}

QVariant CalculatorWrapper::ResultListModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) return {};
    auto& calc = getCalculator();
    auto& results = calc.getResultList();
    size_t rowIndex = index.row();
    if (rowIndex >= results.size()) {
        return {};
    }
    auto& result = results[rowIndex];
    auto id = results[rowIndex].shapeID;
    auto str = calc.models[id].getFormat(result.param.options[0], result.param.options[1])->text.data();
    return QString(str).arg(result.area)
        .arg(result.param.numbers[0])
        .arg(result.param.numbers[1])
        .arg(result.param.numbers[2])
        .arg(result.param.numbers[3]);
}

