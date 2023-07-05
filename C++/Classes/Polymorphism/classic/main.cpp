#include <iostream>
#include <string>

// Animal interface
class Animal {
 public:
  virtual void Eat() = 0;
};

void UseTheInterface(Animal& animal) {
  animal.Eat();
}

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
  Donkey() {
    UseTheInterface(*this);
  };

 private:
  // Notice that is's perfectly possible to have the Eat() method private, so it
  // can only be called through the base class interface.
  void Eat() override {
    std::cout << "Donkey eats\n";
  }
};

//-------------------------------------------------------------------------------
int main(int argc, const char* argv[]) {
  Dog dog;
  Donkey donkey;

  UseTheInterface(dog);
  UseTheInterface(donkey);

  return 0;
}
