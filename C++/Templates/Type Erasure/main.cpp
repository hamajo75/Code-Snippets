#include <iostream>
#include <memory>
#include <string>
#include <vector>

/* Compare below implementation with a standard virtual method approach.
Pro
- The derived class doesn't need to know the base class.
Contra
- Difficult to implement.
*/

class Object {        // std::functional, std::any act like Object
 public:
  template <typename T>
  explicit Object(const T& obj) : object(std::make_shared<Model<T>>(std::move(obj))) {}

  std::string getName() const {
    return object->getName();                   // virtual object call -> Model
  }

 private:
  struct Concept {                              // tells us what a duck is
    virtual ~Concept() {}
    virtual std::string getName() const = 0;    // this is what we actually want to call (quack)
  };

  template <typename T>                         // implements the abstract class Concept
  struct Model : Concept {
    explicit Model(const T& t) : object(t) {}
    std::string getName() const override {
      return object.getName();                  // concrete object call
    }

   private:
    T object;
  };

  std::shared_ptr<const Concept> object;
};

void printName(std::vector<Object> vec) {                     // this is generic now (the goal of the whole thing)
  for (auto v : vec) std::cout << v.getName() << std::endl;
}

struct Bar {
  std::string getName() const {  // concrete implementation
    return "Bar";
  }
};

struct Foo {
  std::string getName() const {  // concrete implementation
    return "Foo";
  }
};

int main() {
  std::vector<Object> vec{Object{Foo()},  // objects, not base class pointers, any type can be used
                          Object{Bar()}};
                          // Object{std::string{""}}};  // this doesn't work, no getName fct
  printName(vec);
}