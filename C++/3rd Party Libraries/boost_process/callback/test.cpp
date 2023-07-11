#include <gtest/gtest.h>
#include <boost/process.hpp>
#include "execute.h"

TEST(ExecuteCommandNonBlockingTest, TestScript) {
  std::string command = "script.sh";
  auto future = ExecuteCommandNonBlocking(command,
    [](ExecutionResult& result) {
      ASSERT_EQ(result.result, 1);
      ASSERT_EQ(result.output, "script started\n");
      ASSERT_EQ(result.error, "script finished with error\n");
    }
  );

  std::cout << "Waiting for future to finish..." << std::endl;
  future.wait();

}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
