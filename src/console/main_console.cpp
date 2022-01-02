#include "console_view.hpp"


int main () {
    auto calc = Calculator();
    auto viewer = ConsoleView(calc);
    viewer.mainLoop();
}
