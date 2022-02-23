#include <QApplication>

#include "calcutator_window.hpp"

#ifdef LANG_ENG
    auto applicationTitle = "Area calculator";
#else 
    auto applicationTitle = "Калькулятор площади";
#endif

int main (int argc, char *argv[])
{
    QApplication app(argc, argv);
    Calculator calc;
    CalculatorMainWindow qtWidgetCalc(calc);
    qtWidgetCalc.setWindowTitle(applicationTitle);
    qtWidgetCalc.show();
    return app.exec();
}
