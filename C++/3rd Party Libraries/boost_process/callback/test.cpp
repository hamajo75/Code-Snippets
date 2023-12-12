#include "gtest/gtest.h"
#include "process.h"

TEST(ProcessTest, Start) {
  Process process;
  process.Start("sleep 1");
  ASSERT_TRUE(process.IsRunning());
}

TEST(ProcessTest, Kill) {
  Process process;
  process.Start("sleep 10");
  process.Kill();
  ASSERT_FALSE(process.IsRunning());
}

TEST(ProcessTest, IsRunning) {
  Process process;
  process.Start("sleep 1");
  ASSERT_TRUE(process.IsRunning());
  process.Kill();
  ASSERT_FALSE(process.IsRunning());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}