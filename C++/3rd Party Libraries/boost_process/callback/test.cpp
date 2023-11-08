#include <gtest/gtest.h>
#include <boost/process.hpp>
#include "process.h"

TEST(ProcessTest, TestStart) {
  Process process("echo hello world");
  process.Start();
  // Check that process completed successfully
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}