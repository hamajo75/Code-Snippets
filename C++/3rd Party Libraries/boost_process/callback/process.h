#include <boost/process.hpp>
#include <string>

class Process {
 public:
  void Start(const std::string& cmd);
  void Kill();
  bool IsRunning();

 private:
  boost::process::child child;
};