#include <string>

#include <boost/asio.hpp>
#include <boost/process.hpp>

#include "execute.h"

std::string GetString(boost::process::ipstream &stream) {
  std::string str;
  std::string line;
  while (std::getline(stream, line)) {
    str += line + "\n";
  }
  return str;
}

std::future<ExecutionResult> ExecuteNonBlocking(
  const std::string &command,
  std::function<void(ExecutionResult&)> callback
){
  auto result_future = std::async(std::launch::async, [&command, &callback]() {
    int result = 1;
    boost::process::ipstream output;
    boost::process::ipstream error;

    try {
      result = boost::process::system(
        command,
        boost::process::std_out > output,
        boost::process::std_err > error);
    } catch (const std::exception& e) {
      ExecutionResult execution_result{result, "", e.what()};
      callback(execution_result);
      return execution_result;
    }

    auto output_str = GetString(output);
    auto error_str = GetString(error);

    ExecutionResult execution_result{result, output_str, error_str};
    callback(execution_result);
    return execution_result;
  });

  return result_future;
}