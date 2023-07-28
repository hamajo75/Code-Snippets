#include <string>
#include <thread>
#include <memory>
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

class Process {
 public:
  explicit Process(ProcessCallback callback);
  ~Process();

  bool Execute(const std::string &command);
  void Terminate();
  void Wait();

  bool IsRunning();

 private:
  std::unique_ptr<boost::process::child> child_;
  boost::process::ipstream output_;
  boost::process::ipstream error_;
  std::thread thread_;

  ProcessCallback callback_;

  void WaitThread();
  void DoWait();
};
