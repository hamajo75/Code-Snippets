#include <iostream>
#include <string>

/*
 * Composition order quick summary:
 * 1. Member objects are constructed before the constructor body.
 * 2. Members are constructed in declaration order, not initializer-list order.
 * 3. Destruction runs in reverse declaration order.
 */

class Part {
 public:
  explicit Part(std::string name) : name_(std::move(name)) {
    std::cout << "Part constructed: " << name_ << "\n";
  }

  ~Part() { std::cout << "Part destroyed: " << name_ << "\n"; }

 private:
  std::string name_;
};

class Computer {
 public:
  Computer()
      : storage_("storage"),
        cpu_("cpu"),
        memory_("memory") {
    std::cout << "Computer constructor body\n";
  }

  ~Computer() { std::cout << "Computer destructor body\n"; }

 private:
  Part cpu_;
  Part memory_;
  Part storage_;
};

int main() {
  std::cout << "Creating Computer object\n";
  Computer object;

  std::cout << "Leaving main\n";
  return 0;
}
