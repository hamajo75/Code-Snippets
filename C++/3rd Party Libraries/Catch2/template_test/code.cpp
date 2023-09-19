#include "code.h"

#include <iostream>

void print_vector(const std::vector<int>& vec) {
  for (const auto& val : vec) {
    std::cout << val << " ";
  }
  std::cout << std::endl;
}