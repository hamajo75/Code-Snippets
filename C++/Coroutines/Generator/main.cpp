#include <iostream>
#include <string>
#include <coroutine>
#include <utility>
#include <cstdint>

class Generator {
 public:
  struct promise_type {
      std::uint64_t current_value_;
      Generator get_return_object() {
          return Generator{
              std::coroutine_handle<promise_type>::from_promise(*this)};
      }

      std::suspend_never initial_suspend() { return {}; }  // Don't suspend initially
      std::suspend_always final_suspend() noexcept { return {}; }  // Suspend at the end
      void return_void() {}
      void unhandled_exception() { std::terminate(); }
      std::suspend_always yield_value(std::uint64_t value) {
          current_value_ = value;
          return {};
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

Generator fibonacci() {
  std::uint64_t n_minus_1 = 0, n = 1;
  while(true) {
    co_yield n;
    n = std::exchange(n_minus_1, n_minus_1 + n);
  }
}

int main() {
  std::cout << "Printing Fibonacci numbers:\n";
  // for (auto i : fibonacci()) {
    auto generator = fibonacci();
    std::cout << generator() << "\n";
    std::cout << generator() << "\n";
    std::cout << generator() << "\n";
  // }

  return 0;
}
