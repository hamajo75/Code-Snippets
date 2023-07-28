#include <chrono>
#include <gtest/gtest.h>

#include "code.h"

class ProcessTest : public ::testing::Test {
 public:
  int i = 1;
  Process p {
    [this](ExecutionResult result) {
      if (result.result == 0) {
        std::cout << "Success " << result.output << std::endl;
        i++;
      } else {
        std::cout << "Error " << result.error << std::endl;
        i--;
      }
    }
  };
};

class MeasureTime {
 public:
  MeasureTime() {
    start_ = std::chrono::high_resolution_clock::now();
  }
  void Expect_LT(std::chrono::milliseconds ms) {
    auto diff = GetDuraction();
    EXPECT_LT(diff.count(), ms.count());
  }
  void Expect_GT(std::chrono::milliseconds ms) {
    auto diff = GetDuraction();
    EXPECT_GT(diff.count(), ms.count());
  }
 private:
  std::chrono::high_resolution_clock::time_point start_;
  std::chrono::duration<double, std::milli>GetDuraction() {
    auto end = std::chrono::high_resolution_clock::now();
    return end - start_;
  }
};

TEST_F(ProcessTest, SimpleUse) {
  ASSERT_TRUE(p.Execute("echo Hello, World!"));

  // give some time for the callback to finish
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  ASSERT_EQ(i, 2);
}

TEST_F(ProcessTest, Wait) {
  MeasureTime time;
  ASSERT_TRUE(p.Execute("sleep 1"));
  p.Wait();

  time.Expect_GT(std::chrono::seconds(1));

  // give some time for the callback to finish
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  ASSERT_EQ(i, 2);
}

TEST_F(ProcessTest, Terminate) {
  MeasureTime time;
  ASSERT_TRUE(p.Execute("sleep 10"));
  p.Terminate();

  time.Expect_LT(std::chrono::seconds(1));

  // give some time for the callback to finish
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  ASSERT_EQ(i, 0);
}

TEST_F(ProcessTest, ExecuteWithTimeout) {
  MeasureTime time;
  ASSERT_TRUE(p.Execute("sleep 10", std::chrono::seconds(1)));

  time.Expect_LT(std::chrono::seconds(2));

  // give some time for the callback to finish
  std::this_thread::sleep_for(std::chrono::seconds(3));
  ASSERT_EQ(i, 0);
}

TEST_F(ProcessTest, ExecuteFail) {
  ASSERT_FALSE(p.Execute("akdjfhkafh"));
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
