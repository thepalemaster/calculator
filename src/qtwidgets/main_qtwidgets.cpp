#include <QApplication>

#include "calcutator_window.hpp"

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    Calculator calc;
    CalculatorMainWindow qtWidgetCalc(calc);
    qtWidgetCalc.show();
    return app.exec();
    
}