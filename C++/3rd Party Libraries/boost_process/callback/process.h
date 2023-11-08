#include <boost/process.hpp>
#include <memory>

class Process {
 public:
  explicit Process(const std::string& command);
  void Start();
  void Kill();
  bool IsRunning() const;

 private:
  std::string command_;
  std::unique_ptr<boost::process::child> child_process_;
};