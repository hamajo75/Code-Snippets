#include <memory>
#include <iostream>
#include <string>

class Listener;
//-------------------------------------------------------------------------------
class AbstractDispatcher {
 protected:
  std::weak_ptr<Listener> listener_;

 public:
  void RegisterListener(std::weak_ptr<Listener> listener) {
    listener_ = listener;
  }
};
//-------------------------------------------------------------------------------
// Below code doesn't work! You cannot use weak_from_this() inside a constructor,
// because the shared_ptr doesn't exist yet.
// note: public inheritance is important !!
//-------------------------------------------------------------------------------
class Listener : public std::enable_shared_from_this<Listener>{
 public:
  // explicit Listener(std::shared_ptr<AbstractDispatcher> dispatcher) {
  //   dispatcher->RegisterListener(weak_from_this());                          // this only get's you an empty weak_ptr !
  // }

  // void RegisterMe() {
  //   dispatcher->RegisterListener(weak_from_this());                      // you need to call this when the object is
  // }                                                                      // already created (the shared_ptr to be exact)

  void Notify() {
    std::cout << "Notified\n";
  }
};
//-------------------------------------------------------------------------------
class Dispatcher: public AbstractDispatcher {
 public:
  void Dispatch() {
  if (auto spt = listener_.lock())
    spt->Notify();
  else
    std::cout << "Cannot lock\n";
  }
};
//-------------------------------------------------------------------------------
int main() {
  auto dispatcher = std::make_shared<Dispatcher>();
  auto listener = std::make_shared<Listener>();
  dispatcher->RegisterListener(listener);

  dispatcher->Dispatch();

  return 0;
}
