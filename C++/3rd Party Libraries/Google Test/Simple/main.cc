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
  ASSERT_TRUE(1 == 1) << "Error message!";
}

void MyThrowingFun() {
  throw std::runtime_error("exception");
}

TEST(ConfigurationTest, EmptyCfg) {
  EXPECT_NO_THROW(
    MyThrowingFun());

  EXPECT_THROW(
    MyThrowingFun(),
    std::exception);
}
//-----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}

/* options
--gtest_list_tests        list all tests
--gtest_filter=*MessagingRequestManager*
--gtest_catch_exceptions
*/

