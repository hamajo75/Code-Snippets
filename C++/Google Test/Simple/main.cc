/*
Installation (Ubuntu)
: sudo apt install libgtest-dev

Build gtest lib
: cd /usr/src/gtest
: sudo cmake CMakeLists.txt
: sudo make
: sudo cp lib/*.a /usr/lib
*/

#include <iostream>
#include <string.h>
#include <gtest/gtest.h>

TEST(Test1, Subtest1) {
  ASSERT_TRUE(1 == 1);
}
TEST(Test1, Subtest2) {
  ASSERT_FALSE(1 == 2);
}
//-----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}




