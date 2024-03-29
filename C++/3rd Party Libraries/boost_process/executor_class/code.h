#include <string>
#include <thread>
#include <memory>
#include <optional>

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

typedef std::function<void(ExecutionResult)> ProcessCallback;

bool Execute(const std::string &command, ProcessCallback callback);
bool Execute(const std::string &command, ProcessCallback callback, std::chrono::milliseconds timeout);

class Process {
 public:
  explicit Process(ProcessCallback callback);
  ~Process();

  bool Execute(const std::string &command);
  bool Execute(const std::string &command, std::chrono::milliseconds timeout);
  void Terminate();
  void Wait();

  bool IsRunning();

 private:
  std::unique_ptr<boost::process::child> child_;
  boost::process::ipstream output_;
  boost::process::ipstream error_;
  std::thread thread_;

  ProcessCallback callback_;

  void WaitThread(std::optional<std::chrono::milliseconds> timeout = std::nullopt);
  void DoWait(std::optional<std::chrono::milliseconds> timeout = std::nullopt);
};
