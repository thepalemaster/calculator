#pragma once
#include <QtWidgets/QStackedLayout>

#include "shape_model.hpp"
#include "shape_buttons.hpp"
#include "calculator.hpp"

class ShapeOptions: public QWidget {
private:
    ShapeButtons* buttons;
    QStackedLayout* stackLayout;
public:
    ShapeOptions(Calculator& calc, QWidget* parent = nullptr);
    void addShape(const ShapeModel& model);
};
