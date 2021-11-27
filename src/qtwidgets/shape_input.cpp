#include "shape_input.hpp"
#include "result.hpp"
#include <QtWidgets/QGroupBox>


ShapeInput::ShapeInput(QString name, std::array<const Shapes::Option*, 7> params, QWidget* parent):
QWidget(parent) {
    auto mainLayout = new QVBoxLayout();
    auto newGroup = new QGroupBox(name);
    auto innerLayout = new QVBoxLayout();
    mainLayout->addWidget(newGroup);
    for (int i = 1; i < 5; ++i) {
        if (!params[i]) break;
        auto nameLabel = new QLabel(params[i]->text.data());
        auto inputDouble = new QLineEdit();
        usedInputLine[i - 1] = inputDouble;
        auto inputBox = new QHBoxLayout();
        inputBox->addWidget(nameLabel);
        inputBox->addWidget(inputDouble);
        innerLayout->addLayout(inputBox);
    }
    if (params[5]) {
        auto cbox = new QCheckBox(params[5]->text.data());
        innerLayout->addWidget(cbox);
        usedCheckBox[0] = cbox; 
        if (params[6]) {
            auto cbox = new QCheckBox(params[6]->text.data());
            innerLayout->addWidget(cbox);
            usedCheckBox[1] = cbox;
        }
    }
    newGroup->setLayout(innerLayout);
    setLayout(mainLayout);
}

CalculatorParameters ShapeInput::getInput() {
    CalculatorParameters params {};
    for (int i = 0; i < 4; ++i) {
        if (usedInputLine[i]) {
            params.numbers[i] = (usedInputLine[i + 1]->text().toDouble());
        }
    }
    for (int i = 0; i < 2; ++i) {
        if (usedCheckBox[i]) {
            params.options[i] = (usedCheckBox[i + 1]->isChecked());
        }
    }
    return params;
}