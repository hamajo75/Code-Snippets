#include <iostream>
#include <coroutine>

struct ReturnObject
{
  // The compiler will generate code that calls the functions in the promise_type struct.
  struct promise_type
  {
    // This is what the caller of the coroutine will get as a return value.
    ReturnObject get_return_object()
    {
      return ReturnObject{
          std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    auto initial_suspend()
    {
      return std::suspend_never{}; // Don't suspend initially, start immediately
      // return std::suspend_always{}; // - suspend immediately
    }
    std::suspend_always final_suspend() noexcept { return {}; } // Suspend at the end
    void return_void() {}                                       // deal with co_return and reaching the end of the coroutine
    void unhandled_exception() { std::terminate(); }            // deal with exceptions - terminate the program
  };

  std::coroutine_handle<promise_type> handle_;

  ReturnObject(std::coroutine_handle<promise_type> h) : handle_(h) {}

  ~ReturnObject()
  {
    if (handle_)
      handle_.destroy(); // Clean up coroutine resources
  }
  bool Resume() const {
    if (!handle_ || handle_.done()) {
      return false; // nothing (more) to process
    }
    handle_.resume(); // RESUME (blocks until suspended again or the end), segfault when the coroutine is already finished
    return !handle_.done();
  }
};

ReturnObject my_coroutine()
{
  std::cout << "Coroutine started\n";
  co_await std::suspend_always{};     // Suspend here
  std::cout << "Coroutine resumed\n"; // This will run when resumed
}

int main()
{
  auto returnObj = my_coroutine(); // The coroutine starts and prints "Hello"

  std::cout << "after calling coroutine\n"; // Now "World" is printed

  returnObj.Resume(); // Resume the coroutine and print "Coroutine!"
  returnObj.Resume(); // Resume the coroutine and print "Coroutine!"

  return 0;
}
