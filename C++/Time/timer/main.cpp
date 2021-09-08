#include <chrono>
#include <iostream>
#include <map>

#include <thread>
#include <functional>

class CallBackTimer {
 public:
  CallBackTimer() : is_running_(false) {}

  ~CallBackTimer() {
    if (is_running_.load(std::memory_order_acquire)) {
      Stop();
    }
  }
  CallBackTimer(const CallBackTimer& other) {                       // copy constructor
    std::cout << "Copy constructor\n";
  }
  CallBackTimer& operator=(const CallBackTimer& other) {            // copy assignment
    std::cout << "Copy assignment\n";
    return *this;
  }

  void Stop() {
    is_running_.store(false, std::memory_order_release);
    if (thread_.joinable())
      thread_.join();
  }

  void Start(int interval, std::function<void(void)> func) {
    if (is_running_.load(std::memory_order_acquire)) {
      Stop();
    }
    is_running_.store(true, std::memory_order_release);
    thread_ = std::thread([this, interval, func]() {
      while (is_running_.load(std::memory_order_acquire)) {
        func();
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
      }
    });
  }

  bool is_running() const noexcept {
    return (is_running_.load(std::memory_order_acquire) && thread_.joinable());
  }

 private:
  std::atomic<bool> is_running_;
  std::thread thread_;
};
//-----------------------------------------------------------------------------
void CallbackFun() {
  std::cout << "tick\n";
}
//-----------------------------------------------------------------------------
int main() {
  std::map<std::string, CallBackTimer> timers_;

  CallBackTimer timer;
  timers_["1"] = timer;

  timers_["1"].Start(1000, CallbackFun);
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  timers_["1"].Stop();

  return 0;
}