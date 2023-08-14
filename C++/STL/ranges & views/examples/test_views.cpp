#include <gtest/gtest.h>

#include "code.h"
#include "test_ranges.h"

TEST(Views, SplitString) {
  auto split_str = SplitString("one two three", ' ');
  ASSERT_EQ(split_str.size(), 3);
}

TEST(Views, SplitStringEmpty) {
  auto split_str = SplitString("", ' ');
  ASSERT_EQ(split_str.size(), 0);
}

TEST(Views, GetSumOfSquares) {
  auto sum = GetSumOfSquares(GetData());
  ASSERT_EQ(sum, 139);
}

TEST(Views, FilteringObjects) {
  std::vector<Person> people = {
      {"Alice", 25},
      {"Bob", 17},
      {"Charlie", 30},
      {"David", 16},
      {"Eve", 22}
  };

  // Using a range-based loop to filter and print adult persons
  std::cout << "Adults (using range-based loop):" << std::endl;
  for (const Person& person : people) {
      if (person.age >= 18) {
          std::cout << person.name << " (" << person.age << " years old)" << std::endl;
      }
  }

  std::cout << std::endl;

  // Using std::ranges::views::filter to create a filtered view
  auto adultView = people | std::views::filter([](const Person& person) {
      return person.age >= 18;
  });

  // Using a range-based loop to print filtered persons
  std::cout << "Adults (using std::ranges::views::filter):" << std::endl;
  for (const Person& person : adultView) {
      std::cout << person.name << " (" << person.age << " years old)" << std::endl;
  }
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
