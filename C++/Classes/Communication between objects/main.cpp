#include <string.h>
#include <iostream>

#include <memory>

// circular referenced (or cyclic dependency)
/* This can lead to memory leak because both hold a shared ptr
   to each other, even when the rest of the app is disconnected.

   Solution: std::weak_ptr - see below
*/
struct Forth;
struct Back {
  std::shared_ptr<Forth> forth;
};

struct Forth {
  std::shared_ptr<Back> back;
};
struct Event {
  //..
};
//-------------------------------------------------------------------------------
class Listener {
 public:
  void onEvent(Event e) {
    // Handle event from Dispatcher
  }
  // ...
};

class Dispatcher {
 public:
  void dispatchEvent(Event e) {
    if (auto listener = weakListener.lock())             // acquire strong reference
      listener->onEvent(e);
  }

  void registerListener(const std::shared_ptr<Listener>& lp) {
    weakListener = lp;
  }
  //...
 private:
  std::weak_ptr<Listener> weakListener;
};
//-------------------------------------------------------------------------------
int main() { return 0; }
