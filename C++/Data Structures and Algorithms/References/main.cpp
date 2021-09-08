#include <iostream>
#include <string.h>

void myfun(std::string& str) {
  str = "you";
  // std::cout << str << "\n";
}
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  std::string str = "hello";
  myfun(str);
  std::cout << str << "\n";

  return 0;
}
