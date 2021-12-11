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
    connect(calcButton, &QPushButton::clicked, calcButton, [this, &calc](){
        auto inputWidget = static_cast<ShapeInput*>(stackLayout->currentWidget());
        calc.calculate(inputWidget->shapeID, inputWidget->getInput());
    });
}

void ShapeOptions::addShape(int id, const ShapeModel& model) {
    auto nameString = QString(model.getName()->text.data());
    auto currentButton = buttons->newButton(nameString);
    auto newInput = new ShapeInput(id, nameString, model.getParamNames());
    int index = stackLayout->addWidget(newInput);
    connect(currentButton, &QPushButton::clicked, stackLayout, [currentPage{stackLayout}, index](){
        currentPage->setCurrentIndex(index);
    });
}
