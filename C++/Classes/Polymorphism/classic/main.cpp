#include <iostream>
#include <string>

#include <iostream>
#include <string.h>


// Animal interface
class Animal {
 public:
  virtual void Eat() = 0;
};

class Dog : private Animal {
 public:
  Dog(){ std::cout << "Dog constructor\n"; }
  ~Dog(){ std::cout << "Dog destructor\n"; }

 private:
  void Eat() override {
    std::cout << "Dog eats\n";
  }
};

class Donkey : private Animal {
 public:
  Donkey(){ std::cout << "Donkey constructor\n"; }
  ~Donkey(){ std::cout << "Donkey destructor\n"; }

 private:
  void Eat() override {
    std::cout << "Donkey eats\n";
  }
};

void UseTheInterface(Animal& animal) {
  animal.Eat();
}

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  Dog dog;
  Donkey donkey;

  UseTheInterface(dog);
  UseTheInterface(donkey);

  return 0;
}
