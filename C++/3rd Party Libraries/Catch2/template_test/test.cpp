// Dependencies:
// https://github.com/catchorg/Catch2

// Generated by CodiumAI

#include <catch2/catch_test_macros.hpp>
#include <cstdint>
#include <iostream>
#include <sstream>

#include "code.h"

TEST_CASE("PrintVector") {
  // Should print all elements of a non-empty vector
  SECTION("should print all elements of a non-empty vector when the vector is non-empty") {
    std::vector<int> vec = {1, 2, 3, 4};
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    print_vector(vec);

    std::cout.rdbuf(oldCout);
    REQUIRE(output.str() == "1 2 3 4 \n");
  }
}

TEST_CASE("PrintVectorEmpty") {
  // Should print nothing when the vector is empty
  SECTION("should print nothing when the vector is empty") {
    std::vector<int> vec = {};
    std::stringstream output;
    std::streambuf* oldCout = std::cout.rdbuf(output.rdbuf());

    print_vector(vec);

    std::cout.rdbuf(oldCout);
    REQUIRE(output.str() == "\n");
  }
}