#include <gtest/gtest.h>

#include "code.h"

TEST(SomeTestSuite, SomeTest) {
  ChildProcess process([](int exit_code) {
    std::cout << "exit_code: " << exit_code << "\n";
  });

  ASSERT_TRUE(false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
