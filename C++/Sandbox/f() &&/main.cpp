#include <iostream>
#include <string>
#include <vector>

struct X {
  // can be invoked on lvalue
  void f() & { std::cout << "f() &" << std::endl; }

  // can be invoked on rvalue
  void f() && { std::cout << "f() &&" << std::endl; }
};

//-------------------------------------------------------------------------------
int main() {
  X x;

  x.f();  // invokes the first function
         // because x is a named object, hence lvalue

  X().f();  // invokes the second function
           // because X() is an unnamed object, hence rvalue
  return 0;
}
