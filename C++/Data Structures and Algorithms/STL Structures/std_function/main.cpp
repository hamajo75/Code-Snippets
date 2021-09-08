#include <iostream>
#include <string>
#include <functional>

void print(std::string str) {
  std::cout << str << '\n';
}

struct MyStruct {
  void my_member_fun(){
    std::cout << "my_member_fun" << '\n';
  }
};
//-------------------------------------------------------------------------------
int main() {
  // store a free function
  std::function<void(std::string)> print_stored = print;
  print_stored("stored free function");

  // store a lambda
  std::function<void()> lambda_stored = []() { print("stored lambda"); };
  lambda_stored();

  // store a member function
  MyStruct my_struct;
  std::function<void()> member_stored = std::bind(&MyStruct::my_member_fun, my_struct);
  member_stored();

  return 0;
}
