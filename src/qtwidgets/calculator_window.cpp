#include "calcutator_window.hpp"

CalculatorMainWindow::CalculatorMainWindow(Calculator& calc, QWidget* parent):
    QWidget{parent}, vbox{new QVBoxLayout(this)}, number{new AreaViewer()}, 
    listViewer{new ShapeListWigdet(calc)} {
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
    for (int i = 0; i < calc.models.size(); ++i) {
        options->addShape(i, calc.models[i]);
    }
    vbox->addWidget(options);
    vbox->addWidget(number);
    vbox->addWidget(listViewer);
    setLayout(vbox);
}
