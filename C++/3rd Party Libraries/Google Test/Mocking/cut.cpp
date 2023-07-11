#include "cut.h"

#include <iostream>
#include <string.h>

// For unit testing purpose
// override fct. the test code
__attribute__((weak))
std::string fun2BMocked() {
  return "fun2BMockedOriginal";
}

void fun2BTested() {
  std::cout << fun2BMocked() << "\n";
}