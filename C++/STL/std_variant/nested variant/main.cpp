#include <iostream>
#include <string>
#include <variant>

struct A{ std::string name = "A"; };
struct B{ std::string name = "B"; };
struct C{ std::string name = "C"; };
struct D{ std::string name = "D"; };

using Type1 = std::variant<A, B>;
using Type2 = std::variant<C, D>;
using Nested = std::variant<Type1, Type2>;

Nested GetObject() {
  return C{};
}

// select with visitor
struct visitor_Type1 {
  void operator()(A a) const { std::cout << a.name << "\n"; }
  void operator()(B b) const { std::cout << b.name << "\n"; }
};
struct visitor_Type2 {
  void operator()(C c) const { std::cout << c.name << "\n"; }
  void operator()(D d) const { std::cout << d.name << "\n"; }
};
struct visitor_Nested {
  void operator()(Type1 t1) const { std::visit(visitor_Type1{}, t1); }
  void operator()(Type2 t2) const { std::visit(visitor_Type2{}, t2); }
};
//-------------------------------------------------------------------------------
int main() {
  Nested o = GetObject();

  // std::cout << std::get<A>(std::get<Type1>(o)).name;    // get via index
  // A a = std::get<A>(std::get<Type1>(o));                // via type

  std::visit(visitor_Nested{}, GetObject());

  return 0;
}
