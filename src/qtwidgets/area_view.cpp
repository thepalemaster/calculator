#include "area_view.hpp"

#include <cmath>

const double almostIntergral = 1.0e-7;

QString fromValueToStr(const double value) {
    auto rounded = std::lround(value);
    double delta = std::abs(value - rounded);
    QString str;
    if (delta < almostIntergral) {
        str = QString::number(rounded);
    } else {
        str = QString::number(value, 'g', 5);
        auto pos = str.indexOf('e', Qt::CaseInsensitive);
        if (pos != -1) {
            str.replace(pos, 1, " ×10<sup>");
            str.insert(str.size(), "</sup>");
        }
    }
    
    return str;
}

AreaViewer::AreaViewer(QWidget *parent):
QWidget(parent), fullNumber{new QLabel("0")}, box{new QHBoxLayout()}, info{new QLabel()}  {
    QFont font = fullNumber->font();
    font.setPointSize(30);
    fullNumber->setFont(font);
    box->addStretch();
    box->addWidget(fullNumber);
    box->addWidget(info);
    setLayout(box);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

void AreaViewer::updateArea(double value) {
    currentArea = value;
    fullNumber->setText(fromValueToStr(value));
}

double AreaViewer::getValue(){
    return currentArea;    
}

void AreaViewer::setMeasure(QString measureUnit) {
    info->setText(QString("<strong>%1</strong>").arg(measureUnit));
}
