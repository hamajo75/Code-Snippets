#include <chrono>
#include <iostream>

#include <thread>
#include <functional>

class CallBackTimer {
 public:
  CallBackTimer() : is_running_(false) {}

  ~CallBackTimer() {
    if (is_running_.load(std::memory_order_acquire)) {
      Stop();
    };
  }

  void Stop() {
    is_running_.store(false, std::memory_order_release);
    if (thread_.joinable())
      thread_.join();
  }

  void Start(int interval, std::function<void(void)> func) {
    if (is_running_.load(std::memory_order_acquire)) {
      Stop();
    };
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
  CallBackTimer timer;

  timer.Start(1000, CallbackFun);

  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  timer.Stop();

  return 0;
}