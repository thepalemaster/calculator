#pragma once

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFormLayout>

#include "shape_model.hpp"
#include "inputnumberqvalidator.hpp"


class ShapeInput: public QWidget{
private:
    InputNumberQValidator validator;
    std::array<QLineEdit*, 4> usedInputLine {};
    std::array<QCheckBox*, 2> usedCheckBox {};
    int currentParamNumber = 0;
    QGroupBox* newGroup;
    QLineEdit* factorLineEdit;
    QFormLayout* formLayout;
public:
    const int shapeID;
    ShapeInput(int id, QString name, const ShapeModel& model, QWidget* parent = nullptr);
    void setInput (const Result& result);
    bool getState(int index);
    CalculatorParameters getInput();
    void updateNames(std::array<const Shapes::Option*, 5> newNames);
};
