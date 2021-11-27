#include "shape_options.hpp"
#include "shape_input.hpp"

ShapeOptions::ShapeOptions(Calculator& calc, QWidget* parent): 
QWidget(parent), buttons{new ShapeButtons()}, stackLayout{new QStackedLayout()}{
    auto vbox = new QVBoxLayout();
    vbox->addWidget(buttons);
    vbox->addLayout(stackLayout);
    auto calcButton = new QPushButton("КАЛЬКУЛИРОВАТЬ");
    vbox->addWidget(calcButton);
    setLayout(vbox);
    connect(calcButton, &QPushButton::clicked, [this, &calc](){
        auto inputWidget = static_cast<ShapeInput*>(stackLayout->currentWidget());
        calc.calculate(0, inputWidget->getInput());
    });
}

void ShapeOptions::addShape(const ShapeModel& model) {
    auto nameString = QString(model.getName()->text.data());
    auto currentButton = buttons->newButton(nameString);
    auto newInput = new ShapeInput(nameString, model.getParamNames());
    int index = stackLayout->addWidget(newInput);
    connect(currentButton, &QPushButton::clicked, stackLayout, [currentPage{stackLayout}, index](){
        currentPage->setCurrentIndex(index);
    });
}

void updateShape(int index){};

void sendData();
