#include <iostream>
#include <string.h>

#include <variant>

// select with index
void print(const std::variant<int, double, float>& value) {
  switch(value.index()) {
    case 0: std::cout << "int: " << std::get<0>(value) << "\n"; break;
    case 1: std::cout << "double: " << std::get<1>(value) << "\n"; break;
    case 2: std::cout << "float: " << std::get<2>(value) << "\n"; break;
  }
}

// select with visitor
struct visitor {
  void operator()(int v, int add) const { std::cout << "int: " << v + add << "\n"; }
  void operator()(double v, int add) const { std::cout << "double: " << v + add << "\n"; }
  void operator()(float v, int add) const { std::cout << "float: " << v + add << "\n"; }
  // default handler to ignore types we are not interested in here
  template <typename T1, typename T2>
  void operator()(T1, T2) {}
};

void print_visitor(const std::variant<int, double, float, std::string>& value) {
  std::variant<int> add;
  add = 10;
  std::visit(visitor{}, value, add);
}

struct ReturnVisitor {
  int operator()(int v, int add) { return v + add; }
  int operator()(double v, int add) { return v + add; }
  // default handler to ignore types we are not interested in here
  template <typename T1, typename T2>
  void operator()(T1, T2) {}
};

int add_visitor(const std::variant<int, double>& value) {
  std::variant<int> add;
  add = 10;
  return std::visit(ReturnVisitor{}, value, add);
}

using var_t = std::variant<int, long, double, std::string>;
//-------------------------------------------------------------------------------
int main() {
  print(5);
  print(5.0);
  print(5.0f);

  print_visitor(5);
  print_visitor(5.0);
  print_visitor(5.0f);

  var_t v = 1;
  std::cout << "return parameter (lambda): " << std::visit([](auto&& arg) -> int {return 1;}, v) << "\n";

  double value = 3.0f;
  std::cout << "return parameter: " << add_visitor(value) << "\n";

  return 0;
}
