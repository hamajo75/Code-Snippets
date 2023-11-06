#include "process.h"

Process::Process(const std::string& command) : command_(command) {}

void Process::Start() {
  child_process_ = std::make_unique<boost::process::child>(command_);
}

void Process::Kill() {
  if (child_process_ && child_process_->valid()) {
    child_process_->terminate();
  }
}

bool Process::IsRunning() const {
  if (child_process_ && child_process_->valid()) {
    return child_process_->running();
  }
  return false;
}