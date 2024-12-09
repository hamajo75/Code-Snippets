#include <iostream>
#include <vector>
#include <map>
#include <ranges>

void filter_map() {
  std::map<std::string, int> composers{
    {"Bach", 1685},
    {"Beethoven", 1770},
    {"Chopin", 1810},
    {"Mozart", 1756},
    {"Tchaikovsky", 1840},
    {"Vivaldi ", 1678},
  };

  // iterate over the names of the first three composers born since 1700:
  for (const auto& elem : composers
                           | std::views::filter([](const auto& y) {   // since 1700
                                           return y.second >= 1700;
                                         })
                           | std::views::take(3)                      // first three: sorted by key
                           | std::views::keys                         // keys/names only
                           ) {
    std::cout << "- " << elem << '\n';
  }
}

int main() {
  filter_map();
}

