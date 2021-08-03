#include <iostream>
#include <string.h>

/********************************************************************************
* Inheritance: Access Types
*  public:    Interface stays the same
*  protected: public -> protected
*  private:   everything becomes private
********************************************************************************/
//-------------------------------------------------------------------------------
class Animal {
 public:
  void doAnimalStuff() {}
};
//-------------------------------------------------------------------------------
// private inheritance: not is-a but is-implemented-in-terms-of
// no effect on design (interface), only on implementation
class Dog : private Animal {
 private:
  std::string name_ = "";

 public:
  explicit Dog(const std::string& name) : name_(name) {}
  Dog(const std::string& name, Dog& anotherDog) : name_(name) {
    std::cout << "This dog object can access the private member of the other"
                 "dog object!\nAccess is on class level, not on object level.\n";
    std::cout << "other dog: " << anotherDog.name_ << "\n";

    doAnimalStuff();  // use function from Animal, but remove it from the interface
  }
};

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  Dog a{"wuffi"};
  Dog b{"rex", a};

  return 0;
}
