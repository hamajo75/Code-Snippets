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

void SplitString() {
  // lazy evaluation
  auto split_strings =
    std::string_view{"one two three"} | std::ranges::views::split(' ');

  std::cout << "SplitString()" << "\n";
  for (const auto& str : split_strings) {
    std::cout << std::string_view{str} << "\n";
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
