#include <iostream>
#include <string.h>

/*
Default copy: copy each member.
For sophisticated types or abstract types this is not the right semantics.

When a class is a resource handle, i.e. when it manages data through a pointer (reference, handle, etc),
make sure that assignment, and passing by value works and moving data works without exception.

Rule of Zero C.20
If you can avoid defining default operations, do.
In other words: Don't write any of the 6 operations above, if you don't have to.
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
  explicit MyClass(int* data) : data_{data} {           // default constructor
    std::cout << "Default constructor\n";
  }
  ~MyClass() {                                          // 1. destructor
    std::cout << "destructor\n";
  }
  MyClass(const MyClass& other) {                       // 2. copy constructor    fun(object)
    std::cout << "Copy constructor\n";
    data_ = new int[1];
    *data_ = *other.data_;
    // *this = other;                                            // call copy assignment
  }
  MyClass& operator=(const MyClass& other) {            // 3. copy assignment     a = b (other), a will be constructed
    std::cout << "Copy assignment\n";

    if (this == &other) return *this;                        // check assignment to self

    data_ = new int[1];
    *data_ = *other.data_;

    return *this;
  }
  MyClass(MyClass&& other) {                            // 4. move constructor
    std::cout << "Move constructor\n";
  }
  MyClass& operator=(MyClass&& other) {                 // 5. move assignment
    std::cout << "Move assignment\n";
    return other;
  }

};

//-------------------------------------------------------------------------------
int main() {
  int data = 1;
  MyClass o1{&data};  // default constructor

  MyClass o2{o1};     // copy initialization
  MyClass o3 = o2;    // still copy contructor !
  MyClass o4{&data};  // default constructor
  o4 = o3;            // copy assignment

  return 0;
}
