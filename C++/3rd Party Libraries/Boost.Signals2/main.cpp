#include <iostream>
#include <string>

#include <boost/signals2.hpp>

void Simple() {
  boost::signals2::signal<void(const std::string&)> event;        // define event

  event.connect([](const std::string& info) {                     // connect handlers (observers, callbacks, whatever u wanna call them)  // NOLINT
      std::cout << "event handler 1: " << info << "\n";
  });
  event.connect([](const std::string& info) {
      std::cout << "event handler 2: " << info << "\n";
  });

  event("this is event A");                                       // fire event
}

//-------------------------------------------------------------------------------
int main() {

  Simple();

  return 0;
}
