#include <iostream>
#include <string>

#include <algorithm>

// typical use of a STL algorithm
int myFunction(int i) {
  return i*2;
}
//-------------------------------------------------------------------------------
int main() {
  auto inputs = std::vector<int>{1, 2, 3, 4, 5};
  auto results = std::vector<int>{};

  std::transform(std::begin(inputs), std::end(inputs), std::back_inserter(results), myFunction);

  for (auto e : inputs)
    std::cout << e << " ";
  std::cout << "\n";
  for (auto e : results)
    std::cout << e << " ";


  return 0;
}
