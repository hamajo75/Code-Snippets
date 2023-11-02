#pragma once

TEST(Ranges, TestElementsOfRange) {
  auto all_bigger_4 = std::ranges::all_of(GetData(),
  [](const int i) {
    return i < 5;
  });
  ASSERT_FALSE(all_bigger_4);
}

TEST(Ranges, TestElementsOfModifiedRange) {
   auto all_bigger_4 =
    std::ranges::all_of(GetData() | std::ranges::views::drop(1) | std::ranges::views::take(2),
    [](const int i) {
      return i < 5;
    });
 ASSERT_TRUE(all_bigger_4);
}