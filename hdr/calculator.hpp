#pragma once
#include <functional>

#include "shape_areas.hpp"

class Calculator {
    private:
        std::vector<Result> resultList;
        const std::vector<Shapes::AbstactShape> shapes;
        std::function<void(double)> resultCallback;
        std::function<void(int, Result::action)> listCallback;
        double totalArea = 0;
    public:
        Calculator();
        void setupResultCallback(std::function<void(double)> callback);
        void setupListCallback(std::function<void(int index, Result::action action)> callback);
        const std::vector<Shapes::Option>& shapeOptionsByID (int id) const;
        void calculate(int shapeID, std::string input);
        void edit (int index, std::string newInput);
        void remove (int index);
        void reset();
        const std::vector<Result>& getResultList() const;
        const std::vector<Shapes::AbstactShape>& getShapes() const;
}; 
