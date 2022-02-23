#include <cmath>
#include <stdexcept>

#include "calculator.hpp"

template <typename Head, typename ...Tail>
constexpr void addShape(std::vector<std::unique_ptr<Shapes::AbstractShape>>& vec, int i) {
    vec.emplace_back(std::make_unique<Head>(i));
    ++i;
    if constexpr (sizeof...(Tail) != 0) {
        addShape<Tail...>(vec, i);
    }
}

template <typename ...ArgTypes>
auto generateShapesList() {
    std::vector<std::unique_ptr<Shapes::AbstractShape>> vec;
    std::vector<std::unique_ptr<Shapes::AbstractShape>> vec1;
    vec.reserve(sizeof...(ArgTypes));
    addShape<ArgTypes...>(vec, 0);
    return vec;
}

std::vector<ShapeModel> generateModels(const std::vector<std::unique_ptr<Shapes::AbstractShape>>& shapes){
    std::vector<ShapeModel> models;
    models.reserve(shapes.size());
    for(auto& shape: shapes) {
        models.emplace_back(shape->getOptions());
    }
    return models;
}

Calculator::Calculator():
shapes{generateShapesList<
    Shapes::Rectangle, Shapes::Circle, Shapes::Cylinder,
    Shapes::Sphere, Shapes::Hexagon, Shapes::Bushing, Shapes::HexPrism,
    Shapes::Cuboid>()}, models{generateModels(shapes)} {}

void Calculator::calculate(int shapeID, CalculatorParameters& param) {
    if (shapeID < 0 || shapeID >= shapes.size()) return;
    auto number = models[shapeID].getParamNumber();
    for (int i = 0; i < number; ++i) {
        if (!param.numbers[i]) return;
    }
    normalizeParams(param);
    resultList.emplace_back(
        shapes[shapeID]->calculate(param) * param.factor / ratio, shapeID, param);
    totalArea += resultList.back().area;
    resultCallback(totalArea); 
    listCallback(resultList.size() - 1, Result::NEW_ITEM);
}

void Calculator::reset(){
    totalArea = 0;
    resultList.clear();
    resultCallback(0);
    listCallback(0, Result::RESET);
}

void Calculator::remove(int index){
    if (index < 0 || index >= resultList.size()) return;
    totalArea -= resultList[index].area;
    resultList.erase(resultList.begin() + index);
    resultCallback(totalArea);
    listCallback(index, Result::REMOVE_ITEM);
}

void Calculator::edit (int index, CalculatorParameters& param) {
    if (index < 0 || index >= resultList.size()) return;
    auto number = models[resultList[index].shapeID].getParamNumber();
    for (int i = 0; i < number; ++i) {
        if (!param.numbers[i]) return;
    }
    normalizeParams(param);
    totalArea -= resultList[index].area;
    resultList[index].param = param;
    resultList[index].area = shapes[resultList[index].shapeID]->calculate(param);
    totalArea += resultList[index].area;
    resultCallback(totalArea);
    listCallback(index, Result::CHANGE_ITEM);
}

const std::vector<Result>& Calculator::getResultList() const{
    return resultList;
}

void Calculator::normalizeParams(CalculatorParameters& calc) {
    for(auto& x: calc.numbers) {
        if (x < 0) {
            x = -x;
            if (calc.factor > 0) {
                calc.factor = -calc.factor;
            }
        }
    }
}

const std::vector<std::unique_ptr<Shapes::AbstractShape>> & Calculator::getShapes() const {
    return shapes;
}

const std::vector<Shapes::Option> & Calculator::shapeOptionsByID(int id) const {
    return shapes[id]->getOptions();
}

void Calculator::setupListCallback(std::function<void (int, Result::action)> callback) {
    listCallback = callback;
}

const Result& Calculator::getResult(int index) const {
    if (index < 0 || index >= resultList.size()) {
        throw std::out_of_range("Unknown shape ID");
    }
    return resultList[index];
}


void Calculator::setupResultCallback(std::function<void (double)> callback) {
    resultCallback = callback;
}

void Calculator::setMeasureOutput(double value) {
    if (!std::isnormal(value)) return;
    double updateFactor = outputMagnitude / value;
    for (size_t i = 0; i < resultList.size(); ++i) {
        resultList[i].area *= updateFactor;
        listCallback(i, Result::CHANGE_ITEM);
    }
    totalArea *= updateFactor;
    resultCallback(totalArea);
    outputMagnitude = value;
    double newRatio = outputMagnitude / inputMagnitude;
    newRatio *= newRatio;
    ratio = newRatio;
}

void Calculator::setMeasureInput(double value) {
    if (!std::isnormal(value)) return;
    double updateFactor = inputMagnitude / value;
    for (size_t i = 0; i < resultList.size(); ++i) {
        for (auto& num: resultList[i].param.numbers){
            num *= updateFactor;
        }
        listCallback(i, Result::CHANGE_ITEM);
    }
    inputMagnitude = value;
    double newRatio = outputMagnitude / inputMagnitude;
    newRatio *= newRatio;
    ratio = newRatio;
}
