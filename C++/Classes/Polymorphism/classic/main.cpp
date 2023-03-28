#include <iostream>
#include <string>

#include <iostream>
#include <string.h>


// Animal interface
class Animal {
 public:
  virtual void Eat() = 0;
};

class Dog : public Animal {
 public:
  Dog() = default;

 private:
  void Eat() override {
    std::cout << "Dog eats\n";
  }
};

class Donkey : public Animal {
 public:
  Donkey() = default;

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
