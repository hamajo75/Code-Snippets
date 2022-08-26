#include <boost/asio.hpp>
#include <iostream>

#include "watchdog_timer.h"

//-------------------------------------------------------------------------------
void Handler() {
  std::cout << "Timer expired\n";
}

void SomeTests() {
  Timer timer{2000, Handler};
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
}

class Parent {
  struct SafetyData {
    int64_t last_sequence_number = -1;
    Timer heartbeat_timer;
  };
  SafetyData safety_data_;

 public:
  explicit Parent(int timeout)
    : safety_data_{0, Timer{timeout, [this](){
       std::cout << "timeout\n";
     }}} {}

  void Start() {
    safety_data_.heartbeat_timer.Reset();
  }
};
//-------------------------------------------------------------------------------
int main() {
// SomeTests();

  Parent p{10000};
  p.Start();

  std::this_thread::sleep_for(std::chrono::milliseconds(11000));

  return 0;
}
