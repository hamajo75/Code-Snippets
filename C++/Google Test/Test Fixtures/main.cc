#include <iostream>
#include <string.h>
#include <gtest/gtest.h>

//-----------------------------------------------------------------------------
class MyClassUnderTest {
  int base_value_;
 public:
  explicit MyClassUnderTest(int start) : base_value_{start} {}
  void Increment(int value) {
    base_value_ += value;
  }
  int getValue() {return base_value_;}
};
//-----------------------------------------------------------------------------
struct MyClassTest : public testing::Test {
  MyClassUnderTest *mc;
  void SetUp() { mc = new MyClassUnderTest(100); }
  void TearDown() { delete mc; }
};
//-----------------------------------------------------------------------------
TEST_F(MyClassTest, IncrementBy5) {
  mc->Increment(5);
  ASSERT_EQ(mc->getValue(), 105);
}

TEST_F(MyClassTest, IncrementBy10) {
  mc->Increment(10);
  ASSERT_EQ(mc->getValue(), 110);
}
//-----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
