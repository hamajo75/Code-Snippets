#include <functional>
#include <thread>
#include <iostream>

#include <boost/asio.hpp>

/* Purpose: Reset the timer on some recurring event. If the event doesn't
            happen, call a handler function (timeout).
*/

using TimeoutHandler = std::function<void()>;

class Timer {
 public:
  Timer(int interval, TimeoutHandler handler)
    :  timeout_handler_{handler},
       interval_(interval),
       timer_(io_context_, std::chrono::seconds(interval_)) {
    handler_ = [this](const boost::system::error_code& error){
      if (error == boost::asio::error::operation_aborted) {
        // std::cout << "aborted\n";
        return;
      }
      if (timeout_handler_)
        timeout_handler_();
    };
  }

  Timer(const Timer& other)
    : timer_(io_context_, std::chrono::seconds(other.interval_)) {
    *this = other;  // call operator=
  }

  Timer& operator=(const Timer& other) {
    if (this == &other) return *this;

    this->timeout_handler_ = other.timeout_handler_;
    this->interval_ = other.interval_;

    return *this;
  }

  ~Timer() {
    std::cout << "Destructor\n";
    Stop();
  }

  void Stop() {
    timer_.cancel();
    io_context_.stop();
    if (thread_.joinable()) {
      thread_.join();
      thread_started_ = false;
      std::cout << "Thread stopped\n";
    }
  }

  void Reset() {
    if (!thread_started_) {
      Start();
      return;
    }

    // this cancels all running timers
    timer_.expires_after(std::chrono::seconds(interval_));
    // std::cout << "canceled timers: " << timer_.expires_after(std::chrono::seconds(interval_)) << "\n";
    timer_.async_wait(handler_);
  }

 private:
  std::thread thread_;
  bool thread_started_ = false;
  TimeoutHandler timeout_handler_;
  int interval_ = 0;
  boost::asio::io_context io_context_;
  boost::asio::steady_timer timer_;
  std::function<void(const boost::system::error_code& error)>handler_;

  void Start() {
    Stop();
    io_context_.restart();
    thread_ = std::thread([this]() {
      std::cout << "Thread started\n";
      // keep io_context_ event loop running until io_context_.stop()
      boost::asio::executor_work_guard<boost::asio::io_context::executor_type> wg
        = boost::asio::make_work_guard(io_context_);
      thread_started_ = true;
      timer_.async_wait(handler_);
      io_context_.run();
      thread_started_ = false;
      std::cout << "Thread finished\n";
    });
  }
};
