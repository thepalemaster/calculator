#pragma once

#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QLineEdit>
#include "shapes.hpp"


class ShapeInput: public QWidget{
private:
    std::array<QLineEdit*, 4> usedInputLine {};
    std::array<QCheckBox*, 2> usedCheckBox {};
public:
    const int shapeID;
    ShapeInput(int id, QString name, std::array<const Shapes::Option*, 7> params, QWidget* parent = nullptr);
    void setInput (const Result& result);
    CalculatorParameters getInput();
};
