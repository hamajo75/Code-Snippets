#include <iostream>
#include <string>
#include <vector>

#include "helper_class.h"
#include "my_string.h"

void PlayWithMove() {
  std::vector<int> v1 = {1, 2, 3, 4};
  std::vector<int> v2 = {5, 6, 7, 8};

  v2 = std::move(v1);        // now v1 will be empty
  auto v3 = std::move(v2);   // now v2 will be empty
}

MyClass CreateObject() {
  MyClass o;
  return o;
}

void UseObject(MyClass o) {
  o.UseObject();
}

//-------------------------------------------------------------------------------
int main() {

  // PlayWithMove();

  // auto o = CreateObject();  // return value optimization ?

  // UseObject(o);
  // UseObject(MyClass{});

  // o.UseObject();

  MyString s1("Hello");

  MyString s2{MyString{"abcd"}};  // copy constructor

  auto s3 = s2;                   // copy constructor

  return 0;
}
