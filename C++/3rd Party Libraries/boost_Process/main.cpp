#include <boost/asio/io_service.hpp>
#include <boost/process.hpp>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <thread>

struct ExecutionResult {
  int result;
  std::string output;
};

ExecutionResult ExecuteCommandBlocking(const std::string &command) {
  boost::process::ipstream output;
  auto result =
      boost::process::system(command, boost::process::std_out > output);

  std::string output_str;
  std::string line;
  while (output && std::getline(output, line)) {
    output_str += line + '\n';
  }

  return ExecutionResult{result, output_str};
}

ExecutionResult ExecuteCommandNonBlocking(const std::string &command) {
  boost::process::ipstream output;
  auto result =
      boost::process::system(command, boost::process::std_out > output);

  std::string output_str;
  std::string line;
  while (output && std::getline(output, line)) {
    output_str += line + '\n';
  }

  return ExecutionResult{result, output_str};
}



int main() {
  // auto result = ExecuteCommandBlocking("ls -l");
  // std::cout << "Command output:\n" << result.output;

    boost::asio::io_service ios;
    std::vector<char> buf(4096);
    boost::process::child c(
        "ls -l", boost::process::std_out > boost::asio::buffer(buf), ios);

    std::thread t([&ios, &c]() {
        ios.run();
        c.wait();
    });

    t.join(); // Wait for the thread to finish

  std::cout << "exit_code: " << c.exit_code();

  return 0;
}
