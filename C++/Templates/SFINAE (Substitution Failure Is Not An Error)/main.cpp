#include <iostream>
#include <string>

#include <type_traits>

/* If a template substitution results in an invalid type or expression this does not
   result in a compile error (as it would if you'd write the substituted code yourself).
   What happens is that the specialization is only discarded from the overload set.
*/

template<typename Float,
         typename = std::enable_if<std::is_floating_point<Float>::value>::type>
auto add(Float f1, Float f2) {
  return f1 + f2;
}

//-------------------------------------------------------------------------------
int main() {
  std::cout << add(1.0, 2.0) << "\n";
  std::cout << add(1, 2) << "\n";       // this specialization is discarded

  return 0;
}
