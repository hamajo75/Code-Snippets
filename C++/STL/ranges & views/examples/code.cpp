#include "code.h"

#include <vector>

std::vector<int> GetData() {
  return std::vector<int>{2,3,4,5,6,7};
}

std::vector<std::string> SplitString(std::string_view str, char delimiter) {
  auto split_ranges = std::ranges::views::split(str, delimiter);
  std::vector<std::string> split_str;
  for (const auto& range : split_ranges) {
    split_str.emplace_back(range.begin(), range.end());
  }

  return split_str;
}

