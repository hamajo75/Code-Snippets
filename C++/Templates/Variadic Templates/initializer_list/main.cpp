#include <iostream>
#include <string>
#include <sstream>
#include <vector>

template<typename T>
std::string ToStringImpl(const T& t) {
  std::stringstream ss;
  ss << t;
  return ss.str();
}

template<typename ... Params>
std::vector<std::string> ToString(const Params& ... params) {
  return {ToStringImpl(params)...};
}

// the compiler will expand that into something like this:
// auto ToString(T1 t1, T2 t2, T3 t3, T4 t4) {
//   return {
//     ToStingImmp(t1),
//     ToStringImpl(t2),
//     ToStringImpl(t3),
//     ToStringImpl(t4),
//   }
// }

//-------------------------------------------------------------------------------
int main() {
  const auto strings = ToString("hello", 1, 3.14, "world");

  for (const auto& str : strings) {
    std::cout << str << "\n";
  }

  return 0;
}
