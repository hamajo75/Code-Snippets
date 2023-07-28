#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>
#include <thread>

#include <boost/asio.hpp>
#include <boost/process.hpp>

std::string GetString(boost::process::ipstream &stream) {
  std::string str;
  std::string line;
  while (std::getline(stream, line)) {
    str += line + "\n";
  }
  return str;
}

void AsyncUse() {
  auto command = "ls -l";
  boost::asio::io_context io_context;

  auto c = boost::process::child {
    command,
    io_context,
    boost::process::on_exit([&](int exit, const std::error_code& ec_in) {
        std::cout << "on_exit: " << exit << "\n";
        std::cout << "on_exit: " << ec_in.message() << "\n";
    })
  };

  io_context.run();
}

void SimpleUse() {
  boost::process::ipstream output;
  boost::process::ipstream error;

  auto command = "ls -l";

  std::unique_ptr<boost::process::child> c;

  c = std::make_unique<boost::process::child>(
    boost::process::child{
      command,
      boost::process::std_out > output,   // if omitted defaults to stdout
      boost::process::std_err > error     // if omitted defaults to stderr
    });

  std::cout << "doing other stuff\n";

  // c.wait();
  c->wait_until(std::chrono::system_clock::now() + std::chrono::seconds(1));

  std::cout << "exit_code: " << c->exit_code() << "\n";
  std::cout << "output: " << GetString(output);
  std::cout << "error: " << GetString(error);
}

int main() {
  // SimpleUse();
  AsyncUse();

  return 0;
}
