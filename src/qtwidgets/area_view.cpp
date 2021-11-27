#include "area_view.hpp"

AreaViewer::AreaViewer(QWidget *parent):
QWidget(parent), box{new QHBoxLayout(this)}, number(new QLabel(QString::number(0.)))  {
    box->addWidget(number);
}

void AreaViewer::updateArea(double value) {
    number->setText(QString::number(value));
}

