#include <iostream>
#include <string>

// see Scott Meyers Effective C++, 3rd Edition, Item 3: Use const whenever possible.
//   const and non-const versions of member functions witout code duplication.


class MyClass {
 public:
  const int& GetElement() const { return i_; }
  // int& GetElement() { return i; }  // code duplication, we wanna get rid of this

  int& GetElement() {
    return const_cast<int&>(
      static_cast<const MyClass*>(this)->GetElement());   // add const first! this is the Scott Meyer trick
  }
  // Notes:
  // - Calling GetElement() would only recursively call itself. That's why we need the static_cast.

  explicit MyClass(int i) : i_{i} {}
 private:
  int i_;

};

//-------------------------------------------------------------------------------
int main() {
  MyClass m{0};

  m.GetElement() = 1;
  std::cout << "m.GetElement(): " << m.GetElement() << "\n";

  return 0;
}
