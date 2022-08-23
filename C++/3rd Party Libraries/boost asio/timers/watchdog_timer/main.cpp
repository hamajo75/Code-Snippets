#include <boost/asio.hpp>
#include <iostream>

#include "watchdog_timer.h"

//-------------------------------------------------------------------------------
void Handler() {
  std::cout << "Timer expired\n";
}

//-------------------------------------------------------------------------------
int main() {
  Timer timer{2, Handler};
  timer.Reset();

  for (int i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    timer.Reset();
    std::cout << "Timer reset" << i << "\n";
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  timer.Reset();

  for (int i = 0; i < 3; ++i) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    timer.Reset();
    std::cout << "Timer reset" << i << "\n";
  }

  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  return 0;
}
