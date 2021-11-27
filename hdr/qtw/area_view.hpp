#pragma once

#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>

class AreaViewer: public QWidget {
    //Q_OBJECT
private:
    QHBoxLayout* box;
    QLabel* number;
public:
    explicit AreaViewer(QWidget *parent = nullptr);
public slots:
    void updateArea(double value);
};
