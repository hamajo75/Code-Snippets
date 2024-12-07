#include <iostream>
#include <string>

/**
 * C++ is different than math.

 Math: Division with Rest
    a = qb + r      a, q, r in Z and b in N, with 0<= r<b
    mit a = -7, b = 5
    -7 = -2 * 5 + 3
    Rest = 3

    In C++ you get -2. (E.g. in Python you get the correct value: 3)
    C++ uses truncate division, Python uses floor division.
    -7 % 5 = -7 – 5 *( trunc(-7/5) ) = -2  - truncate division
    Python: -7 – 5 *( floor(-7/5) ) = 3  - floor division

    Number line:
    -9 -8 -7 -6 -5 -4 -3 -2 -1  0  1  2  3  4  5  6  7  8  9 ...
     0  1  2  0  1  2  0  1  2  0  1  2  0  1  2  0  1  2  0 ...      % 3 (Python)
     0 -2 -1  0 -2 -1  0 -2 -1  0  1  2  0  1  2  0  1  2  0 ...      % 3 (C++)
 */
void ModuloOperator() {
  int a = -7;
  int b = 5;
  int c = a % b;
  std::cout << "a % b = " << c << std::endl;
  c = ((a % b) + b) % b;
  std::cout << "a mod b = " << c << std::endl;
}

//-------------------------------------------------------------------------------
int main() {
  ModuloOperator();

  return 0;
}
