#include <person.h>
#include <iostream>

// implementation is hidden here
class Person::PersonImpl {
 private:
  // here you can hide a lot of stuff too
 public:
  void greet(Person* p) {
    std::cout << "hello from " << p->name << "\n";
  }
};

Person::Person()
: impl (new PersonImpl) {

}

Person::~Person() {
  delete impl;
}

void Person::greet() {
  impl->greet(this);
}
