#pragma once

#include "shape_input.hpp"
#include "calculator.hpp"

class ModalOptions: public QWidget {
    Q_OBJECT
private:
    ShapeInput* modalInput;
public:
    ModalOptions(int index, Calculator& calc, const Result& oldResult, QWidget* parent = nullptr);
};


