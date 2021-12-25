#pragma once
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QScrollArea>

#include "shape_view.hpp"

class ShapeListWigdet: public QScrollArea{
    //Q_OBJECT
private:
    std::vector<ShapeViewer*> widgetList;
    Calculator& calculator;
    int visibleWidgets = 0;
    QVBoxLayout* mainBox;
    QWidget* mainWidget;
public:
   ShapeListWigdet(Calculator& calc, QWidget* parent = nullptr);
   void updateItem (int index, const Result& newResult);
   void removeItem (int index);
   void addItem(const Result& newResult);
   void clear();
};
