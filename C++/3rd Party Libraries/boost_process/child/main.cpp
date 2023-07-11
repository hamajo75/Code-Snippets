#include <boost/asio/io_service.hpp>
#include <boost/process.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <thread>

std::string GetString(boost::process::ipstream &stream) {
  std::string str;
  std::string line;
  while (std::getline(stream, line)) {
    str += line + "\n";
  }
  return str;
}

int main() {
  boost::process::ipstream output;
  boost::process::ipstream error;

  boost::process::child c(
      "ls -l",
      boost::process::std_out > output,
      boost::process::std_err > error);

  std::cout << "doing other stuff\n";

  // c.wait();
  c.wait_until(std::chrono::system_clock::now() + std::chrono::seconds(1));

  std::cout << "exit_code: " << c.exit_code() << "\n";
  std::cout << "output: " << GetString(output);
  std::cout << "error: " << GetString(error);

  return 0;
}
