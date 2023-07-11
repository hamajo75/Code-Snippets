#include <boost/process/async_system.hpp>
#include <boost/process/detail/child_decl.hpp>
#include <boost/process/search_path.hpp>
#include <boost/process/spawn.hpp>
#include <iostream>
#include <string>

#include <boost/process.hpp>
#include <thread>


using namespace std::literals::chrono_literals;
//-------------------------------------------------------------------------------
int main() {

  // boost::process::search_path("");

  // this will wait until the child process is finished
  auto result = boost::process::system("ls -l");

  // boost::process::async_system(boost::asio::io_context &ios, ExitHandler &&exit_handler, Args &&args...)

  // immediately detached (fire & forget)
  // boost::process::spawn(Args &&args...)

  // non blocking execution
  boost::process::child proc("sleep 10; ls -l");

  while (proc.running()) {
    std::cout << "doing other stuff\n";
    std::this_thread::sleep_for(1s);
  }

  proc.wait();

  return 0;
}
