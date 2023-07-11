#include <string>

#include <boost/asio.hpp>
#include <boost/process.hpp>

/* What do we need?
- a child process
- an end result
- capture output & error
- a callback function, handling error code & output
*/

struct ExecutionResult {
  int result;
  std::string output;
  std::string error;
};

std::string GetString(boost::process::ipstream &stream) {
  std::string str;
  std::string line;
  while (std::getline(stream, line)) {
    str += line + "\n";
  }
  return str;
}

std::future<ExecutionResult> ExecuteCommandNonBlocking(
  const std::string &command
){
  auto result_future = std::async(std::launch::async, [&command]() {
    int result = 1;
    boost::process::ipstream output;
    boost::process::ipstream error;

    try {
      result = boost::process::system(
        command,
        boost::process::std_out > output,
        boost::process::std_err > error);
    } catch (const std::exception& e) {
      return ExecutionResult{result, "", e.what()};
    }

    auto output_str = GetString(output);
    auto error_str = GetString(error);

    return ExecutionResult{result, output_str, error_str};
  });

  return result_future;
}
