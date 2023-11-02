#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <algorithm>
#include <ranges>
#include <numeric>

std::vector<int> GetData();

struct Person {
    std::string name;
    int age;
};

std::vector<std::string> SplitString(std::string_view str, char delimiter);
template <typename T>
int GetSumOfSquares(const T& range) {
  auto view = range
    | std::ranges::views::transform([](int i) { return i * i; })   // this is lazy!
    | std::ranges::views::common;  // good practice when "view" is to be used with C++ 17 algorithms,
                                   // transforms the range into a common type (expected by std::accumulate)

  return std::accumulate(view.begin(), view.end(), 0);
}