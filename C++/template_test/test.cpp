#include <gtest/gtest.h>

#include "code.h"

TEST(SomeTestSuite, SomeTest) {
  ASSERT_TRUE(MyTest());
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
