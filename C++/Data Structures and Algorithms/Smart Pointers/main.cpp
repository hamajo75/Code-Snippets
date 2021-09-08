#include <iostream>
#include <string>
#include <memory>
#include <set>
//-------------------------------------------------------------------------------
class MyStruct {
 private:
  std::string msg;

 public:
  explicit MyStruct(std::string msg) {
    std::cout << "Create "<< msg << "\n";
    this->msg = msg;
  }
  ~MyStruct() {std::cout << "Destroy " << this->msg << "\n";}
  void myFun(){std::cout << "Doing Fun Stuff\n";}
};
//-------------------------------------------------------------------------------
void DanglingPointer()
{
  int* p1 = new int;
  int* p2 = p1;
  delete p2;

  // now we use the already destroyed object
  std::cout << *p1 << "\n";

}
//-------------------------------------------------------------------------------
void CallUniqueMyFun(std::unique_ptr<MyStruct> uptr) {
  uptr->myFun();
}
//-------------------------------------------------------------------------------
void CallSharedMyFun(std::shared_ptr<MyStruct> sptr) {
  sptr->myFun();
}
//-------------------------------------------------------------------------------
void CallWeakMyFun(std::weak_ptr<MyStruct> wptr) {
  if (auto sptr = wptr.lock())
    sptr->myFun();  // cannot call with weak ptr directly
}
//-------------------------------------------------------------------------------
// define an templated alias
template<typename T>
using Scope = std::unique_ptr<T>;
template<typename T>
using Ref = std::shared_ptr<T>; 
//-------------------------------------------------------------------------------
int main(int argc, const char* argv[])
{
  Scope<MyStruct> u_ptr2;
  CallUniqueMyFun(std::move(u_ptr2));                    // move ownership

  // std::shared_ptr<MyStruct> s_ptr2;

  std::weak_ptr<MyStruct> w_ptr;  // don't take ownership, refcount not increased
  {
    std::unique_ptr<MyStruct> u_ptr = std::make_unique<MyStruct>("unique");
    // std::unique_ptr<MyStruct> u_ptr(new MyStruct("unique"));
    u_ptr->myFun();

    u_ptr2 = std::move(u_ptr);

    std::shared_ptr<MyStruct> s_ptr = std::make_shared<MyStruct>("shared");

    // s_ptr2 = s_ptr;
    w_ptr = s_ptr;
    CallWeakMyFun(w_ptr);
  }

  std::cout << "some code here\n";

  // shared pointer to a stack object (why would you do that?)
  MyStruct my_struct{"stack object"};
  std::shared_ptr<MyStruct> shared_ptr(&my_struct,  [](auto){});
  shared_ptr->myFun();

  return 0;
}
