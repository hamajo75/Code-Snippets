#include <iostream>
#include <string.h>
#include <memory>

#include <message.h>
/********************************************************************************
 * Show only the public interface
 * Only declaration includes need to be in the header file.
 *   The other includes can be in the .cc file.
 * Modifying the data members of the hidden Impl class does not affect binary compatibility.
 * -> can have a clean and stable header file
*********************************************************************************/

// The Pimpl - Idiom is an example of the Bridge - Pattern.
//-------------------------------------------------------------------------------
class Person {
 private:
  class PersonImpl;                   // hide implementation in .cpp file
  std::unique_ptr<PersonImpl> impl;   // opaque pointer - bridge
  std::string name_;

 public:
  explicit Person(const std::string& name);
  void greet();
};
Person::Person(const std::string& name) :
  impl{std::make_unique<PersonImpl>()},
  name_{name} {}

class Person::PersonImpl {
 public:
  void greet(Person* p);
};

void Person::greet() {
  impl->greet(this);
}
void Person::PersonImpl::greet(Person* p) {
  std::cout << "Person " << p->name_ << "\n";
}
//-------------------------------------------------------------------------------
int main() {
  Person p{"Sepp"};
  p.greet();

  Messaging::Message{"text"};

  return 0;
}
