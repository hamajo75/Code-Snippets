#include <chrono>
#include <future>
#include <iostream>
#include <numeric>
#include <thread>
#include <vector>

//-----------------------------------------------------------------------------
void accumulate(std::vector<int>::iterator first,
                std::vector<int>::iterator last,
                std::promise<int> accumulate_promise) {
  int sum = std::accumulate(first, last, 0);
  accumulate_promise.set_value(sum);                                                     // fulfill promise
}
//-----------------------------------------------------------------------------
void do_work(std::promise<void> barrier) {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  barrier.set_value();
}
//-----------------------------------------------------------------------------
int main() {
  // Transmit a result from thread to main thread.
  std::vector<int> numbers = {1, 2, 3, 4, 5, 6};

  std::promise<int> accumulate_promise;
  std::future<int> accumulate_future = accumulate_promise.get_future();

  std::thread work_thread(accumulate, numbers.begin(), numbers.end(),
                          std::move(accumulate_promise));                                 // start accumulate

  // future::get() will wait until the future has a valid result and retrieves
  // it. Calling wait() before get() is not needed accumulate_future.wait();  //
  // wait for result
  std::cout << "result=" << accumulate_future.get() << '\n';                              // wait for promise with get()
  work_thread.join();  // wait for thread completion

  // Demonstrate using promise<void> to signal state between threads.
  std::promise<void> barrier;
  std::future<void> barrier_future = barrier.get_future();

  std::thread new_work_thread(do_work, std::move(barrier));                             // start do_work
  barrier_future.wait();                                                                // wait for promise with wait()
  new_work_thread.join();
}