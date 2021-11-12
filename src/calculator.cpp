#include "calculator.hpp"
#include "shape_model.hpp"



template <typename Head, typename ...Tail>//нужно пересмотреть функцию которая всё разрулит
constexpr void addShape(std::vector<std::unique_ptr<Shapes::AbstactShape>>& vec, int i) {
    vec.emplace_back(std::make_unique<Head>(i));
    ++i;
    if constexpr (sizeof...(Tail) != 0) {
        addShape<Tail...>(vec, i);
    }
}

template <typename ...ArgTypes>
std::vector<std::unique_ptr<Shapes::AbstactShape>> generateShapesList() {
    std::vector<std::unique_ptr<Shapes::AbstactShape>> vec;
    std::vector<std::unique_ptr<Shapes::AbstactShape>> vec1;
    vec.reserve(sizeof...(ArgTypes));
    addShape<ArgTypes...>(vec, 0);
    return vec;
}

Calculator::Calculator(): shapes{generateShapesList<Shapes::Rectangle, Shapes::Circle>()} {}

void Calculator::calculate(int shapeID, CalculatorParameters& param) {
    if (shapeID < 0 || shapeID >= shapes.size()) return;
    resultList.emplace_back(shapes[shapeID]->calculate(param), shapeID, param);
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

const std::vector<std::unique_ptr<Shapes::AbstactShape>> & Calculator::getShapes() const {
    return shapes;
}

const std::vector<Shapes::Option> & Calculator::shapeOptionsByID(int id) const {
    return shapes[id]->getOptions();
}

void Calculator::setupListCallback(std::function<void (int, Result::action)> callback) {
    listCallback = callback;
}

void Calculator::setupResultCallback(std::function<void (double)> callback) {
    resultCallback = callback;
}
