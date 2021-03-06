#include <QtWidgets/QComboBox>
#include <QtWidgets/QBoxLayout>

#include "measure_units.hpp"
#include "utility_measure_units_qt.hpp"
#include "calculator.hpp"

#ifdef LANG_ENG
    auto outputUnits = "Output units :";
    auto inputUnits = "Input units :";
#else 
    auto outputUnits = "Единицы ввода :";
    auto inputUnits = "Единицы вывода :";
#endif

MeasureUnits::MeasureUnits (Calculator& calc, QWidget *parent):
QWidget(parent) {
    auto labelInput = new QLabel(outputUnits);
    comboInput = new QComboBox();
    comboInput->addItems(Utility::getLenghtList());
    connect(comboInput, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [&calc](int index){
        calc.setMeasureInput(Utility::magnitudeByIndex(index));
    });
    auto labelOutput = new QLabel(inputUnits);
    comboOutput = new QComboBox();
    comboOutput->addItems(Utility::getAreaList());
    connect(comboOutput, QOverload<int>::of(&QComboBox::currentIndexChanged), this, [this, &calc](int index){
        calc.setMeasureOutput(Utility::magnitudeByIndex(index));
        emit changedInputName(Utility::getShortName(index));
    });
    auto measureBox = new QHBoxLayout();
    measureBox->addWidget(labelInput);
    measureBox->addWidget(comboInput);
    measureBox->addWidget(labelOutput);
    measureBox->addWidget(comboOutput);
    measureBox->addStretch();
    setLayout(measureBox); 
}


void MeasureUnits::setDefaults() {
    comboInput->setCurrentIndex(4);
    comboOutput->setCurrentIndex(1);
}


