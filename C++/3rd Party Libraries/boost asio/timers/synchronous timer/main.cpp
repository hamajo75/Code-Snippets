#include <boost/asio.hpp>
#include <iostream>

boost::asio::io_context io_context;
boost::asio::steady_timer timer(io_context, boost::asio::chrono::seconds(5));

void StopTimer() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  timer.cancel();
  std::cout << "Timer stopped\n";
}

//-------------------------------------------------------------------------------
int main() {
  std::cout << "Waiting for timer\n";

  std::thread my_thread([](){
    StopTimer();
  });

  // blocking wait (cannot be stopped)
  timer.wait();

  std::cout << "Timer expired\n";

  my_thread.join();

  return 0;
}
