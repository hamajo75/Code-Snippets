#include <iostream>
#include <string.h>

//-------------------------------------------------------------------------------
class Logger {
 private:
  std::string name = "log";   // have some state here

  Logger() {}

  // thread-safe in C++11
  static Logger& getInstance() {
    static Logger logger;             // here would be the place to inject an alternative object
    return logger;
  }

  void log(const std::string& message) {
    std::cout << name << ": " << message << "\n";
  }

 public:
  static void Debug(const std::string& message) {
    getInstance().log(message);
  }
};
//-------------------------------------------------------------------------------
int main() {
  Logger::Debug("Hello World");

  return 0;
}
