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
    CalculatorMainWindow qtWidgetCalc;
    qtWidgetCalc.setWindowTitle(applicationTitle);
    qtWidgetCalc.show();
    return app.exec();
}
