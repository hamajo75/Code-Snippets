#include "code.h"

void ChildProcess::Run(const std::string &command) {
  proc_ = std::make_unique<boost::process::child>(command);
}

void ChildProcess::Wait() {
  proc_->wait();
  callback_(proc_->exit_code());
}

