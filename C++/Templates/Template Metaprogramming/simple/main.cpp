#include <iostream>
#include <string>
#include <climits>

template<int N>
struct absolute {
  static_assert(N != INT_MIN);
  static constexpr int value = (N < 0) ? -N : N;
};

//-------------------------------------------------------------------------------
int main() {

  int constexpr n  = 42;
  int constexpr res = absolute<n>::value;               // instantiation of the template

  std::cout << "res: " << res << "\n";

  return 0;
}
