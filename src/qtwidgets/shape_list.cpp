#include "shape_list.hpp"

ShapeListWigdet::ShapeListWigdet(Calculator& calc, QWidget* parent):
QScrollArea(parent), calculator{calc}, mainBox{new QVBoxLayout()} {
    mainWidget = new QWidget();
    auto externLayout = new QVBoxLayout();
    externLayout->addLayout(mainBox);
    externLayout->addStretch(1);
    mainWidget->setLayout(externLayout);
    setWidget(mainWidget);
    setWidgetResizable(true);
    setFrameShape(QFrame::NoFrame);
    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
}


void ShapeListWigdet::addItem(const Result& newResult){
    if(visibleWidgets < widgetList.size()){
        widgetList[visibleWidgets]->newShape(newResult);
        widgetList[visibleWidgets]->show();
        widgetList[visibleWidgets]->index = visibleWidgets;
    } else {
        auto shapeView = new ShapeViewer(calculator, newResult);
        widgetList.push_back(shapeView);
        mainBox->addWidget(shapeView);
        shapeView->index = widgetList.size() - 1; 
    }
    visibleWidgets++;
}

void ShapeListWigdet::clear() {
    for(auto widget: widgetList){
        widget->setInvisible();
    }
    visibleWidgets = 0;
}

void ShapeListWigdet::removeItem(int index) {
    if (index < 0 || index >= widgetList.size()) {
         return;       
    }
    widgetList[index]->setInvisible();
    if (index != visibleWidgets) {
        widgetList[index]->setInvisible();
        mainBox->removeWidget(widgetList[index]);
        widgetList.erase(widgetList.begin() + index);
    }
    visibleWidgets--;
    for (auto i = index; i < visibleWidgets; ++i) {
        widgetList[i]->index--;
    }
}

void ShapeListWigdet::updateItem(int index, const Result& newResult) {
    if (index < 0 || index >= widgetList.size()) {
         return;       
    }
    widgetList[index]->newShape(newResult);
}
