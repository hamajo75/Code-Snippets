#include <iostream>
#include <string.h>
#include <set>

struct Sender {};
//-------------------------------------------------------------------------------
class HandlerIF {
 public:
  virtual void HandleEvent(Sender sender) = 0;
};
//-------------------------------------------------------------------------------
class ConcreteHandlerA : public HandlerIF {
 public:
  void HandleEvent(Sender sender) {
    std::cout << "ConcreteHandlerA\n";
  }
};
//-------------------------------------------------------------------------------
class ConcreteHandlerB : public HandlerIF {
 public:
  void HandleEvent(Sender sender) {
    std::cout << "ConcreteHandlerB\n";
  }
};
//-------------------------------------------------------------------------------
class Reactor {
 private:
  std::set<HandlerIF*> handlers_;

 public:
  void Run() {
    while (true) {
      // call event handler function
    }
  }

  void AddHandler(HandlerIF* handler) {
    handlers_.insert(handler);
  }
  void RemoveHandler(HandlerIF* handler) {
    handlers_.erase(handler);
  }
};
//-------------------------------------------------------------------------------
int main() {
  Reactor reactor;

  ConcreteHandlerA handlerA;
  ConcreteHandlerB handlerB;

  reactor.AddHandler(&handlerA);
  reactor.AddHandler(&handlerB);

  reactor.Run();  // start event loop
  return 0;
}
