#include <iostream>
#include <limits>
#include <cmath>
#include <sstream>

#include "parser.hpp"
#include "result.hpp"




bool almost_equal(double x, double y, int ulp) {
    return std::fabs(x-y) <= std::numeric_limits<double>::epsilon() * std::fabs(x+y) * ulp
    || std::fabs(x-y) < std::numeric_limits<double>::min();
}

bool almost_equal(CalculatorParameters x, CalculatorParameters y) {
    return almost_equal(x.numbers[0], y.numbers[0], 2) &&
         almost_equal(x.numbers[1], y.numbers[1], 2) &&
         almost_equal(x.numbers[2], y.numbers[2], 2) &&
         almost_equal(x.numbers[3], y.numbers[3], 2) &&
         almost_equal(x.factor, y.factor, 2)&&
         x.options[0] == y.options[0] && x.options[1] == y.options[1];
}

void make_test (std::string s, double y) {
    double x;
    try {
        x = Parser::toDouble(s.data(), s.size());
    } catch (std::invalid_argument) {
        std::cout << "[-] Incorrect parse: \"" << s << "\". Parse function throw exception (expected value = " << y << ")" << '\n';
        return;
    }
    if (almost_equal(x, y, 2)) {
        std::cout << "[+] Correct parse: \"" << s << "\" equal " << y << '\n';
    } else {
        std::cout << "[-] Incorrect parse: \"" << s << "\" NOT equal " << x << " (expected value = " << y << ")" << '\n';
    }
}

void make_test_int_zero (std::string s, int y) {
    int x;
    x = Parser::pureIntOrZero(s);
    if (x = y) {
        std::cout << "[+] Correct parse: \"" << s << "\" equal " << y << '\n';
    } else if (y == 0) {
        std::cout << "[+] Correct parse: function return 0 for value \"" << s << "\"\n";
    } else {
        std::cout << "[-] Incorrect parse: \"" << s << "\" NOT equal " << x << " (expected value = " << y << ")" << '\n';
    }
}


std::string to_string (CalculatorParameters z) {
    std::ostringstream stream;
    stream << "{";
    for (int i = 0; i < 4; ++i) {
        if (z.numbers[i] == 0) {
            break;
        }
        if (i != 0) stream << ", ";
        stream << "num" << i + 1 << ": " << z.numbers[i];
    }
    if (z.options[0]) {
        stream << ", option1: ON";
        if (z.options[1]) {
            stream << ", option2: ON";
        }
    }
    if (z.factor != 1.) {
        stream << ", factor: " << z.factor;
    }
    stream << "}";
    return stream.str();
}


void make_console_test (std::string s, int number, CalculatorParameters z) {
    CalculatorParameters x;
    try {
        x = Parser::getCalcParams(s.data(), s.size(), number);
    } catch (std::invalid_argument) {
        std::cout << "[-] Incorrect parse: \"" << s << "\"(param number:" << number << "). Parse function throw exception (expected value = " << to_string(z) << ")" << '\n';
        return;
    }
    if (almost_equal(x, z)) {
        std::cout << "[+] Correct parse: \"" << s << "\" (param number:" << number << ") equal " << to_string(z) << '\n';
    } else {
        std::cout << "[-] Incorrect parse: \"" << s << "\" (param number:" << number << ") NOT equal " << to_string(x) << " (expected value = " << to_string(z) << ")" << '\n';
    }
}



int main () {
    std::cout << "--- Test of Parser::toDouble function ---\n";
    make_test ("12.8+ 1,7", 14.5);
    make_test ("+ 1 ", 1);
    make_test ("- 1 ", -1);
    make_test ("45,5 - 55.6", -10.1);
    make_test ("  + 2 -  -  1", 3);
    make_test ("", 0);
    make_test ("+ +", 0);
    make_test (" 45. 45", 45);
    make_test ("+45- 12.5+7 -0,5 - 8,7", 30.3);
    
    std::cout << "--- Test of Parser::getCalcParams function ---\n";    
    CalculatorParameters param {12., 2., 5.};
    param.setFactor(5);
    make_console_test ("12 2 5 5", 3, param);
    param = CalculatorParameters {12., 2., 5., 5.};
    make_console_test ("12 2 5 5", 4, param);
    param = CalculatorParameters{1.};
    make_console_test (" +1 ", 1, param);
    param = CalculatorParameters {100., 12.};
    make_console_test ("100   12", 2, param);
    param = CalculatorParameters {100., 12.};
    param.setFactor(6);
    make_console_test ("100   12   6", 2, param);
    param = CalculatorParameters {};
    make_console_test ("", 1, param);
    param = CalculatorParameters {true, true, 4.4, 5.4, 4.66, -6.01};
    param.setFactor(3.14);
    make_console_test ("4.4   5,4 +4.66 -6.01 3.14 + +", 4, param);
    param = CalculatorParameters {true, 4.75};
    param.setFactor(8.6);
    make_console_test ("4.5+2.5-1,5-0,75 7,6+1 +", 1, param);
    param = CalculatorParameters {true, true, 3, 4 };
    make_console_test ("3 4 + +", 2, param);
    
    std::cout << "--- Test of Parser::pureIntOrZero function ---\n";
    make_test_int_zero(" 1", 1);
    make_test_int_zero("a", 0);
    make_test_int_zero("1 d", 0);
    make_test_int_zero("   4  ", 4);
    make_test_int_zero("-45j", 0);
    make_test_int_zero("-5", -5);
}
