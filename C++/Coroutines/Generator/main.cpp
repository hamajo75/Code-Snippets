#include <iostream>
#include <string>
#include <coroutine>
#include <utility>
#include <cstdint>

class Generator {
 public:
  struct promise_type {
      std::uint64_t current_value_ = 0;
      Generator get_return_object() {
          return Generator{
              std::coroutine_handle<promise_type>::from_promise(*this)};
      }

      auto initial_suspend() { return std::suspend_always{}; }          // suspend initially
      auto final_suspend() noexcept { return std::suspend_always{}; }   // Suspend at the end
      void return_void() {}
      void unhandled_exception() { std::terminate(); }
      std::suspend_always yield_value(std::uint64_t value) {
          current_value_ = value;
          return std::suspend_always{};                         // here the coroutine is really suspended
      }
  };

  Generator(auto handle) : handle_{handle} {}
  ~Generator() {
    if (handle_)
      handle_.destroy();
  }

  // For simplicity, we don't implement copy/move constructors
  Generator(const Generator&) = delete;
  Generator& operator=(const Generator&) = delete;

  std::uint64_t operator()() const {
    handle_.resume();
    return handle_.promise().current_value_;
  }

 private:
  std::coroutine_handle<promise_type> handle_;
};

Generator Fibonacci() {
  std::uint64_t n_minus_1 = 0, n = 1;
  while(true) {
    co_yield n;                                         // Suspend and return value of the expression behind co_yield
                                                        // this will call promise_type::yield_value()
    n_minus_1 = std::exchange(n, n_minus_1 + n);
  }
}

int main() {
  std::cout << "Printing Fibonacci numbers:\n";

  auto generator = Fibonacci();
  for (int i = 0; i < 10; ++i) {
    std::cout << generator() << "\n";
  }

  return 0;
}
