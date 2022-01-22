#pragma once

#include <QtWidgets/QLabel>

class Calculator;
class QComboBox;

class MeasureUnits: public QWidget {
    Q_OBJECT
private:
    QComboBox* comboInput;
    QComboBox* comboOutput;
public:
    void setDefaults();
    explicit MeasureUnits(Calculator& calc, QWidget *parent = nullptr);
signals:
    void changedInputName(const QString newName);
};
