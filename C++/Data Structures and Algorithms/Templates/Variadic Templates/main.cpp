#include <iostream>
#include <string.h>

//   template <typename ...Args> pimpl
//     (Args&& ...args);

// // forwarding constructor
// template<typename T>
// template<typename... Args>
// pimpl<T>::pimpl(Args &&... args)
//   : impl{new T{std::forward<Args>(args)... }} {

// }

//-------------------------------------------------------------------------------
// unpack parameters using fold expressions
template<typename ...T>
auto sum(const T& ... x) {
  return (x + ...);  // fold expression
}
//-------------------------------------------------------------------------------
// if fold expression doesn't work, use recursion
template<typename T>
auto sum2(const T& x) {
  return x;
}

template<typename T1, typename ...T>
auto sum2(const T1& x1, const T& ... x) {
  return (x1 + sum2(x ...));
}
//-------------------------------------------------------------------------------
// Args -> parameter pack
template<typename ...Args>
void printer(Args&&... args) {
    (std::cout << ... << args) << "\n";
}
//-------------------------------------------------------------------------------
// use initializer_list
// drawback: all arguments have to be of the same type
template<typename T>
void print(std::initializer_list<T> args) {
  for (const auto& x : args) {
    std::cout << x << " ";
  }
}
//-------------------------------------------------------------------------------
// ...args   pack
// args...   unpack
void print2() {}  // base case

template<typename T, typename... Params>
void print2(T x, Params ...args) {
  std::cout << "sizeof... " << sizeof...(args) << "\n";
  std::cout << x << " ";
  print2(args...);
}
//-------------------------------------------------------------------------------
int main() {
  std::cout << sum(1, 2, 3, 4, 5) << "\n";
  std::cout << sum2(1, 2.4f, 4, 5) << "\n";

  printer("a", 1, 0.5f);
  print({1, 2, 3, 4, 5});
  print2("\n", 1, 2.3f, "a");

  return 0;
}
