#pragma once
#include <functional>
#include <utility>

#include "shape_areas.hpp"
#include "shape_model.hpp"


class Calculator {
    private:
        std::vector<Result> resultList;
        const std::vector<std::unique_ptr<Shapes::AbstactShape>> shapes;
        std::function<void(double)> resultCallback;
        std::function<void(int, Result::action)> listCallback;
        double totalArea = 0;
    public:
        const std::vector<ShapeModel> models;
        Calculator();
        void setupResultCallback(std::function<void(double)> callback);
        void setupListCallback(std::function<void(int index, Result::action action)> callback);
        const std::vector<Shapes::Option>& shapeOptionsByID (int id) const;
        void calculate(int shapeID, const CalculatorParameters& param);
        void edit (int index, CalculatorParameters& param);
        void remove (int index);
        void reset();
        const std::vector<Result>& getResultList() const;
        const std::vector<std::unique_ptr<Shapes::AbstactShape>>& getShapes() const;
}; 
