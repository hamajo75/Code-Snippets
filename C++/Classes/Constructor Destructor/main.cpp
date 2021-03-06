#include <iostream>
#include <string.h>
/********************************************************************************
 * Inheritance:
 * - construction: from base to derived
 * - destruction: from derived to base
 * Composition:
 * - construction: from parts to whole
 * - destruction: from whole to parts
 * Stack: Destruction happens in reversed order of construction.
 *
 * Notes:
 * - Destructors are always called in reverse order of the constructors.
 *
*********************************************************************************/
//-------------------------------------------------------------------------------
class Animal {
 private:

 public:
  int i_;
  Animal(std::string msg){
    this->i_ = 10;
    std::cout << "Animal constructor with msg: " + msg + "\n";
    }
  Animal() : Animal("hello") {                // constructor delegation
    std::cout << "Animal constructor\n";
    }
  ~Animal(){ std::cout << "Animal destructor\n"; }
};
//-------------------------------------------------------------------------------
class Dog : private Animal {
 public:
  Dog(){ std::cout << "Dog constructor\n"; }
  ~Dog(){ std::cout << "Dog destructor\n"; }
};
//-------------------------------------------------------------------------------
class AnotherClass {
 public:
  AnotherClass(){ std::cout << "AnotherClass constructor\n"; }
  ~AnotherClass(){ std::cout << "AnotherClass destructor\n"; }
};
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  AnotherClass c;
  Animal a;
  Dog b;

  std::cout << "a.i_ " << a.i_ << "\n";

  return 0;
}
