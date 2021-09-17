#include "hdr/calculator.hpp"

template <typename Head, typename ...Tail>
constexpr void addShape(std::vector<Shapes::AbstactShape>& vec, int i) {
    vec.push_back(Head(i));
    ++i;
    if constexpr (sizeof...(Tail) != 0) {
        addShape<Tail...>(vec, i);
    }
}

template <typename ...ArgTypes>
std::vector<Shapes::AbstactShape> generateShapesList() {
    std::vector<Shapes::AbstactShape> vec;
    vec.reserve(sizeof...(ArgTypes));
    addShape<ArgTypes...>(vec, 0);
    return vec;
}

Calculator::Calculator(): shapes{ generateShapesList<Shapes::Rectangle, Shapes::Circle>()} {}

void Calculator::calculate(int id, std::string input) {
    if (id < 0 || id > shapes.size()) return;
    Result tmpResult;
    try {
        tmpResult = shapes[id].calculate(input);
    } catch(std::invalid_argument) {
        return;
    }
    totalArea += tmpResult.area;
    resultList.push_back(std::move(tmpResult)); 
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
    if (index < 0 || index > resultList.size()) return;
    totalArea -= resultList[index].area;
    resultList.erase(resultList.begin() + index);
    resultCallback(totalArea);
    listCallback(index, Result::REMOVE_ITEM);
}


void Calculator::edit (int index, std::string newInput) {
    if (index < 0 || index > resultList.size()) return;
    totalArea -= resultList[index].area;
    try {
        resultList[index] = shapes[resultList[index].shapeID].calculate(newInput);
    } catch(std::invalid_argument) {
        return;
    }
    totalArea += resultList[index].area;
    resultCallback(totalArea);
    listCallback(index, Result::CHANGE_ITEM);
}

const std::vector<Result>& Calculator::getResultList() const{
    return resultList;
}

const std::vector<Shapes::AbstactShape> & Calculator::getShapes() const {
    return shapes;
}

const std::vector<Shapes::Option> & Calculator::shapeOptionsByID(int id) const {
    return shapes[id].getOptions();
}


