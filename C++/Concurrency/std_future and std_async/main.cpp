#include <future>
#include <iostream>
#include <string>

//-----------------------------------------------------------------------------
std::string helloFunction(const std::string& s) {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  return "Hello C++11 from " + s + ".";
}
//-----------------------------------------------------------------------------
class HelloFunctionObject {
 public:
  std::string operator()(const std::string& s) const {
    std::this_thread::sleep_for(std::chrono::seconds(2));
    return "Hello C++11 from " + s + ".";
  }
};

std::future<int> async_function() {
  return std::async(std::launch::async, []() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 42;
  });
}

//-----------------------------------------------------------------------------
int main() {
  std::cout << std::endl;

  // future with function
  auto futureFunction = std::async(helloFunction, "function");

  std::cout << "started function.\n";

  // future with function object
  HelloFunctionObject helloFunctionObject;
  auto futureFunctionObject =
      std::async(helloFunctionObject, "function object");

  std::cout << "started object.\n";

  // future with lambda function
  auto futureLambda = std::async(
      [](const std::string& s) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        return "Hello C++11 from " + s + "."; },
      "lambda function");

  std::cout << "started lambda.\n";

  // here we wait until all functions are finished
  std::cout << futureFunction.get() << "\n"
            << futureFunctionObject.get() << "\n"
            << futureLambda.get() << std::endl;

  std::cout << std::endl;


  std::future<int> result_future = async_function();

  int result = result_future.get();
  std::cout << "Result: " << result << std::endl;
}