#include <QClipboard>

#include "calcutator_window.hpp"
#include "measure_units.hpp"


CalculatorMainWindow::CalculatorMainWindow(Calculator& calc, QWidget* parent):
    QWidget{parent}, vbox{new QVBoxLayout()}, number{new AreaViewer()}, 
    listViewer{new ShapeListWigdet(calc)} {
    calc.setupResultCallback([this](double value){number->updateArea(value);});
    calc.setupListCallback([this, &calc](int index, Result::action action){
        switch (action) {
            case Result::NEW_ITEM:
                listViewer->addItem(calc.getResult(index));
                break;
            case Result::RESET:
                listViewer->clear();
                break;
            case Result::CHANGE_ITEM:
                listViewer->updateItem(index, calc.getResult(index));
                break;
            case Result::REMOVE_ITEM:
                listViewer->removeItem(index);
                break;
            default:
                break;
        }
    });
    auto options = new ShapeOptions(calc);
    auto measure = new MeasureUnits(calc);
    for (int i = 0; i < calc.models.size(); ++i) {
        options->addShape(i, calc.models[i]);
    }
    connect(measure, &MeasureUnits::changedInputName, number, &AreaViewer::setMeasure);
    vbox->addWidget(options);
    vbox->addWidget(measure);
    vbox->addWidget(number);
    vbox->addWidget(listViewer);
    auto buttonBox = new QHBoxLayout();
    auto buttonClear = new QPushButton("Очистить");
    connect(buttonClear, &QPushButton::clicked, this, [&calc](){
        calc.reset();
    });
    auto buttonClipboard = new QPushButton("Скопировать");
    connect(buttonClipboard, &QPushButton::clicked, this, [this, copyBuffer = QApplication::clipboard()](){
        copyBuffer->setText(QString::number(number->getValue()));
    });
    buttonBox->addWidget(buttonClear);
    buttonBox->addWidget(buttonClipboard);
    vbox->addLayout(buttonBox);
    setLayout(vbox);
    measure->setDefaults();
    resize(0, 800);
}
