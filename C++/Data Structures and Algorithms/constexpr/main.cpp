#include <iostream>
#include <string>

/*
- implicitly thread-safe.
- constexpr functions have the potential to run at compile time.

*/
constexpr double myDouble= 5.2;

constexpr int square(int x) { return x * x; }

constexpr auto gcd(int a, int b) {
  while (b != 0){
    auto t= b;
    b= a % b;
    a= t;
  }
  return a;
}

int main() {

 std::cout << std::endl;

  constexpr int i= gcd(11,121);     // (1) compile time

  int a= 11;
  int b= 121;
  int j= gcd(a,b);                  // (2) runtime

  std::cout << "gcd(11,121): " << i << std::endl;
  std::cout << "gcd(a,b): " << j << std::endl;

  std::cout << std::endl;

  int arrayNewWithConstExpression[square(10)];    // this is nice
}
