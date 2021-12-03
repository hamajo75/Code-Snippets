#include <iostream>
#include <string>

/* There are 2 use cases:
 *  1. use same code (implemented in base class) for different derived classes
 *     i.e. extend the derived class with functionality from the base class.
 *  2. static interfaces or static polymorphism (without virtual methods)
 */

// add functionality to the derived class

template <typename T> struct NumericalFunctions {
  void scale(double multiplicator) {
    T &underlying = static_cast<T &>(*this);
    underlying.setValue(underlying.getValue() * multiplicator);
  }
  void square() {
    T &underlying = static_cast<T &>(*this);
    underlying.setValue(underlying.getValue() * underlying.getValue());
  }
  void setToOpposite() { scale(-1); }
};


class Sensitivity : public NumericalFunctions<Sensitivity>{
 public:
  double getValue() const { return value_; }

  void setValue(double value) { value_ = value; }

 private:
  double value_;
};


// static interface
template <typename T> class Amount {
 public:
  double getValue() const { return static_cast<T const &>(*this).getValue(); }
};

class Constant42 : public Amount<Constant42> {
 public:
  double getValue() const { return 42; }
};

class Variable : public Amount<Variable> {
 public:
  explicit Variable(int value) : value_(value) {}
  double getValue() const { return value_; }

 private:
  int value_;
};

// using the static interface
// the polymorphic call has been resolved at compile time
// concepts are better !
template <typename T> void print(Amount<T> const &amount) {
  std::cout << amount.getValue() << '\n';
}
//-------------------------------------------------------------------------------
int main() {
  Sensitivity sens;
  sens.setValue(1);
  sens.scale(2);

  std::cout << "sens.getValue(): " << sens.getValue() << "\n";

  Constant42 c42;
  print(c42);
  Variable v(43);
  print(v);

  return 0;
}
