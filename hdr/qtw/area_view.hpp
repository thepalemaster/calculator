#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>

class QSvgWidget;

QString fromValueToStr(double value);

class AreaViewer: public QWidget {
    //Q_OBJECT
private:
    bool powerFlag = false;
    QLabel* fullNumber;
    int previousLen = 0;
    double currentArea = 0;
    QHBoxLayout* box;
    QLabel* info;
    std::array<QSvgWidget*, 12> numbers;
    void setupDigit(QSvgWidget* digit, QChar symbol);
    
public:
    explicit AreaViewer(QWidget *parent = nullptr);
    double getValue();
    
public slots:
    void updateArea(double value);
    void setMeasure(QString measureUnit);
};


