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

void Process::Execute(const std::string &command) {
  if (IsRunning())
    return;

  child_ = std::make_unique<boost::process::child>(
    boost::process::child{command}
  );

  WaitThread();
}

void Process::Wait() {
  if (IsRunning())
    DoWait();
}

void Process::Terminate() {
  if (IsRunning())
    child_->terminate();
}

bool Process::IsRunning() {
  if (!child_)
    return false;

  return child_->running();
}
