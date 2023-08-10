#include <string>
#include <boost/process.hpp>

/* What do we need?
- a child process
- an end result
- optional: capture output & error
- a callback function, handling error code & output
- terminate the process
- check if the process is still running
- limit process execution with a timeout
*/

struct ExecutionResult {
  int result;
  std::string output;
  std::string error;
};

std::future<ExecutionResult> ExecuteNonBlocking(
  const std::string &command,
  std::function<void(ExecutionResult&)> callback
);
