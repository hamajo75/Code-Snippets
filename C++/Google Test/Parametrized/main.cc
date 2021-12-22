#include "gtest/gtest.h"
#include "gtest/gtest-param-test.h"

#include <tuple>
#include <memory>

#include "cut.h"

class ToHexTest :
  public testing::TestWithParam<std::tuple<int, int, const char*>>
{};

TEST_P(ToHexTest, IntToHex) {
  const auto& [val, width, expected] = GetParam();
  EXPECT_EQ(ToHex(val, width), expected);
}

INSTANTIATE_TEST_SUITE_P(
  HexDecIntegers,
  ToHexTest,
  testing::Values(
    std::make_tuple(0, 0, "0x0"),
    std::make_tuple(26, 0, "0x1a"),
    std::make_tuple(32, 0, "0x20"),
    std::make_tuple(1, 2, "0x01"),
    std::make_tuple(259, 8, "0x00000103"),
    std::make_tuple(511, 2, "0x1ff")
  )
);

//-----------------------------------------------------------------------------
int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}




