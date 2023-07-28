#include "code.h"
#include <memory>

#include <iostream>
Process::Process(ProcessCallback callback)
  : callback_{callback} {
}

Process::~Process() {
  if (IsRunning()) {
    Terminate();
  }
}

void Process::DoWait() {
  try {
    // throws an unnecessary exception when the process is terminated
    child_->wait();
  } catch (...) {}
}

void Process::WaitThread() {
  if (!child_)
    return;

  thread_ = std::thread([this]() {
    DoWait();
    callback_(ExecutionResult{child_->exit_code(), "", ""});
  });
  thread_.detach();
}

bool Process::Execute(const std::string &command) {
  if (IsRunning())
    return false;

  try {
    child_ = std::make_unique<boost::process::child>(
      boost::process::child{command}
    );
  } catch (boost::process::process_error& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return false;
  }

  WaitThread();
  return true;
}

void Process::Wait() {
  if (child_)
    DoWait();
}

void Process::Terminate() {
  if (child_)
    child_->terminate();
}

bool Process::IsRunning() {
  if (!child_)
    return false;

  return child_->running();
}
