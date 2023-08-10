#include <gtest/gtest.h>

#include "code.h"

// apt install libfmt-dev

TEST(SomeTestSuite, SomeTest) {
  testing::internal::CaptureStdout();
  Print();
    std::string output = testing::internal::GetCapturedStdout();
  ASSERT_EQ(output, "I'd rather be happy than right.");

  ASSERT_EQ(ToString({1, 2, 3}), "{1, 2, 3}");
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
