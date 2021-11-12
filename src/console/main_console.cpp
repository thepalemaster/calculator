#include <iostream>

#include "hdr/console_view.hpp"


int main () {
    auto calc = Calculator();
    auto viewer = ConsoleView(calc);
    viewer.mainLoop();
}
