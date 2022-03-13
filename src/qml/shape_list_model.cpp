#include "shape_list_model.hpp"

#include <QDebug>

ShapeListModel::ShapeListModel(Calculator& calc, QObject* parent):
QAbstractListModel(parent) {
    for (auto& model:  calc.models) {
        strList.push_back(&model.getName()->text);
    }    
}

ShapeListModel::ShapeListModel(QObject* parent):
    QAbstractListModel(parent) {
    qDebug() << "start";
//    strList.resize(10);
        for (auto& model:  calc.models) {
            strList.push_back(&model.getName()->text);
            qDebug() << strList.back();
        }
    }


int ShapeListModel::rowCount(const QModelIndex & parent) const {
    return strList.size();
};

int ShapeListModel::columnCount(const QModelIndex & parent) const {
    return 1;
};

QVariant ShapeListModel::data(const QModelIndex & index, int role) const {
    qDebug() << role;
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }
    size_t rowIndex = index.row();
    qDebug() << role << '+' << rowIndex;
    if (rowIndex >= strList.size()) {
        return {};
    }
    return QVariant(strList[rowIndex]->data());
};
