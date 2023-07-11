#pragma once

#include <iomanip>
#include <ios>
#include <sstream>
#include <string>

inline std::string ToHex(int val, int width) {
  std::ostringstream out;
  out << "0x" << std::setfill('0') << std::setw(width) << std::hex << val;
  return out.str();
}
