#include <chrono>
#include <iostream>
#include <map>

#include <thread>
#include <functional>
#include <condition_variable>
#include <atomic>

class CallBackTimer {
 private:
  std::atomic<bool> is_running_;
  std::thread thread_;
  std::function<void()> callback_;
  int interval_;
  std::condition_variable condition_variable_;
  std::mutex cv_mutex;

 public:
  CallBackTimer() = default;
  CallBackTimer(int interval, std::function<void()> callback) :
    is_running_(false),
    callback_{callback},
    interval_{interval} {}

  ~CallBackTimer() {
    if (is_running_.load(std::memory_order_acquire)) {
      Stop();
    }
  }

  CallBackTimer(const CallBackTimer& other) {
    *this = other;  // call operator=
  }

  CallBackTimer& operator=(const CallBackTimer& other) {
    if (this == &other) return *this;

    this->callback_ = other.callback_;
    this->interval_ = other.interval_;

    return *this;
  }

  void Stop() {
    is_running_.store(false, std::memory_order_release);
    condition_variable_.notify_all();
    if (thread_.joinable())
      thread_.join();
  }

  void Start() {
    if (is_running_.load(std::memory_order_acquire)) {
      return;
    }
    is_running_.store(true, std::memory_order_release);
    thread_ = std::thread([this]() {
      std::unique_lock<std::mutex> lock(cv_mutex);
      while (is_running_.load(std::memory_order_acquire)) {
        callback_();
        // better than thread_sleep because it can interrupted
        condition_variable_.wait_for(lock, std::chrono::milliseconds(interval_));
      }
    });
  }

  bool is_running() const noexcept {
    return (is_running_.load(std::memory_order_acquire) && thread_.joinable());
  }
};
//-----------------------------------------------------------------------------
void CallbackFun() {
  std::cout << "CallbackFun\n";
}
//-----------------------------------------------------------------------------
int main() {
  std::map<std::string, CallBackTimer> timers_;

  CallBackTimer timer{1000, CallbackFun};
  timers_["1"] = timer;

  timers_["1"].Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  timers_["1"].Stop();

  return 0;
}