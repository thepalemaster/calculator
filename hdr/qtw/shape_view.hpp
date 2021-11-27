#pragma once
#include <QtWidgets/QLabel>
#include <QtWidgets/QHBoxLayout>

#include "shape_model.hpp"
#include "result.hpp"


class ShapeViewer: public QWidget{
private:
    const std::vector<ShapeModel>& models;
    QHBoxLayout* hbox;
    QLabel* shapeInfo;

    
public:
    ShapeViewer(const std::vector<ShapeModel>& modelsList, const Result& shapeResult, QWidget* parent = nullptr);
    void newShape(const Result& shapeResult);
    QString getText(const Result& shapeResult);
};
