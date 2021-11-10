#include <iostream>
#include <string>

#include <vector>
#include <random>

#include <thread>
#include <atomic>

std::atomic<bool> printing = false;

void Print(int i) {
  std::cout << "printing: " << i << std::endl;
}

void WaitRandomTime() {
  std::mt19937_64 eng{std::random_device{}()};  // or seed however you want
  std::uniform_int_distribution<> dist{10, 100};
  std::this_thread::sleep_for(std::chrono::milliseconds{dist(eng)});
}

//-------------------------------------------------------------------------------
int main() {

  std::vector<std::thread> threads;

  for (int i = 0; i < 100; ++i) {
    threads.push_back(
      std::thread{[i](){
        WaitRandomTime();
        if (!printing.exchange(true)) {     // winner takes it all
          Print(i);
        }
      }}
    );
  }

  for (auto& t : threads) t.join();

  return 0;
}
