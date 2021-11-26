#include <iostream>
#include <string>

class Fruit {
 public:
  enum Value : uint8_t { Apple, Pear, Banana, Strawberry };

  Fruit() = default;
  constexpr explicit Fruit(Value aFruit) : value(aFruit) {}

  constexpr bool operator==(Fruit a) const { return value == a.value; }
  constexpr bool operator!=(Fruit a) const { return value != a.value; }

  constexpr bool IsYellow() const { return value == Banana; }

 private:
  Value value;
};

//-------------------------------------------------------------------------------
int main() {
  Fruit f = Fruit::Strawberry;
  f.IsYellow();

  return 0;
}
