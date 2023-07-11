#include <string>
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

std::future<ExecutionResult> ExecuteCommandNonBlocking(
  const std::string &command,
  std::function<void(ExecutionResult&)> callback
);
