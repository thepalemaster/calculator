#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>

class QSvgWidget;

class AreaViewer: public QWidget {
    //Q_OBJECT
private:
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
};
