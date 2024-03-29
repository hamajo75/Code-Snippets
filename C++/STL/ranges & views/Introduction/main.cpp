#include <ios>
#include <iostream>
#include <string>

#include <algorithm>
#include <vector>
#include <ranges>
#include <numeric>

#include <string_view>

std::vector<int> GetData() {
  return std::vector<int>{2,3,4,5,6,7};
}

// Advantage 1: safe begin(), end()
bool TestData() {

  auto result =
 // std::all_of(
 //   GetData().begin(), GetData().end(),  // BUG: 2 objects
    std::ranges::all_of(GetData(),
    [](const int i) {
      return i < 5;
    });
  return result;
}

// Advantage 2: we can now pipe range views
bool TestDataViews() {
  auto result =
    std::ranges::all_of(GetData() | std::ranges::views::drop(1) | std::ranges::views::take(2),
    [](const int i) {
      return i < 5;
    });
  return result;
}

int GetSumOfSquares() {
  auto view = GetData()
    | std::ranges::views::transform([](int i) { return i * i; })   // this is lazy!
    | std::ranges::views::common;  // good practice when "view" is to be used with C++ 17 algorithms,
                                   // transforms the range into a common type (expected by std::accumulate)

  return std::accumulate(view.begin(), view.end(), 0);
}

std::vector<std::string> SplitString(std::string_view str, char delimiter) {
  auto split_ranges = std::ranges::views::split(str, delimiter);
  std::vector<std::string> split_str;
  for (const auto& range : split_ranges) {
    split_str.emplace_back(range.begin(), range.end());
  }

  return split_str;
}

void SplitString() {
  std::cout << "SplitString():\n";
  auto split_str = SplitString("one two three", ' ');

  for (const auto& str : split_str) {
    std::cout << str << "\n";
  }
}

//-------------------------------------------------------------------------------
int main() {

  SplitString();
  std::cout << "GetSumOfSquares(): " << GetSumOfSquares() << "\n";

  std::cout << std::boolalpha << TestData() << "\n";
  std::cout << std::boolalpha << TestDataViews() << "\n";

  return 0;
}
