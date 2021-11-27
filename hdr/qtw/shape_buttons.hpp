#pragma once
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>

class ShapeButtons: public QWidget {
private:
    QGridLayout* buttonLayout;
    int buttonCounter = 0;
public:
    ShapeButtons(QWidget* parent = nullptr);
    QPushButton* newButton(const QString& name);
};
