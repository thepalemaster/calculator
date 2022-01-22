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
    ShapeOptions(Calculator& calculator, QWidget* parent = nullptr);
    void addShape(int id, const ShapeModel& model);
};
