#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFormLayout>

#include "shape_input.hpp"
#include "result.hpp"
#include "area_view.hpp"


ShapeInput::ShapeInput(int id, QString name, std::array<const Shapes::Option*, 7> params, QWidget* parent):
QWidget(parent), shapeID{id} {
    auto mainLayout = new QVBoxLayout();
    auto newGroup = new QGroupBox(name);
    auto innerLayout = new QVBoxLayout();
    auto formLayout = new QFormLayout();
    mainLayout->addWidget(newGroup);
    for (int i = 1; i < 5; ++i) {
        if (!params[i]) break;
        auto inputDouble = new QLineEdit();
        usedInputLine[i - 1] = inputDouble;
        formLayout->addRow(params[i]->text.data(), inputDouble);
        innerLayout->addLayout(formLayout);
    }
    factorLineEdit = new QLineEdit();
    formLayout->addRow("Коэффициент", factorLineEdit);
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
            params.numbers[i] = (usedInputLine[i]->text().toDouble());
        }
    }
    const auto factorStr = factorLineEdit->text();
    if (factorStr != "1" && !factorStr.isEmpty()) {
        params.setFactor(factorStr.toDouble());
    }
    for (int i = 0; i < 2; ++i) {
        if (usedCheckBox[i]) {
            params.options[i] = (usedCheckBox[i]->isChecked());
        }
    }
    return params;
}

void ShapeInput::setInput(const Result& result){ 
    for(size_t i = 0; i < result.param.numbers.size(); ++i) {
        if (result.param.numbers[i]){
            usedInputLine[i]->setText(fromValueToStr(result.param.numbers[i]));
        } else {
            break;
        }
    }
    factorLineEdit->setText(fromValueToStr(result.param.factor));
    for (size_t i = 0; i < result.param.options.size(); ++i) {
        if (result.param.options[i]) {
            usedCheckBox[i]->setCheckState(Qt::CheckState::Checked);
        }
    }
}
