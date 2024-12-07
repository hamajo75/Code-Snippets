#include "gtest/gtest.h"
#include "gtest/gtest-param-test.h"

#include <tuple>
#include <memory>

#include "cut.h"

/* Run the same test logic with different parameters.
*/

// Test fixture class.
class ToHexTest :
  public testing::TestWithParam<std::tuple<int, int, const char*>>
{};

// Parameterized test case.
TEST_P(ToHexTest, IntToHex) {
  const auto& [val, width, expected] = GetParam();
  EXPECT_EQ(ToHex(val, width), expected);
}

INSTANTIATE_TEST_SUITE_P(
  Set1,                                       // Instance name, used internally by Google Test, you'll see it in the test output.
  ToHexTest,                                  // Test case name
  testing::Values(
    std::make_tuple(0, 0, "0x0"),
    std::make_tuple(26, 0, "0x1a"),
    std::make_tuple(32, 0, "0x20"),
    std::make_tuple(1, 2, "0x01")
  )
);

INSTANTIATE_TEST_SUITE_P(
  Set2,                                       // Instance name, used internally by Google Test.
  ToHexTest,                                  // Test case name
  testing::Values(
    std::make_tuple(259, 8, "0x00000103"),
    std::make_tuple(511, 2, "0x1ff")
  )
);

//-----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}




