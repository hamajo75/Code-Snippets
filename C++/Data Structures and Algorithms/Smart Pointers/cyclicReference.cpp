#include <iostream>
#include <memory>

// Mother points to Son and Daughter and the other way round
// Mother and Son don't get destroyed because the hold a pointer to each other

struct Son;
struct Daughter;

struct Mother{
  ~Mother() {
    std::cout << "Mother gone" << std::endl;
  }
  void setSon(const std::shared_ptr<Son> s) {
    mySon = s;
  }
  void setDaughter(const std::shared_ptr<Daughter> d) {
    myDaughter = d;
  }
  std::shared_ptr<const Son> mySon;                       // Son & Mother don't get destroyed because of the shared_ptr
  std::weak_ptr<const Daughter> myDaughter;               // Daughter get's destroyed
};

struct Son {
  explicit Son(std::shared_ptr<Mother> m) : myMother(m) {}
  ~Son() {
    std::cout << "Son gone" << std::endl;
  }
  std::shared_ptr<const Mother> myMother;
};

struct Daughter {
  explicit Daughter(std::shared_ptr<Mother> m) : myMother(m) {}
  ~Daughter() {
    std::cout << "Daughter gone" << std::endl;
  }
  std::shared_ptr<const Mother> myMother;
};

int main() {
  std::cout << std::endl;
  {
    auto mother { std::make_shared<Mother>() };
    auto son { std::make_shared<Son>(mother) };
    auto daughter { std::make_shared<Daughter>(mother) };

    mother->setSon(son);
    mother->setDaughter(daughter);
  }
  std::cout << std::endl;
}
