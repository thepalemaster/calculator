#include "qml_calculator.hpp"
#include "parser.hpp"

#include <QDebug>


CalculatorWrapper::ShapeInputView::ShapeInputView(QObject* parent):
QObject(parent){
    setupShape(0);
}

void CalculatorWrapper::ShapeInputView::setupShape(int id) {
    auto& calc = getCalculator();
    auto& model = calc.models[id];
    auto tempNames = model.getParamNames();
    if (currentNames[0] != tempNames[0]) {
        currentNames[0] = tempNames[0];
        emit nameChanged();
    }
    if (currentNames[1] != tempNames[1]) {
        currentNames[1] = tempNames[1];
        emit fieldChanged1();
    }
    if (currentNames[2] != tempNames[2]) {
        currentNames[2] = tempNames[2];
        emit fieldChanged2();
    }
    if (currentNames[3] != tempNames[3]) {
        currentNames[3] = tempNames[3];
        emit fieldChanged3();
    }
    if (currentNames[4] != tempNames[4]) {
        currentNames[4] = tempNames[4];
        emit fieldChanged4();
    }
    if (currentNames[5] != tempNames[5]) {
        currentNames[5] = tempNames[5];
        emit optionChanged1();
    }
    if (currentNames[6] != tempNames[6]) {
        currentNames[6] = tempNames[6];
        emit optionChanged2();
    }
    currentShape = id;
}

void CalculatorWrapper::ShapeInputView::setupNames(bool first, bool second) {
    auto& calc = getCalculator();
    auto& model = calc.models[currentShape];
    auto tempNames = model.updateNames(first, second);
    if (currentNames[0] != tempNames[0]) {
        currentNames[0] = tempNames[0];
        emit nameChanged();
    }
    if (currentNames[1] != tempNames[1]) {
        currentNames[1] = tempNames[1];
        emit fieldChanged1();
    }
    if (currentNames[2] != tempNames[2]) {
        currentNames[2] = tempNames[2];
        emit fieldChanged2();
    }
    if (currentNames[3] != tempNames[3]) {
        currentNames[3] = tempNames[3];
        emit fieldChanged3();
    }
    if (currentNames[4] != tempNames[4]) {
        currentNames[4] = tempNames[4];
        emit fieldChanged4();
    }
}

QString CalculatorWrapper::ShapeInputView::name() {
    if (!currentNames[0]) {
        return "";
    }
    return currentNames[0]->text.data();
}

QString CalculatorWrapper::ShapeInputView::fieldName1() {
    if (!currentNames[1]) {
        return "";
    }
    return currentNames[1]->text.data();
}

QString CalculatorWrapper::ShapeInputView::fieldName2() {
    if (!currentNames[2]) {
        return "";
    }
    return currentNames[2]->text.data();
}

QString CalculatorWrapper::ShapeInputView::fieldName3() {
    if (!currentNames[3]) {
        return "";
    }
    return currentNames[3]->text.data();
}

QString CalculatorWrapper::ShapeInputView::fieldName4() {
    if (!currentNames[4]) {
        return "";
    }
    return currentNames[4]->text.data();
}

QString CalculatorWrapper::ShapeInputView::optionName1() {
    if (!currentNames[5]) {
        return "";
    }
    return currentNames[5]->text.data();
}

QString CalculatorWrapper::ShapeInputView::optionName2() {
    if (!currentNames[6]) {
        return "";
    }
    return currentNames[6]->text.data();
}

void CalculatorWrapper::ShapeInputView::calculate(QString num1, QString num2, QString num3, QString num4, bool first, bool second){
    CalculatorParameters params;
    auto str = num1.toLatin1();
    params.numbers[0] = Parser::toDouble(str.data(), str.size());
    str = num2.toLatin1();
    params.numbers[1] = Parser::toDouble(str.data(), str.size());
    str = num3.toLatin1();
    params.numbers[2] = Parser::toDouble(str.data(), str.size());
    str = num4.toLatin1();
    params.numbers[3] = Parser::toDouble(str.data(), str.size());
    params.options = {first, second};
    auto& calc = getCalculator();
    calc.calculate(currentShape, params);
}
