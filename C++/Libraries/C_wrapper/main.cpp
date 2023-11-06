// main.cpp

#include <iostream>
#include "mathlib_wrapper.h"

int main() {
    MathLibWrapper mathLib;

    int a = 10;
    int b = 5;

    int sum = mathLib.add(a, b);
    int difference = mathLib.subtract(a, b);

    std::cout << "Sum: " << sum << std::endl;
    std::cout << "Difference: " << difference << std::endl;

    return 0;
}
