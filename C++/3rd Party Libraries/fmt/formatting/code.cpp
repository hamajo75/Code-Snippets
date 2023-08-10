#include "code.h"

#include <fmt/core.h>
#include <fmt/ranges.h>

bool Print() {
  fmt::print("I'd rather be {1} than {0}.", "right", "happy");
  return true;
}

std::string ToString(const std::vector<int>& v) {
  return fmt::format("{}", v);
}