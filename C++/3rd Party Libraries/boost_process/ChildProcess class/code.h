#pragma once

#include <functional>
#include <memory>
#include <string>

#include <boost/process.hpp>

class ChildProcess {
public:
  ChildProcess(std::function<void(int)> callback) : callback_(callback) {}

  void Run(const std::string &command);
  void Wait();

private:
  std::unique_ptr<boost::process::child> proc_;
  std::function<void(int)> callback_;
};