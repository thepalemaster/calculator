#pragma once
#include <functional>
#include <utility>

#include "shape_areas.hpp"
#include "shape_model.hpp"


class Calculator final {
private:
    std::vector<Result> resultList;
    const std::vector<std::unique_ptr<Shapes::AbstractShape>> shapes;
    std::function<void(double)> resultCallback;
    std::function<void(int, Result::action)> listCallback;
    void normalizeParams(CalculatorParameters& calc);
    double totalArea = 0;
    double ratio = 1;
    double inputMagnitude = 1;
    double outputMagnitude= 1;
public:
    const std::vector<ShapeModel> models;
    Calculator();
    void setupResultCallback(std::function<void(double)> callback);
    void setupListCallback(std::function<void(int index, Result::action action)> callback);
    const std::vector<Shapes::Option>& shapeOptionsByID (int id) const;
    void edit (int index, CalculatorParameters& param);
    void remove (int index);
    void reset();
    void setMeasureOutput(double value);
    void setMeasureInput(double value);
    const std::vector<Result>& getResultList() const;
    const Result& getResult(int index) const;
    const std::vector<std::unique_ptr<Shapes::AbstractShape>>& getShapes() const;
    void calculate(int shapeID, CalculatorParameters& param);
};
