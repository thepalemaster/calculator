#pragma once
#include <QtWidgets/QVBoxLayout>

#include "shape_view.hpp"

class ShapeListWigdet: public QWidget{
private:
    std::vector<ShapeViewer*> widgetList;
    const std::vector<ShapeModel>& models;
    int visibleWidgets = 0;
    QVBoxLayout* mainBox;
    
    
public:
   ShapeListWigdet(const std::vector<ShapeModel>& modelsList, QWidget* parent = nullptr);
   void updateItem (int index, const Result& newResult);
   void removeItem (int index);
   void addItem(const Result& newResult);
   void clear();
};
