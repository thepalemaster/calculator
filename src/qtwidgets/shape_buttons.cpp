#include "shape_buttons.hpp"

ShapeButtons::ShapeButtons (QWidget* parent):
QWidget(parent), buttonLayout{new QGridLayout()} {
    
}

QPushButton* ShapeButtons::newButton(const QString& name){
    const int size_rows = 3;
    auto button = new QPushButton(name);
    buttonLayout->addWidget(button, buttonCounter/size_rows, buttonCounter%size_rows);
    ++buttonCounter;
    setLayout(buttonLayout);
    return button;
}
