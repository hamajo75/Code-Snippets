#include <iostream>
#include <string>

#include <any>

/*  container for single values of any copy constructible type.
*/

void Simple() {
  std::any a;

  a = 1;
  std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
  a = 3.1415;

  std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
  a = std::string{"hello"};
  std::cout << a.type().name() << ": " << std::any_cast<std::string>(a) << '\n';
  a = "hello";
  try {
    std::cout << a.type().name() << ": " << std::any_cast<std::string>(a) << '\n';
  } catch(const std::bad_any_cast& e)  {
    std::cout << e.what() << '\n';
  }

  a = true;
  std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';
}
//-------------------------------------------------------------------------------
int main() {
  Simple();

  return 0;
}
