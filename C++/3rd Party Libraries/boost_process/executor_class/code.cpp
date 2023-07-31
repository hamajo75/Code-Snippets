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

  // thread_ = std::thread([this, timeout]() {
    DoWait(timeout);
    callback_(ExecutionResult{child_->exit_code(), "", ""});
  // });
  // thread_.detach();
}

bool DoExecute(const std::string &command,
                        ProcessCallback callback,
                        std::optional<std::chrono::milliseconds> timeout) {
  std::thread([command, callback, timeout]() {
    try {
      boost::process::child child = boost::process::child{command};
      try {
        // throws an unnecessary exception when the process is terminated
        if (timeout.has_value()) {
          child.wait_for(timeout.value());
        } else {
          child.wait();
        }
      } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
      }
      callback(ExecutionResult{child.exit_code(), "", ""});
    } catch (boost::process::process_error& e) {
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }).detach();

  return true;
}

bool Process::Execute(const std::string &command, std::chrono::milliseconds timeout) {
  return DoExecute(command, callback_, timeout);
}

bool Process::Execute(const std::string &command) {
  return DoExecute(command, callback_, std::nullopt);
}

bool Execute(const std::string &command, ProcessCallback callback, std::chrono::milliseconds timeout) {
  return DoExecute(command, callback, timeout);
}

bool Execute(const std::string &command, ProcessCallback callback) {
  return DoExecute(command, callback, std::nullopt);
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
