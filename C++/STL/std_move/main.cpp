#include <iostream>
#include <ratio>
#include <string>
#include <vector>

// avoid avoidable construction/destruction of objects

/* std::move is a static_cast to a rvalue ref type
*/

void print_vector(const std::vector<int>& vec) {
  for (const auto& val : vec) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}

//-------------------------------------------------------------------------------
int main() {
  std::vector<int> v1 = {1, 2, 3, 4};
  std::vector<int> v2;

  v2 = std::move(v1);  // now v1 is empty, same works for std::string

  std::cout << "v1: ";
  print_vector(v1);

  std::cout << "v2: ";
  print_vector(v2);


  return 0;
}
