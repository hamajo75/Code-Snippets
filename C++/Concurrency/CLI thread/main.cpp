#include <stdio.h>
#include <string.h>
#include <iostream>

#include <chrono>
#include <thread>

//-----------------------------------------------------------------------------
// use member function for std::thread
class CLIThread {
 private:
  std::unique_ptr<std::thread> cli_thread_;
  std::string input_ = "";

  void HandleCLI() {
    while (true) {
      std::cout << "Enter a command: ";
      std::cin >> input_;
    }
  }

 public:
  CLIThread() {
    // &CLIThread::HandleCLI, this !! - you have to pass the this pointer
    cli_thread_ = std::make_unique<std::thread>(&CLIThread::HandleCLI, this);
  }
  void WaitForMe() {
    cli_thread_->join();
  }
};
// //-------------------------------------------------------------------------------
// void handle_cli() {
//   std::string input = "";
//   while (true) {
//     std::cout << "Enter a command: ";
//     std::cin >> input;
//   }
// }
//-------------------------------------------------------------------------------
int main() {
  // std::thread command_line_interface(handle_cli);  // here the thread is started
  CLIThread cli_thread;

  while (true) {
    std::cout << "Working in the main thread\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  // command_line_interface.join();  // wait
  cli_thread.WaitForMe();

  return 0;
}
