#include <iostream>
#include <string>
#include <boost/process.hpp>

struct ExecutionResult {
  int result;
  std::string output;
};

ExecutionResult ExecuteCommand(const std::string& command) {
  boost::process::ipstream output;
  auto result = boost::process::system(
    command,
    boost::process::std_out > output);

  std::string output_str;
  std::string line;
  while (output && std::getline(output, line)) {
      output_str += line + '\n';
  }

  return ExecutionResult{result, output_str};
}

int main() {
  auto result = ExecuteCommand("ls -l");
  std::cout << "Command output:\n" << result.output;

  return 0;
}
