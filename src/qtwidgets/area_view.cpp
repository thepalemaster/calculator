#include "area_view.hpp"

#include <QtWidgets/QComboBox>
#include <QtSvg/QSvgWidget>
#include <cmath>
#include <QLatin1String>

const QLatin1String num0 (":/digits/0.svg");
const QLatin1String num1 (":/digits/1.svg");
const QLatin1String num2 (":/digits/2.svg");
const QLatin1String num3 (":/digits/3.svg");
const QLatin1String num4 (":/digits/4.svg");
const QLatin1String num5 (":/digits/5.svg");
const QLatin1String num6 (":/digits/6.svg");
const QLatin1String num7 (":/digits/7.svg");
const QLatin1String num8 (":/digits/8.svg");
const QLatin1String num9 (":/digits/9.svg");
const QLatin1String comma (":/digits/comma.svg");
const QLatin1String minus (":/digits/minus.svg");
const QLatin1String empty (":/digits/empty.svg");

const double almostIntergral = 1.0e-7;

QString fromValueToStr(const double value) {
    auto rounded = std::lround(value);
    double delta = std::abs(value - rounded);
    QString str;
    if (delta < almostIntergral) {
        str = QString::number(rounded);
    } else {
        str = QString::number(value, 'g', 5);
    }
    return str;
}

AreaViewer::AreaViewer(QWidget *parent):
QWidget(parent), box{new QHBoxLayout()}, info(new QLabel())  {
    box->addStretch();
    for (auto& num: numbers) {
        num = new QSvgWidget(empty);
        box->addWidget(num);
    }
    numbers[11]->load(num0);
    box->addWidget(info);
    setLayout(box);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
}

void AreaViewer::updateArea(double value) {
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

void AreaViewer::setMeasure(QString measureUnit) {
    info->setText(QString("<strong>%1</strong>").arg(measureUnit));
}




