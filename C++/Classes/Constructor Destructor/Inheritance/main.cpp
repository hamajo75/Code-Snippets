#include <iostream>
#include <string>

/*
 * Inheritance order quick summary:
 * 1. Virtual base classes
 * 2. Non-virtual base classes in the order listed in the class declaration
 * 3. Data members in declaration order
 * 4. Derived class constructor body
 *
 * Destruction runs in the exact reverse order.
 */

class VirtualBase {
 public:
  VirtualBase() { std::cout << "1. VirtualBase constructed\n"; }
  ~VirtualBase() { std::cout << "7. VirtualBase destroyed\n"; }
};

class LeftBase : virtual public VirtualBase {
 public:
  LeftBase() { std::cout << "2. LeftBase constructed\n"; }
  ~LeftBase() { std::cout << "6. LeftBase destroyed\n"; }
};

class RightBase : virtual public VirtualBase {
 public:
  RightBase() { std::cout << "3. RightBase constructed\n"; }
  ~RightBase() { std::cout << "5. RightBase destroyed\n"; }
};

class Member {
 public:
  explicit Member(std::string name) : name_(std::move(name)) {
    std::cout << "4. Member constructed: " << name_ << "\n";
  }

  ~Member() { std::cout << "4. Member destroyed: " << name_ << "\n"; }

 private:
  std::string name_;
};

class Derived : public LeftBase, public RightBase {
 public:
  Derived() : member_("member inside Derived") {
    std::cout << "5. Derived constructor body\n";
  }

  ~Derived() { std::cout << "3. Derived destructor body\n"; }

 private:
  Member member_;
};

int main() {
  std::cout << "Creating Derived object\n";
  Derived object;

  std::cout << "Leaving main\n";
  return 0;
}
