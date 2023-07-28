#include "code.h"
#include <memory>

#include <iostream>
#include <optional>
Process::Process(ProcessCallback callback)
  : callback_{callback} {
}

Process::~Process() {
  if (IsRunning()) {
    Terminate();
  }
}

void Process::DoWait(std::optional<std::chrono::milliseconds> timeout) {
  try {
    // throws an unnecessary exception when the process is terminated
    if (timeout.has_value()) {
      child_->wait_for(timeout.value());
    } else {
      child_->wait();
    }
  } catch (std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void Process::WaitThread(std::optional<std::chrono::milliseconds> timeout) {
  if (!child_)
    return;

  thread_ = std::thread([this, timeout]() {
    DoWait(timeout);
    callback_(ExecutionResult{child_->exit_code(), "", ""});
  });
  thread_.detach();
}

bool Process::DoExecute(const std::string &command,
                      std::optional<std::chrono::milliseconds> timeout) {
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

  WaitThread(timeout);
  return true;
}

bool Process::Execute(const std::string &command, std::chrono::milliseconds timeout) {
  return DoExecute(command, timeout);
}

bool Process::Execute(const std::string &command) {
  return DoExecute(command, std::nullopt);
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
