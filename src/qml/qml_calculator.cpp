#include "qml_calculator.hpp"

Q_GLOBAL_STATIC(Calculator, globalCalculator)

namespace CalculatorWrapper {
    Calculator calc{};
    
    Calculator& getCalculator () {
        return *globalCalculator;
    }

    void ResultListModel::remove(int index){}
    void ResultListModel::edit(int index){}
    void ResultListModel::clear(){}

    int ResultListModel::rowCount(const QModelIndex& parent) const {
        return 0;
    }

}


