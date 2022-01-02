#include "area_view.hpp"

//#include <QPicture>
//#include <QtWidgets/QSvgWidget>
#include <QtSvg/QSvgWidget>
#include <cmath>

const QString num0 (":/digits/0.svg");
const QString num1 (":/digits/1.svg");
const QString num2 (":/digits/2.svg");
const QString num3 (":/digits/3.svg");
const QString num4 (":/digits/4.svg");
const QString num5 (":/digits/5.svg");
const QString num6 (":/digits/6.svg");
const QString num7 (":/digits/7.svg");
const QString num8 (":/digits/8.svg");
const QString num9 (":/digits/9.svg");
const QString comma (":/digits/comma.svg");
const QString minus (":/digits/minus.svg");
const QString empty (":/digits/empty.svg");

const QString areaName ("<strong>дм<sup>2</sup></strong>");

const double almostIntergral = 1.0e-7;

QString fromValueToStr(const double value) {
    auto rounded = std::lround(value);
    double delta = std::abs(value - rounded);
    QString str;
    if (delta < almostIntergral) {
        str = QString::number(rounded);
    } else {
        str = QString::number(value, 'f', 5);
    }
    return str;
}

AreaViewer::AreaViewer(QWidget *parent):
QWidget(parent), box{new QHBoxLayout()}, info(new QLabel(areaName))  {
    box->addStretch();
    for (auto& num: numbers) {
        num = new QSvgWidget(empty);
        box->addWidget(num);
    }
    numbers[11]->load(num0);
    box->addWidget(info);
    setLayout(box);
    resize(200, 200);
}

void AreaViewer::updateArea(double value) {
    currentArea = value;
    QString str = fromValueToStr(value);
    auto len = str.size();
    if (len > 12) len = 12;
    while (previousLen > len) {
        numbers[12 - previousLen]->load(empty);
        --previousLen;
    }
    for (int i = 0; i < len; ++i) {
        setupDigit (numbers[11 - i], str[len - i - 1]);
    }
    previousLen = len;
    
}

void AreaViewer::setupDigit(QSvgWidget* digit, QChar symbol) {
    if (symbol == '0') {
        digit->load(num0);
    } else if (symbol == '1') {
        digit->load(num1);
    } else if (symbol == '2') {
        digit->load(num2);
    } else if (symbol == '3') {
        digit->load(num3);
    } else if (symbol == '4') {
        digit->load(num4);
    } else if (symbol == '5') {
        digit->load(num5);
    } else if (symbol == '6') {
        digit->load(num6);
    } else if (symbol == '7') {
        digit->load(num7);
    } else if (symbol == '8') {
        digit->load(num8);
    } else if (symbol == '9') {
        digit->load(num9);
    } else if (symbol == '.') {
        digit->load(comma);
    } else if (symbol == '-') {
        digit->load(minus);
    }
}

double AreaViewer::getValue(){
    return currentArea;    
}



