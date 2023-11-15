#include <gtest/gtest.h>

#include "code.h"

TEST(SomeTestSuite, SomeTest) {
  Foo foo;
  Bar bar(std::move(foo));
  bar.Use();
  foo.Use();  // This is dangerous.
  ASSERT_TRUE(false);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
