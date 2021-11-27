#pragma once

#include "shape_list.hpp"
#include "shape_options.hpp"
#include "area_view.hpp"

class CalculatorMainWindow: public QWidget {
    
private:
    QVBoxLayout*  vbox; 
    AreaViewer* number;
    ShapeListWigdet* listViewer;
    void updadeArea(double value);
    
public:
    CalculatorMainWindow(Calculator& calc, QWidget* parent = nullptr);
    
signals:
    void setArea(double value);
};
