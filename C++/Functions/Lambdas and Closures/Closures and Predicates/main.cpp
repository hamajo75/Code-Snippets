#include <stdio.h>
#include <iostream>
#include <string.h>
#include <vector>

// always use auto when assigning lambda expressions
// lambda expresseion: [=](int x) { return x + y; } - syntax
// closure: the unnamed function object corresponding to the expression
// Note: A class exists only in source code; it doesn't exist at runtime. Same thing.

/* Capture clauses:
[=]     -  capture all variables in scope by copy
[&]     -  capture all variables in scope by reference
[x]     - a specific variable (by copy)
[&x]    - a specific variable (by ref)
[x = 1] - initialize
*/

//-------------------------------------------------------------------------------
/* Traverse a container and do something with each element.
*/
template<typename C, typename O>
void for_all(C& container, O operation) { // assume that C is a container of pointers
  for (auto& x : container)
    operation(x);          // pass a reference to each element pointed to
}
//-------------------------------------------------------------------------------
/* Predicate: return true or false
*/
template<typename C, typename P>
int count(const C& container, P predicate) {
  int cnt = 0;
  for (const auto& x : container) {
    if (predicate(x))
      ++cnt;
  }
  return cnt;
}
//-------------------------------------------------------------------------------
template<typename C>
void print(C container){
  for(const auto& x: container)
    std::cout << x << std::endl;
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {  
  int y = 100;

  auto closure = [=](int x) { return x + y; };  // can access y ! - closure
  auto closure_ref = [&](int x) { return x + y; };  // can access y ! - closure
  std::cout << "closure(2): " << closure(2) << std::endl;  // gives: 102
  y = 200;
  std::cout << "closure(2): " << closure(2) << std::endl;  // gives also 102, the value was captured at declaration
  std::cout << "closure_ref(2): " << closure_ref(2) << std::endl;  // make sure y still exists!

  std::cout << "Use a lambda as a predicate:" << std::endl;
  std::vector<int> v{1, 2, 3, 4};
  int x = 4;
  std::cout << count(v, [&](int a) { return a < x;}) << std::endl;

  std::cout << "Multiply all elements by 2:" << std::endl;
  for_all(v, [](int& a) { a *= 2; });
  print(v);
}
