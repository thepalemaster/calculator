#include "shape_input.hpp"
#include "result.hpp"
#include "area_view.hpp"
#include "parser.hpp"

#include <QDebug>
#include <iostream>


#ifdef LANG_ENG
    auto factorName = "Factor";
#else 
    auto factorName = "Коэффициент";
#endif

ShapeInput::ShapeInput(int id, QString name, const ShapeModel& model, QWidget* parent):
QWidget(parent), shapeID{id} {
    auto mainLayout = new QVBoxLayout();
    newGroup = new QGroupBox(name);
    currentParamNumber = model.getParamNumber();
    auto innerLayout = new QVBoxLayout();
    formLayout = new QFormLayout();
    auto params = model.getParamNames();
    mainLayout->addWidget(newGroup);
    for (size_t i = 1; i <= currentParamNumber; ++i) {
        auto inputDouble = new QLineEdit();
        inputDouble->setValidator(&validator);
        usedInputLine[i - 1] = inputDouble;
        formLayout->addRow(params[i]->text.data(), inputDouble);
    }
    innerLayout->addLayout(formLayout);
    factorLineEdit = new QLineEdit();
    factorLineEdit->setValidator(&validator);
    formLayout->addRow(factorName, factorLineEdit);
    if (params[5]) {
        auto cbox = new QCheckBox(params[5]->text.data());
        innerLayout->addWidget(cbox);
        usedCheckBox[0] = cbox;
        connect(usedCheckBox[0], QOverload<int>::of(&QCheckBox::stateChanged), this, [this, &model](int state){
            bool second =  usedCheckBox[1] && usedCheckBox[1]->isChecked() ? true : false;
            updateNames(model.updateNames(state, second));
        });
        if (params[6]) {
            auto cbox1 = new QCheckBox(params[6]->text.data());
            innerLayout->addWidget(cbox1);
            usedCheckBox[1] = cbox1;
            connect(usedCheckBox[1], QOverload<int>::of(&QCheckBox::stateChanged), this, [this, &model](int state){
                updateNames(model.updateNames(usedCheckBox[0]->isChecked(), state));
            });
        }
    }
    newGroup->setLayout(innerLayout);
    setLayout(mainLayout);
}

CalculatorParameters ShapeInput::getInput() {
    CalculatorParameters params {};
    for (int i = 0; i < currentParamNumber; ++i) {
        auto str = usedInputLine[i]->text().toLatin1();
        params.numbers[i] = Parser::toDouble(str.data(), str.size());
    }
    const auto factorStr = factorLineEdit->text();
    if (factorStr != "1" && !factorStr.isEmpty()) {
        auto str = factorStr.toLatin1();
        params.setFactor(Parser::toDouble(str.data(), str.size()));
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

bool ShapeInput::getState(int index) {
    if (index >= usedCheckBox.size() || index < 0 || !usedCheckBox[index]){
        return false;
    }
    return usedCheckBox[index]->isChecked();
}

void ShapeInput::updateNames(std::array<const Shapes::Option *, 5> newNames) {
    if (!newNames[0]) return;
    newGroup->setTitle(newNames[0]->text.data());
    int i; 
    for (i = 0; newNames[i + 1] && i < currentParamNumber; ++i) {
        auto label = static_cast<QLabel*>(formLayout->itemAt(i, QFormLayout::LabelRole)->widget());
        label->setText(newNames[i + 1]->text.data());
    }
    while (i < 4 && newNames[i + 1]) {
        usedInputLine[i] = new QLineEdit();
        formLayout->insertRow(currentParamNumber, newNames[i + 1]->text.data(), usedInputLine[i]);
        ++i;
    }
    if (i < currentParamNumber) {
        auto needlessRows = i;
        while (needlessRows < currentParamNumber) {
            formLayout->removeRow(i);
            ++needlessRows;
        }
    }
    currentParamNumber = i;
}

