#include <gtest/gtest.h>
#include <boost/process.hpp>
#include "execute.h"

TEST(ExecuteCommandNonBlockingTest, TestEchoCommand) {
  std::string command = "echo Hello, World!";
  auto future = ExecuteCommandNonBlocking(command);
  auto result = future.get();

  ASSERT_EQ(result.result, 0);
  ASSERT_EQ(result.output, "Hello, World!\n");
  ASSERT_EQ(result.error, "");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
