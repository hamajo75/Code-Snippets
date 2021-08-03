#include <chrono>
#include <iostream>
#include <thread>

using namespace std::chrono_literals;   // i think you must do it like this

//-----------------------------------------------------------------------------
void sleep_chrono_literals(std::chrono::duration<float> duration) {
  std::this_thread::sleep_for(duration);
}
//-----------------------------------------------------------------------------
void measure_time() {
  auto start = std::chrono::high_resolution_clock::now();

  sleep_chrono_literals(2000ms);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));                  // this seems easier for me
// std::chrono::nanoseconds
// std::chrono::microseconds
// std::chrono::milliseconds
// std::chrono::seconds
// std::chrono::minutes
// std::chrono::hours

  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = end - start;
  std::cout << "Waited " << elapsed.count() << " ms\n";
}
//-----------------------------------------------------------------------------
int main() {
  measure_time();
}