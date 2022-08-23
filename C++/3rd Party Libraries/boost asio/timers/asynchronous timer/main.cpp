#include <boost/asio.hpp>
#include <iostream>


//-------------------------------------------------------------------------------
// callback function, called asynchronously
void Handler(const boost::system::error_code& error) {
  if (!error) {
    std::cout << "Asynchronous operation finished \n";
    std::cout << "Timer expired\n";
  } else {
    std::cout << "Some error occurred\n";
  }
}

void StopTimer(boost::asio::steady_timer &timer) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  timer.cancel();
  std::cout << "Timer stopped\n";
}

//-------------------------------------------------------------------------------
int main(int argc, const char *argv[]) {
  boost::asio::io_context io_context;
  boost::asio::steady_timer timer(io_context, boost::asio::chrono::seconds(5));

  // non blocking wait, immediately return
  timer.async_wait(&Handler);
  std::cout << "Waiting for timer\n";

  std::this_thread::sleep_for(std::chrono::milliseconds(1000));

  StopTimer(timer);

  // callback handlers will only be called from threads running io_context.run()
  io_context.run();  // runs while there is work to do

  return 0;
}
