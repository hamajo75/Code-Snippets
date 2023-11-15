#include <cstdio>
#include <utility>

class Foo {
 public:
  Foo() { std::printf("Foo constructor\n"); }
  Foo(Foo &&) { std::printf("Foo move constructor\n"); }
  void Use() { std::printf("Foo use\n"); }
};

class Bar {
 public:
  explicit Bar(Foo &&f) : foo(std::move(f)) {
    std::printf("Bar constructor\n");
  }
  void Use() {
    std::printf("Bar using foo.Use()\n");
    foo.Use();
  }

 private:
  Foo foo;
};