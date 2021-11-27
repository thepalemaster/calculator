#include "calcutator_window.hpp"

CalculatorMainWindow::CalculatorMainWindow(Calculator& calc, QWidget* parent):
    QWidget{parent}, vbox{new QVBoxLayout(this)}, number{new AreaViewer()}, 
    listViewer{new ShapeListWigdet(calc.models)} {
    calc.setupResultCallback([this](double value){number->updateArea(value);});
    calc.setupListCallback([this, &calc](int index, Result::action action){
        switch (action) {
            case Result::NEW_ITEM:
                listViewer->addItem(calc.getResultList()[index]);
                break;
            case Result::RESET:
                listViewer->clear();
                break;
            case Result::CHANGE_ITEM:
                listViewer->updateItem(index, calc.getResultList()[index]);
                break;
            case Result::REMOVE_ITEM:
                listViewer->removeItem(index);
                break;
            default:
                break;
        }
    });
    auto options = new ShapeOptions(calc);
    for(auto& currentModel: calc.models) {
        options->addShape(currentModel);
    }
    vbox->addWidget(options);
    vbox->addWidget(number);
    vbox->addWidget(listViewer);
    setLayout(vbox);
}
