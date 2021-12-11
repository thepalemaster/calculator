#pragma once
#include <QtWidgets/QVBoxLayout>

#include "shape_view.hpp"

class ShapeListWigdet: public QFrame{
    //Q_OBJECT
private:
    std::vector<ShapeViewer*> widgetList;
    Calculator& calculator;
    int visibleWidgets = 0;
    QVBoxLayout* mainBox;
public:
   ShapeListWigdet(Calculator& calc, QWidget* parent = nullptr);
   void updateItem (int index, const Result& newResult);
   void removeItem (int index);
   void addItem(const Result& newResult);
   void clear();
};
