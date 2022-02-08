#include <iostream>
#include <string>
#include <vector>

// avoid avoidable construction/destruction of objects

/* std::move is a static_cast to a rvalue ref type
*/

//-------------------------------------------------------------------------------
int main() {
  std::vector<int> v1 = {1, 2, 3, 4};
  std::vector<int> v2;

  v2 = std::move(v1);  // now v1 is empty

  return 0;
}
