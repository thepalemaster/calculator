#pragma once
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>

#include "ui_shape_view.h"
#include "calculator.hpp"


class ShapeViewer: public QWidget{
    Q_OBJECT
private:
    Ui::ShapeView ui;
    Calculator &calculator;
public:
    int index;
    ShapeViewer(Calculator& calc, const Result& shapeResult, QWidget* parent = nullptr);
    void newShape(const Result& shapeResult);
    QString getText(const Result& shapeResult);
    void setInvisible();
};
