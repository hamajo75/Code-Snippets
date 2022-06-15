#include <iostream>
#include <string>

// non type template parameter
template<typename T, int i, const char* str>
void myfun(T val) {
  std::cout << val << std::to_string(i) << str << "\n";
}

//-------------------------------------------------------------------------------
int main() {
  const char str[] = " bla";
  myfun<std::string, 42, >("hello ");
  return 0;
}
