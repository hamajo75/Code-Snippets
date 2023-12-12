#include "process.h"

void Process::Start(const std::string& cmd) {
  child = boost::process::child(cmd);
}

void Process::Kill() {
  child.terminate();
}

bool Process::IsRunning() {
  return child.running();
}