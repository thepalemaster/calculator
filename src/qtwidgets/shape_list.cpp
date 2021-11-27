#include "shape_list.hpp"

ShapeListWigdet::ShapeListWigdet(const std::vector<ShapeModel>& modelsList, QWidget* parent):
QWidget(parent), models{modelsList}, mainBox(new QVBoxLayout()){
    setLayout(mainBox);
}


void ShapeListWigdet::addItem(const Result& newResult){
    if(visibleWidgets < widgetList.size()){
        widgetList[visibleWidgets]->newShape(newResult);
        widgetList[visibleWidgets]->show();
    } else {
        auto shapeView = new ShapeViewer(models, newResult);
        widgetList.push_back(shapeView);
    }
    visibleWidgets++;
}

void ShapeListWigdet::clear() {
    for(auto widget: widgetList){
        widget->hide();
    }
    visibleWidgets = 0;
}

void ShapeListWigdet::removeItem(int index) {
    if (index < 0 || index >= widgetList.size()) {
         return;       
    }
    if (index == visibleWidgets) {
        widgetList[index]->hide();
    } else {
        mainBox->removeWidget(widgetList[index]);
        widgetList.erase(widgetList.begin() + index);
    }
    visibleWidgets--;
}

void ShapeListWigdet::updateItem(int index, const Result& newResult) {
    if (index < 0 || index >= widgetList.size()) {
         return;       
    }
    widgetList[index]->newShape(newResult);
}
