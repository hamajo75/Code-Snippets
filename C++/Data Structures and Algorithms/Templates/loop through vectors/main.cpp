#include <algorithm>
#include <iostream>
#include <vector>

// Answer to Georg P. https://stackoverflow.com/questions/44958016/c-concatenate-containers-of-polymorphic-objects
struct Base {
  std::string name = "base";
};

struct A : public Base {};
struct B : public Base {};
struct C : public Base {};

template <typename F, typename... Vectors>
void for_all_vectors(F &&f, Vectors &&...vs) {
  (std::for_each(vs.begin(), vs.end(), f), ...);
}

int main() {
  std::vector<A> my_a;
  std::vector<B> my_b;
  std::vector<C> my_c;

  my_a.emplace_back(A{"A"});
  my_b.emplace_back(B{"B"});
  my_c.emplace_back(C{"C"});
  my_c.emplace_back(C{});

  for_all_vectors([](const auto& x) {
    std::cout << "x.name " << x.name << "\n";
  }, my_a, my_b, my_c);
}
