#include <iostream>
#include <string.h>
#include <memory>

/********************************************************************************
 * compromises:
 * type safety     - you have some type at the compromised memory 
 * memory safety   - we access memory that we shouldn't
 * resource safety - might destroy a resource
 * 
 * Rules to avoid this problem:
 * (R1) every object has an owner
 * (R2) distinguish owners from non-owners (only the owner is supposed to delete the object)
 * (R3) assume raw pointers are non-owners
 * (R4) no raw pointer should outlive the owner scope
 * (R5) anything that holds an owner is an owner
 * (R6) don't assign to a non-owner
*********************************************************************************/
class Part {
 public:
  ~Part() { std::cout << "Part destructor\n"; }
};
//-------------------------------------------------------------------------------
class Whole {
 private:
  Part* my_part_ = nullptr;
 public:
  explicit Whole(Part* part) : my_part_(part) {}
  ~Whole() { std::cout << "Whole destructor\n"; }
};
//-------------------------------------------------------------------------------
// cyclic dependency: 2 objects need to talk to each other
class WorkplaceMessageHandler;
class BackendMessageHandler {
 private:
  WorkplaceMessageHandler* wmh_ = nullptr;
  std::weak_ptr<WorkplaceMessageHandler> wptr_wmh_;
 public:
  ~BackendMessageHandler() { std::cout << "BackendMessageHandler destructor\n"; }

  void AddWorkplaceMessageHandler(WorkplaceMessageHandler* wmh) {
    wmh_ = wmh;
  }

  void AddWorkplaceMessageHandler(std::weak_ptr<WorkplaceMessageHandler> wmh) {
    wptr_wmh_ = wmh;
  }

  void AccessOtherObject();      // implementation needs to be after WorplaceMessageHandler

  void Print() {
    std::cout << "Printing from BackendMessageHandler\n";
  }
};
class WorkplaceMessageHandler {
 private:
  BackendMessageHandler* bmh_ = nullptr;
  std::weak_ptr<BackendMessageHandler> wptr_bmh_;

 public:
  ~WorkplaceMessageHandler() {
    std::cout << "WorkplaceMessageHandler destructor\n";
    AccessOtherObject();
  }

  void AddBackendMessageHandler(BackendMessageHandler* bmh) {
    bmh_ = bmh;
  }

  void AddBackendMessageHandler(std::weak_ptr<BackendMessageHandler> bmh) {
    wptr_bmh_ = bmh;
  }
  void AccessOtherObject() {
    if (auto sptr = wptr_bmh_.lock())
      sptr->Print();
    else
      std::cout << "no object!\n";
  }
  void Print() {
    std::cout << "Printing from WorkplaceMessageHandler\n";
  }
};
void BackendMessageHandler::AccessOtherObject() {
  auto sptr = wptr_wmh_.lock();
  sptr->Print();
}
//-------------------------------------------------------------------------------
void DanglingPointer(int* p) {
  delete p;                           // doesn't comply with (R3)
}
//-------------------------------------------------------------------------------
int main() {
  int* p = new int{0};                // doesn't comply with (R6)

  DanglingPointer(p);

  // now we use the already destroyed object
  std::cout << *p << "\n";

  Part part;
  Whole whole{&part};   // correct order of destruction

  WorkplaceMessageHandler wmh;  // this will have a pointer to a non existing object before it is destroyed
  BackendMessageHandler bmh;    // this will be destroyed first

  wmh.AddBackendMessageHandler(&bmh);
  bmh.AddWorkplaceMessageHandler(&wmh);

  // use weak_ptr: see Item 20 in Effective Modern C++
  auto sptr_wmh = std::make_shared<WorkplaceMessageHandler>();
  auto sptr_bmh = std::make_shared<BackendMessageHandler>();

  sptr_wmh->AddBackendMessageHandler(sptr_bmh);
  sptr_bmh->AddWorkplaceMessageHandler(sptr_wmh);
  sptr_wmh->AccessOtherObject();
  sptr_bmh->AccessOtherObject();

  return 0;
}
