#include <iostream>
#include <string.h>

#include <variant>

template<class... Ts> struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

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

int additionVisitor(const std::variant<int, double>& value) {
  std::variant<int> add;
  add = 10;
  return std::visit(ReturnVisitor{}, value, add);
}

using var_t = std::variant<int, long, double, std::string>;

void UseVisitors() {
  print(5);
  print(5.0);
  print(5.0f);

  print_visitor(5);
  print_visitor(5.0);
  print_visitor(5.0f);

  var_t v = 666;
  // get contained value: method 1
  std::cout << "get value with lambda: " << std::visit([](auto&& arg) -> int {
    using T = std::decay_t<decltype(arg)>;
    if constexpr (std::is_same_v<T, int>)
      return arg;
    return 1;
  }, v) << "\n";

  double value = 3.0f;

  // get contained value : method 2
  // need the helper templates above
  int external_value = 5;
  v = 10.0f;
  std::visit(overloaded {
      [external_value](int arg) { std::cout << "int + external_value: " << arg + external_value << "\n"; },
      [](long arg) { std::cout << "long: " << arg << "\n"; },
      [](const std::string& arg) { std::cout << "string: " << arg << "\n"; },
      // [](double arg) { std::cout << "double: " << arg << "\n"; },
      [](auto arg) { std::cout << "auto: " << arg << "\n"; },                                                // default
  }, v);
}

var_t ReturnVariant() {
  return 0.5f;
}

void AccessVariantValues() {    // std::get<>(), std::get_if<>()
  var_t v = 0.5;
  // double d = v;   // you cannot do this! (even if we know the active type)
  try {
    auto d = std::get<double>(v);
    std::cout << "double! " << d << "\n";
  } catch (std::bad_variant_access&) {
    std::cout << "variant doesn't hold a double right now\n";
  }

  double* ret = std::get_if<double>(&v);

  var_t ret_v = ReturnVariant();
  double* ret_d = std::get_if<double>(&ret_v);    // you'll get a nullptr if the stored value is of another type

  std::cout << "ret: " << *ret_d << "\n";

}
//-------------------------------------------------------------------------------
int main() {
  UseVisitors();
  AccessVariantValues();

  return 0;
}
