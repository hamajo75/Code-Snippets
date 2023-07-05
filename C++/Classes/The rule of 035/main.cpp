#include <iostream>
#include <string.h>

/*
Default copy: copy each member.
For sophisticated types or abstract types this is not the right semantics.

When a class is a resource handle, i.e. when it manages data through a pointer (reference, handle, etc),
make sure that assignment, and passing by value works and moving data works without exception.

Rule of Zero C.20
If you can avoid defining default operations, do.
In other words: Don't write any of the 6 operations below, if you don't have to.
And if you have to, look at the Rules below.

Rule of Three
- If a class defines any of the following, then it should define all three:
- Deleting one usually implies deleting them all.

Destructor ~MyClass()
Copy Constructor MyClass(const MyClass& other)
Copy Assignment Operator MyClass& operator=(MyClass other)

With the implementation of move semantics things get more complicated.

Rule of Five
Destructor ~MyClass()
Copy Constructor MyClass(const MyClass& other)
Copy Assignment Operator MyClass& operator=(MyClass other)
Move Constructor MyClass(MyClass&& other)
Move Assignment Operator MyClass& operator=(MyClass&& other)
*/
class MyClass {
 private:
  int* data_;

 public:
  void PrintData() {
    std::cout << "Data: " << *data_ << "\n";
  }

  MyClass() = default;
  explicit MyClass(int* data) : data_{data} {                 // constructor
    std::cout << "Default constructor\n";
  }
  ~MyClass() {                                                // 1. destructor
    std::cout << "destructor\n";
  }

  // Note: don't make this explicit, it won't be called e.g. in MyClass c = b;
  MyClass(const MyClass& other) {                             // 2. copy constructor    fun(object)
    std::cout << "Copy constructor\n";
    data_ = new int[1];
    *data_ = *other.data_;
    // *this = other;                                         // call copy assignment
  }
  MyClass& operator=(const MyClass& other) {                  // 3. copy assignment     a = b (other), a will be constructed
    std::cout << "Copy assignment\n";

    if (this == &other) return *this;                         // check assignment to self

    data_ = new int[1];
    *data_ = *other.data_;

    return *this;
  }

  // C.66: Make move operations noexcept. (matter of performance)
  MyClass(MyClass&& other) noexcept {                         // 4. move constructor
    std::cout << "Move constructor\n";
    data_ = std::move(other.data_);
  }

  // MyClass(MyClass&& other) = default;


  MyClass& operator=(MyClass&& other) noexcept {              // 5. move assignment
    std::cout << "Move assignment\n";
    return other;
  }
  // When is this function called?
  // rvalue: v = myfun();
  // v2 = std::move(v1);     - lvalue v1 lives on!

};

MyClass CreateObject(int* data) {
  MyClass o{data};
  return o;
}

//-------------------------------------------------------------------------------
int main() {
  // int data = 1;
  // MyClass o1{&data};                     // default constructor
  // MyClass o2{o1};                        // copy initialization -> copy constructor
  // MyClass o3 = o2;                       // still copy contructor !
  // MyClass o5;
  // {
  //   MyClass o4{&data};                   // default constructor
  //   o4 = o3;                             // copy assignment
  //   o5 = std::move(o4);                  // move assignment
  // }
  // MyClass o6 = std::move(o5);            // move constructor

  int d = 2;
  // MyClass o7{std::move(CreateObject(&d))};
  MyClass o7{CreateObject(&d)};
  o7.PrintData();

  return 0;
}
